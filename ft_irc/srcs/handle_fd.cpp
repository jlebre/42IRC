#include "server.hpp"

void	IRCServer::build_fd_set(t_env *e)
{
	int	i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->maxfd)
		{
		if (e->fds[i].type != FD_FREE)
		{
		FD_SET(i, &e->fd_read);
		if (strlen(e->fds[i].buf_write) > 0)
			{
			FD_SET(i, &e->fd_write);
			}
		e->max = MAX(e->max, i);
		}
		i++;
		}
	/*
	// Read
	FD_ZERO(&e->fd_read);
	FD_SET(STDIN_FILENO, &e->fd_read);
	FD_SET(e->sock, &e->fd_read);
	
	// Write
	FD_ZERO(&e->fd_write);
	FD_SET(e->sock, &e->fd_read);
	for (size_t i = 0; e->client[i].id ; ++i)
	{
		FD_SET(e->client[i].fd, &e->fd_read);
	}
	*/
}

void	IRCServer::check_fd_set(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
		e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
		e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) ||
		FD_ISSET(i, &e->fd_write))
		e->r--;
		i++;
	}
}

void	IRCServer::clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
}
