#include "server.hpp"

void    IRCServer::check_clients(t_env *e)
{
	int i;
	std::cout << "Waiting for client..." << std::endl;
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(addr);

	memset(&addr, 0, sizeof(addr));
	i = accept(e->sock, (struct sockaddr *)&addr, &addr_size);
	if (i)
		handleClient(e, i);
}

void    IRCServer::handleClient(t_env *e, int i)
{
	(void)e;
	std::cout << "Client #" << i << " connected!\n";
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

