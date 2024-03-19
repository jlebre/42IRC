#include "server.hpp"

void    IRCServer::check_clients(t_env *e)
{
	std::cout << "Waiting for client..." << std::endl;
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(addr);

	memset(&addr, 0, sizeof(addr));
	e->client->fd = accept(e->sock, (struct sockaddr *)&addr, &addr_size);
	if (e->client->fd)
		handleClient(e);
}

void    IRCServer::handleClient(t_env *e)
{
	std::cout << "Client #" << e->client->fd << " connected!\n";
	e->client->id = _id++;
}
