#include "server.hpp"

void		Server::privmsg(Client& client)
{
    std::cout << "PRIVMSG COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, "451 :You are not registered");
        return ;
    }

    std::string msg;
    msg = _message.find(":");
    
        
    
    // Get the message

    // If it is on channel send message to everyone on channel

    // If it is not, send error
}
