#include "server.hpp"

/*
Usage:
/topic <#channel> [<newtopic>]

Message to Client:
:<nick> TOPIC <channel> :<newtopic>
*/


// It has to change to all users

void		Server::topic(Client& client)
{
    std::cout << "TOPIC COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, "451 :You are not registered");
        return ;
    }


    //std::string msg = ":" + clientNick + " TOPIC " + channel_name + " :" + topic;  
    //client.getNick()
}
