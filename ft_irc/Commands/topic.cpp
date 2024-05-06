#include "server.hpp"

void		Server::topic(Client& client)
{
    (void)client;
    std::cout << "TOPIC COMMAND\n";
}
