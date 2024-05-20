#include "server.hpp"

/*
Usage:
/privmsg <target> <message>

Message to Client:
:<nick> PRIVMSG <target> :<message>
*/

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
    
        
    //client.getNick()
    //std::string msg = ":" + clientNick + " PRIVMSG " + target + " :" + message;  
    // Get the message

    // If it is on channel send message to everyone on channel

    // If it is not, send error
}
