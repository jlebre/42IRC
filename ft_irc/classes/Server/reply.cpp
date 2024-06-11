#include "server.hpp"

// Reply should be everyone, except for myself
void   Server::reply(Client *client, std::string msg)
{
    msg += "\r\n";
    send(client->get_fd(), msg.c_str(), msg.length(), 0);
}

void    Server::reply_all(std::string msg, Client *client)
{
    msg += "\r\n";
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second->getAuth() && it->second->getNick() != client->getNick())
            send(it->second->get_fd(), msg.c_str(), msg.length(), 0);
    }
}

// Sends a message to all clients in the given channel
void    Server::reply_on_channel(std::string msg, Channel *channel, Client *client)
{
    std::vector<Client*> members = channel->get_members();
    for (size_t i = 0; i < members.size(); i++)
        if (members[i]->getAuth() && members[i]->getNick() != client->getNick())
            reply(members[i], msg);
}

// Sends a message to all clients in the same channels as the given client
void    Server::reply_on_all_channels(std::string msg, Client *client)
{
    std::string channel_name;
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (check_client_on_channel(client->getNick(), _channels[i]->get_name()))
        {
            Channel *channel = get_channel(_channels[i]->get_name());
            reply_on_channel(msg, channel, client);
        }
    }
}
