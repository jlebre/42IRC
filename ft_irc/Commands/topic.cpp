#include "server.hpp"


// It has to change to all users

void		Server::topic(Client& client)
{
    std::cout << "TOPIC COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, "451 :You are not registered");
        return ;
    }
    ////client.getNick()
}
