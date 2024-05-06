#include "server.hpp"

void		Server::quit(Client& client)
{
    (void)client;
    std::cout << "QUIT COMMAND\n";
}
