#include "server.hpp"

void		Server::quit(Client& client)
{
    std::cout << "QUIT COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, "451 :You are not registered");
        return ;
    }

    std::string reason = "";
    size_t i = _message.find(":");
    if (i != std::string::npos)
        reason = _message.substr(i + 1);
    client.setStatus(false);
    std::cout << "Client " << client.getNick() << " has quit\n";
    reply(client, ":" + client.getNick() + " ERROR : " + reason + "\r\n");
    //client.getNick()
} 
