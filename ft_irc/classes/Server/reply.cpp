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

void    Server::reply_all_on_channel(std::string msg, std::string channel_name)
{
    msg += "\r\n";
    Channel channel = find_channel(channel_name);
    std::vector<Client> cli = channel.get_clients();
    for (size_t i = 0 ; i < cli.size() ; i++)
    {
        if (cli[i].getAuth() == true)
            send(cli[i].get_fd(), msg.c_str(), msg.length(), 0);
    }
}