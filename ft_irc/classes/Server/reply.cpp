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

// Sends a message to all clients in the same channels as the given client
void    Server::reply_all_on_channel(const std::string msg, const Client& client)
{
    std::vector<Channel*> channels = client.getChannels();
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        std::set<Client*> members = (*it)->getMembers();
        for (std::set<Client*>::iterator member = members.begin(); member != members.end(); ++member)
        {
            if (*member != &client)
                if (write((*member)->get_fd(), msg.c_str(), msg.size()) < 0)
                    std::cerr << "Failed to send message to client\n";
        }
    }
}