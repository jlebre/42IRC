#include "server.hpp"

bool check_if_is_channel(const std::string& str)
{
    if (str.empty() || str.size() > 50)
        return false;

    char firstChar = str[0];
    if (firstChar != '#' && firstChar != '&' && firstChar != '!' && firstChar != '+')
        return false;

    if (str.find_first_of(" \a\b\f\n\r\t\v,:") != std::string::npos)
        return false;
    return true;
}

bool Server::compare_channel_name(const std::string& name1, const std::string& name2)
{
    if (name1.size() != name2.size())
        return false;

    for (size_t i = 0; i < name1.size(); ++i) {
        if (tolower(name1[i]) != tolower(name2[i]))
            return false;
    }
    return true;
}

bool Server::check_if_channel_exists(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i] && compare_channel_name(_channels[i]->get_name(), name))
            return true;
    }
    return false;
}

bool    Server::check_if_client_exists(std::string nick)
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i] && (_clients[i]->getNick() == nick))
            return true;
    }
    return false;
}

bool is_invite_only(Channel *channel)
{
    return channel->get_mode()._invite;
}

void    Server::do_join(Channel *channel, Client *client)
{
    std::string	client_list = "";
    for (unsigned long j = 0; j < channel->get_members().size(); j++)
    {
        if (j != 0)
            client_list += " ";
        if (channel->get_members().at(j)->is_operator(channel))
            client_list += "@" + channel->get_members().at(j)->getNick();
        else
            client_list += channel->get_members().at(j)->getNick();
    }
    channel->add_client(client);
    client->addChannel(channel);
    for (size_t i = 0; i < channel->get_members().size(); i++)
            reply(channel->get_members()[i], JOIN_REPLY(client->getNick(), channel->get_name()));
    if (!channel->get_topic().empty())
        reply(client, RPL_TOPIC(client->getNick(), channel->get_name(), channel->get_topic()));
    else
        reply(client, RPL_NOTOPIC(client->getNick(), channel->get_name()));
    reply(client, RPL_NAMREPLY(client->getNick(), channel->get_name(), client_list));
    reply(client, RPL_ENDOFNAMES(client->getNick(), channel->get_name()));
}

bool    is_invited(Channel *channel, Client *client)
{
    std::vector<Client*> invited = channel->get_invited();
    for (size_t i = 0; i < invited.size(); i++)
    {
        if (invited[i] == client)
            return true;
    }
    return false;
}

void Server::join(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return;
    }

    for (size_t i = 1; i < parsed_message.size(); i++)
    {
        std::string channel_name = parsed_message[i];
        if (check_if_is_channel(channel_name))
        {
            if (!check_if_channel_exists(channel_name))
            {
                Channel *new_channel = new Channel;
                new_channel->set_name(channel_name);
                new_channel->add_operator(client);
                new_channel->set_topic("");
                _channels.push_back(new_channel);
                do_join(new_channel, client);
            }
            else
            {
                for (size_t j = 0; j < _channels.size(); j++)
                {
                    if (compare_channel_name(_channels[j]->get_name(),channel_name))
                    {
                        Channel *channel = _channels[j];
                        if (is_invite_only(channel))
                        {
                            if (!is_invited(channel, client))
                            {
                                reply(client, ERR_INVITEONLYCHAN(client->getNick(), channel->get_name()));
                                return;
                            }
                            else
                                do_join(_channels[j], client);
                        }
                        else if (channel->get_mode()._key)
                        {
                            if (parsed_message.size() > i + 1 && parsed_message[i + 1] == channel->get_mode()._key_password)
                            {
                                i++;
                                do_join(_channels[j], client);
                            }
                            else
                            {
                                reply(client, ERR_BADCHANNELKEY(client->getNick(), channel_name));
                                return;
                            }
                        }
                        else if (channel->get_mode()._limit)
                        {
                            if (channel->get_members().size() < channel->get_mode()._nb)
                                do_join(_channels[j], client);
                            else
                            {
                                reply(client, ERR_CHANNELISFULL(client->getNick(), channel_name));
                                return;
                            }
                        }
                        else
                            do_join(_channels[j], client);
                    }
                }
            }
        }
        else
            reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
    }
    std::cout << "JOIN COMMAND\n";
}