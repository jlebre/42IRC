#include "server.hpp"

void   Server::reply(Client &client, std::string msg)
{
    msg += "\r\n";
    send(client.get_fd(), msg.c_str(), msg.length(), 0);
}

void    Server::reply_all(std::string msg)
{
    msg += "\r\n";
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->second->getAuth() == true)
            send(it->second->get_fd(), msg.c_str(), msg.length(), 0);
    }
}

// Sends a message to all clients in the given channel
void    Server::reply_on_channel(std::string msg, Channel &channel)
{
    msg += "\r\n";
    for (std::vector<Client*>::iterator cli = channel.get_members().begin(); cli != channel.get_members().end(); cli++)
    {
        if ((*cli)->getAuth())
            send((*cli)->get_fd(), msg.c_str(), msg.length(), 0);
    }
}

// Sends a message to all clients in the same channels as the given client
void    Server::reply_all_on_channel(std::string msg, Client& client)
{
    std::string channel_name;
    for (std::vector<Channel>::iterator chan_it = _channels.begin(); chan_it != _channels.end(); chan_it++)
    {
        if (check_client_on_channel(client.getNick(), chan_it->get_name()))
        {
            channel_name = chan_it->get_name();
            Channel channel;
            try {
                channel = find_channel(channel_name);
                reply_on_channel(msg, channel);
            } catch (std::exception &e) {
                return ;
            }
            break;
        }
    }
}
