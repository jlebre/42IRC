#include "server.hpp"

void	IRCServer::build_fd_set(t_env *e)
{
	e->max = 0;
	// READ
	FD_ZERO(&e->fd_read);
	FD_SET(STDIN_FILENO, &e->fd_read);
	FD_SET(e->sock, &e->fd_read);
	
	// WRITE
	FD_ZERO(&e->fd_write);
	FD_SET(e->sock, &e->fd_write);
	for (int i = 0 ; i < e->maxfd ; i++ )
	{
		FD_SET(e->fds[i].type, &e->fd_read);
		FD_SET(e->fds[i].type, &e->fd_write);
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


/*
for (int i = 0 ; i < e->maxfd ; i++ )
{
	FD_SET(i, &e->fd_read);
	if (e->fds[i].type != 0)
	{
		std::cout << "Entered if\n";
		FD_SET(i, &e->fd_read);
		std::cout << "Entered if FDSET\n";
		if (strlen(e->fds[i].buf_write) > 0)
			FD_SET(i, &e->fd_write);
		std::cout << "Entered if after if\n";
		e->max = ft_max(e->max, i);
		std::cout << "Entered if set Max\n";
	}
}
	*/