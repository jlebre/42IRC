#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <cstring>
# include <cerrno>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <vector> 
# include <poll.h>
# include <string>
# include <sys/time.h>
	  
# define BUF_SIZE		1024
# define MAX_CLIENTS	100

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

typedef struct	s_env
{
  t_fd		*fds;
  int		port;
  int		maxfd;
  int		max;
  int		r;
  fd_set	fd_read;
  fd_set	fd_write;
  t_vars	vars;
}		t_env;

class IRCServer
{
	public:
		IRCServer();
		~IRCServer();
		void	start(int argc, char **argv);
		void	kick(t_env *e, int fd);
		void	invite(t_env *e, int fd);
		void	topic(t_env *e, std::string topic);
		void	mode(t_env *e, std::string mode, char flag);
		void	create_socket(int port);
		void	main_loop(t_env *e);
		void	handleClient(int client);
		int     parser(t_env *e, int argc, char **argv);

	private:
		t_env   e;
		int		_sock;
		struct sockaddr_in _addr;
		int		_buf[BUF_SIZE];
		std::vector<int> _clients;
};


#endif

//int poll(struct pollfd *fds, nfds_t nfds, int timeout);