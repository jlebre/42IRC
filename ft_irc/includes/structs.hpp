#ifndef STRUCTS_HPP
# define STRUCTS_HPP

# include "libs.hpp"

typedef struct s_vars
{
	std::string password;
}   t_vars;

// As of bircd:
typedef struct	s_fd
{
	int	type;
	void	(*fct_read)();
	void	(*fct_write)();
	char	buf_read[BUF_SIZE + 1];
	char	buf_write[BUF_SIZE + 1];
}		t_fd;

typedef struct s_client
{
	int			id;
	int			fd;
	int			buf[BUF_SIZE + 1];
	std::string	nick;
	std::string	username;
	std::string	realname;
	std::string	password;
}		t_client;

typedef struct	s_env
{
	t_fd		*fds;
	t_client	*client;
	int		port;
	int		sock;
	int		maxfd;
	int		max;
	int		r;
	int		out;
	char	buf[BUF_SIZE + 1];
	fd_set	fd_read;
	fd_set	fd_write;
	t_vars	vars;
}		t_env;

#endif