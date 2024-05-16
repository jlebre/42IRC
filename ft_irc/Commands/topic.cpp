#include "server.hpp"


// It has to change to all users

void		Server::topic(Client& client)
{
    (void)client;
    std::cout << "TOPIC COMMAND\n";
}
