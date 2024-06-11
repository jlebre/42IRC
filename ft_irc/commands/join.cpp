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
    channel->add_client(client);
    client->addChannel(channel);
    reply_on_all_channels(":" + client->getNick() + " JOIN " + channel->get_name(), client);
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

void		Server::join(Client *client)
{
    std::cout << "JOIN COMMAND\n";
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "JOIN"));
        return ;
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
                reply(client, ":" + client->getNick() + " JOIN " + channel_name);
            }
            else
            {
                for (size_t j = 0; j < _channels.size(); j++){
                    if (_channels[j]->get_name() == channel_name)
                    {
                        if (is_invite_only(_channels[j]))
                        {
                            if (!is_invited(_channels[j], client))
                            {
                                reply(client, ERR_INVITEONLYCHAN(this->_sock.ip, _channels[j]->get_name()));
                                return ;
                            }
                            else
                                do_join(_channels[j], client);
                        }
                        else
                            do_join(_channels[j], client);
                    }
                }
            }
        }
    }
}   