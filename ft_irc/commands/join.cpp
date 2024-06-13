#include "server.hpp"

// Pode juntar a mais do que 1 canal de uma vez

// Adicionar mais checks
// Se tem # no meio e caracteres proibidos
bool check_if_is_channel(std::string str){
    const char *tmp;
    tmp = str.c_str();
    if (tmp[0] == '#')
        return true;
    return false;
}

bool Server::check_if_channel_exists(std::string name)
{
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i] && (_channels[i]->get_name() == name))
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
        {
            client_list += "@" + channel->get_members().at(j)->getNick();
        }	else	{
            client_list += channel->get_members().at(j)->getNick();
        }

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
                new_channel->add_client(client);
                new_channel->add_operator(client);
                new_channel->set_topic("");
                client->addChannel(new_channel);
                _channels.push_back(new_channel);
                reply(client, JOIN_REPLY(client->getNick(), new_channel->get_name()));
            }
            else
            {
                for (size_t j = 0; j < _channels.size(); j++)
                {
                    if (_channels[j]->get_name() == channel_name)
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
                                do_join(channel, client);
                        }
                        else if (channel->get_mode()._key)
                        {
                            if (parsed_message.size() > i + 1 && parsed_message[i + 1] == channel->get_mode()._key_password)
                            {
                                i++; // Skip the password parameter
                                do_join(channel, client);
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
                                do_join(channel, client);
                            else
                            {
                                reply(client, ERR_CHANNELISFULL(client->getNick(), channel_name));
                                return;
                            }
                        }
                        else
                            do_join(channel, client);
                    }
                }
            }
        }
        else
            reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel_name));

    }
    std::cout << "JOIN COMMAND\n";
}