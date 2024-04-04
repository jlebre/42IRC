#ifndef SERVER_HPP
# define SERVER_HPP

# include "structs.hpp"

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
		void	createsocket(t_env *e);
		void	main_loop(t_env *e);
		void	handleClient(t_env *e, int i);
		void    check_clients(t_env *e);
		int     parser(t_env *e, int argc, char **argv);
		void	build_fd_set(t_env *e);
		void	process_input(t_env *e);
		void	check_fd_set(t_env *e);
		void	clean_fd(t_fd *fd);
		int 	ft_max(int a, int b);
		void	client_read(t_env *e, int cs);
		void	client_write(t_env *e, int cs);
		void	reading(t_env *e);

	private:
		t_env   e;
		struct sockaddr_in _addr;
		int		_buf[BUF_SIZE];
};

#endif

//int poll(struct pollfd *fds, nfds_t nfds, int timeout);
