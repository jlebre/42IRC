#include "server.hpp"

/*
Usage:
/part <#channel> [reason]

Message to Client:
:<nick> PART <channel> [:<reason>]
*/

void		Server::part(Client& client)
{
    (void)client;
    std::cout << "PART COMMAND\n";

    //client.removeChannel(channel);
    
    //client.getNick()
    //std::string msg = ":" + clientNick + " PART " + channel_name + " :" + reason; 
}
