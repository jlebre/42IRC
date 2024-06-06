#ifndef SERVER_HPP
# define SERVER_HPP

# include "../Client/client.hpp"
# include "../commands/commands.hpp"
# include "../Channel/channel.hpp"
# include "../includes/replies.hpp"
# include "../includes/libs.hpp"

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
		int							_max_clients;
		char						_buf[BUF_SIZE];
		std::string					_password;
		std::vector<std::string>	parsed_message;
		std::string					_message;
		
		std::string					_line;
		std::map<int, Client*>		_clients;

		// SOCKET
		socket_t 				_sock;

		// POLL
		int						event_fd;
		int						n_events;
		struct epoll_event		_events[200];
		struct epoll_event		_event;

		// CHANNELS
		std::vector<Channel*>	_channels;

	public:
		Server();
		Server(const Server &src);
		Server &operator=(const Server &src);
		~Server();

		//SERVER
		void					parse(int argc, char **argv);
		void					main_loop();
		void					connect_client();
		void					reading(Client& cli);
		void					process_input(Client& cli);
		int	    				check_command(std::string line);

		// REPLY
		void    				reply(Client &client, std::string msg);
		void    				reply_all(std::string msg);
		void    				reply_on_channel(std::string msg, Channel &channel, Client &client);
		void    				reply_all_on_channel(std::string msg, Client& client);

		// CHECK
		bool					check_pass(std::string pass);
		bool					check_nickname(std::string nickname);
		bool					check_on_server(std::string nick, std::string channel);
		bool					check_on_channel(std::string nick);
		bool					check_client_on_channel(std::string nick, std::string channel_name);
		bool 					check_if_channel_exists(std::string name);
		
		// PARSE
		void					parse_mode(std::string &channel_name, std::string &mode);
		void					parse_invite(std::string &invited_nick, std::string &channel_name);
		void        			parse_topic(std::string &channel_name, std::string &new_topic);
		void					parse_pass(std::string &password);
		void    				parse_nick(std::string &nickname);
		void    				parse_user(std::string &user, std::string &real);
		void 					ParseCommand();
		
		// FIND
		Channel					&find_channel(std::string channel_name);
		Client					&find_client(std::string nick);

		// SOCK
		void					init_socket();
        std::string 			read();
        int     				get_fd();

		// POLL
		void					init_poll();

		// COMMANDS
		void					pass(Client& client);
		void					nick(Client& client);
		void					user(Client& client);
		void					join(Client& client);
		void					part(Client& client);
		void					quit(Client& client);
		void					privmsg(Client& client);
		void					mode(Client& client);
		void					topic(Client& client);
		void					kick(Client& client);
		void					invite(Client& client);
};

std::string leave_message(std::vector<std::string> tmp, int it);

#endif
