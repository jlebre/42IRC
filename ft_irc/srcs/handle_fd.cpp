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
		if (e->fds[i].type != 0)
		{
			FD_SET(i, &e->fd_read);
			if (strlen(e->fds[i].buf_write) > 0)
				FD_SET(i, &e->fd_write);
			e->max = ft_max(e->max, i);
		}
		i++;
	}
}

void	IRCServer::check_fd_set(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		/*
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) ||
			FD_ISSET(i, &e->fd_write))
		*/
		e->r--;
		i++;
	}
}

void	IRCServer::clean_fd(t_fd *fd)
{
	fd->type = 0;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
}
