#include "server.hpp"

/*
Usage:
/quit [<message>]

Message to Client:
:<nick> QUIT :<message>
*/

void		Server::quit(Client& client)
{
    std::cout << "QUIT COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }

    std::string reason = "";
    size_t i = _message.find(":");
    if (i != std::string::npos)
        reason = _message.substr(i + 1);
    client.setStatus(false);
    std::cout << "Client " << client.getNick() << " has quit\n";
    reply_all_on_channel(":" + client.getNick() + " QUIT : " + reason, client);
} 
