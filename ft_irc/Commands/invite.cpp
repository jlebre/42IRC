#include "server.hpp"

/*
Usage:
/invite <nick> <#channel>

Message to Client:
:<nick> INVITE <nick> :<channel>
*/

void		Server::invite(Client& client)
{
    (void)client;
    std::cout << "INVITE COMMAND\n";
    //std::string msg = ":" + client.getNick() + " INVITE " + __invitedNick__ + " :" + channel_name; 
}
