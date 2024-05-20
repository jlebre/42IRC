#include "server.hpp"

void		Server::invite(Client& client)
{
    (void)client;
    std::cout << "INVITE COMMAND\n";
    //std::string msg = ":" + client.getNick() + " INVITE " + __invitedNick__ + " :" + channel_name; 
}
