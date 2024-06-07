#include "server.hpp"

void		Server::quit(Client& client)
{
    std::cout << "QUIT COMMAND\n";
    if (!client.getRegistered())
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }
    client.setStatus(false);
    delete_client(client.getNick());
    std::cout << "Client " << client.getNick() << " has quit\n";
    reply_all(":" + client.getNick() + " QUIT : " + leave_message(parsed_message, 1), client);
} 
