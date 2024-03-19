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

void	IRCServer::client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
	{
		if ((e->fds[i].type == 2) &&
			(i != cs))
		send(i, e->fds[cs].buf_read, r, 0);
		i++;
	}
	}
}

void	IRCServer::client_write(t_env *e, int cs)
{
	(void)e;
	(void)cs;
}

