#include "server.hpp"

void		Server::privmsg(Client& client)
{
    (void)client;
    std::cout << "PRIVMSG COMMAND\n";
}
