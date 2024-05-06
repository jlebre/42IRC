#ifndef SERVER_HPP
# define SERVER_HPP

# include "../Client/client.hpp"
# include "../Commands/commands.hpp"
# include "../Channel/channel.hpp"
# include "../includes/libs.hpp"
# include "../includes/definitions.hpp"

class Client;
class Channel;
class Command;

typedef struct socket_s
{
    int fd;
    uint16_t port;
    std::string ip;
} socket_t;

class Server
{
	private:
		int					_max_clients;
		char				_buf[BUF_SIZE];
		std::string			_password;
		std::string			_message;
		std::map<int, Client*> _clients;

		// SOCKET
		socket_t _sock;

		// POLL
		int					event_fd;
		int					n_events;
		struct epoll_event	_events[200];
		struct epoll_event	_event;

		// CHANNELS
		std::vector<Channel>	_channels;

	public:
		Server();
		Server(const Server &src);
		Server &operator=(const Server &src);
		~Server();

		//SERVER
		void		parse(int argc, char **argv);
		void		main_loop();
		void		connect_client();
		void		reading(Client& cli);
		void		process_input(Client& cli);
		int	    	check_command(std::string line);
		void    	reply(Client &client, std::string msg);
		void    	reply_all(std::string msg);
		bool		valid_pass(std::string pass);
		bool		check_nickname(std::string nickname);

		// SOCK
		void		init_socket();
        std::string read();
        int     	get_fd();

		// POLL
		void		init_poll();

		// COMMANDS
		void		pass(Client& client);
		void		nick(Client& client);
		void		user(Client& client);
		void		join(Client& client);
		void		part(Client& client);
		void		quit(Client& client);
		void		privmsg(Client& client);
		void		mode(Client& client);
		void		topic(Client& client);
		void		kick(Client& client);
		void		invite(Client& client);
};

#endif

//int poll(struct pollfd *fds, nfds_t nfds, int timeout);
