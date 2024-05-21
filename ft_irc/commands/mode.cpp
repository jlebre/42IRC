#include "server.hpp"

/*
Usage:
/mode <#channel> <mode> [<mode params>]

Message to Client:
:<nick> MODE <channel> <mode> [<mode params>]
*/

void		Server::mode(Client& client)
{
    (void)client;
    std::cout << "MODE COMMAND\n";
    //std::string msg = ":" + clientNick + " MODE " + channel_name + " " + mode; 
    //client.getNick()
}
