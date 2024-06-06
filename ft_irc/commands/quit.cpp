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
    client.setStatus(false);
    std::cout << "Client " << client.getNick() << " has quit\n";
    std::string msg = (":" + client.getNick() + " QUIT : " + leave_message(parsed_message, 1));
    reply_all(msg);
} 
