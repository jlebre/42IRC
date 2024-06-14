#include "server.hpp"

// Reply should be everyone, except for myself
void   Server::reply(Client *client, std::string msg)
{
    msg += "\r\n";
    send(client->get_fd(), msg.c_str(), msg.length(), 0);
}
