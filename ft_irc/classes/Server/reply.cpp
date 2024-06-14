#include "server.hpp"

// Reply should be everyone, except for myself
void   Server::reply(Client *client, std::string msg)
{
    msg += "\r\n";
    if (send(client->get_fd(), msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1)
        std::cerr << "Error: Attempting to send data to a disconnected client\n";
}
