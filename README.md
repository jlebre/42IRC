# 42IRC
This project is about creating an IRC server.

Using HexChat (an actual IRC client) to connect to the server and test it.

Internet is ruled by solid standards protocols that allow connected computers to interact with each other.

It’s always a good thing to know.

## Setup

## What is an IRC

#

## Step by step
### Setup Server Socket

## Classes
### Server Class
```cpp
#ifndef SERVER_HPP
# define SERVER_HPP

# include "../Client/client.hpp"
# include "../Commands/commands.hpp"
# include "../Channel/channel.hpp"
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

```

## IRC Numeric Reply Codes
```
Initial Replies (001-005):
- 001 RPL_WELCOME: Welcome message. Indicates that the client has successfully connected to the server.
- 002 RPL_YOURHOST: Information about the server's hostname and version.
- 003 RPL_CREATED: Indicates when the server was created.
- 004 RPL_MYINFO: Information about the server's features and supported user modes.
- 005 RPL_ISUPPORT: Provides various support information, such as supported user modes, channel modes, and other capabilities.

Reply Codes (200-399):
- 201 RPL_TRACECONNECTING: Indicates the server is attempting to connect to another server.
- 211 RPL_STATSQLINE: Statistical information about a server's connections.
- 212 RPL_STATSLINKINFO: Statistical information about a server's connection to another server.
- 213 RPL_STATSCOMMANDS: Statistical information about server commands usage.
- 214 RPL_STATSCLINE: Statistical information about client connections.
- 215 RPL_STATSNLINE: Statistical information about server connections.
- 219 RPL_ENDOFSTATS: End of statistics output.
- 221 RPL_UMODEIS: Information about the user's mode settings.
- 222 RPL_SQLINE_NICK: SQLINE status reply.
- 223 RPL_STATSILINE: Information about an IP address match in a user mask.
- 224 RPL_STATSKLINE: Information about a server connection's mask.
- 225 RPL_STATSYLINE: Information about server Y-lines (connecting servers).
- 226 RPL_STATSCONN: Information about a connection class.
- 231 RPL_SERVICEINFO: Information about a service.
- 232 RPL_ENDOFSERVICES: End of service listing.
- 233 RPL_SERVICE: A service entry.
- 234 RPL_SERVLIST: Indicates the start of service listing.
- 235 RPL_SERVLISTEND: Indicates the end of service listing.
- 241 RPL_STATSLLINE: Information about L-line status.
- 242 RPL_STATSUPTIME: Server uptime information.
- 243 RPL_STATSOLINE: Information about O-line status.
- 244 RPL_STATSHLINE: Information about H-line status.
- 251 RPL_LUSERCLIENT: Information about the number of clients and servers connected to the network.
- 252 RPL_LUSEROP: Information about the number of operators online.
- 253 RPL_LUSERUNKNOWN: Information about the number of unknown connections.
- 254 RPL_LUSERCHANNELS: Information about the number of channels formed.
- 255 RPL_LUSERME: Information about the number of clients connected to the server.
- 256 RPL_ADMINME: Information about the server's administrative information.
- 257 RPL_ADMINLOC1: Administrative location information (1).
- 258 RPL_ADMINLOC2: Administrative location information (2).
- 259 RPL_ADMINEMAIL: Administrative contact email.
- 301 RPL_AWAY: Indicates that a user is away and provides a message indicating their absence.
- 302 RPL_USERHOST: Response to the USERHOST command, providing information about the requested users' hostnames.
- 303 RPL_ISON: Response to the ISON command, indicating which of the specified users are online.
- 305 RPL_UNAWAY: Indicates that the user is no longer marked as away.
- 306 RPL_NOWAWAY: Indicates that the user is now marked as away.
- 311 RPL_WHOISUSER: Information about a user's username, hostname, real name, and server.
- 312 RPL_WHOISSERVER: Information about the server a user is connected to.
- 313 RPL_WHOISOPERATOR: Indicates if a user is an IRC operator.
- 314 RPL_WHOWASUSER: Response to the WHOWAS command, providing information about a previously connected user.
- 315 RPL_ENDOFWHO: Indicates the end of a WHO list.
- 317 RPL_WHOISIDLE: Indicates how long a user has been idle.
- 318 RPL_ENDOFWHOIS: Indicates the end of a WHOIS list.
- 319 RPL_WHOISCHANNELS: Indicates which channels a user is currently in.
- 321 RPL_LISTSTART: Indicates the start of the list of channels.
- 322 RPL_LIST: Provides information about a channel, including the number of users and the topic.
- 323 RPL_LISTEND: Indicates the end of the list of channels.
- 324 RPL_CHANNELMODEIS: Provides the mode of a channel.
- 325 RPL_UNIQOPIS: Indicates the nickname of a unique channel operator.
- 331 RPL_NOTOPIC: Indicates that a channel has no topic set.
- 332 RPL_TOPIC: Provides the topic of a channel.
- 341 RPL_INVITING: Indicates that an invitation has been sent to a user to join a channel.
- 342 RPL_SUMMONING: Indicates that the server is attempting to summon a user.
- 346 RPL_INVITELIST: Provides a list of invitees for a channel.
- 347 RPL_ENDOFINVITELIST: Indicates the end of the invite list for a channel.
- 348 RPL_EXCEPTLIST: Provides a list of exceptions for a channel.
- 349 RPL_ENDOFEXCEPTLIST: Indicates the end of the exception list for a channel.

Error Replies (400-599):
- 401 ERR_NOSUCHNICK: No such nickname exists.
- 402 ERR_NOSUCHSERVER: No such server exists.
- 403 ERR_NOSUCHCHANNEL: No such channel exists.
- 404 ERR_CANNOTSENDTOCHAN: Cannot send to channel (e.g., user is banned or the channel is moderated).
- 405 ERR_TOOMANYCHANNELS: Too many channels, cannot join another.
- 406 ERR_WASNOSUCHNICK: A nickname is given that was not recognized.
- 407 ERR_TOOMANYTARGETS: Too many targets (e.g., recipients) for the given command.
- 409 ERR_NOORIGIN: No origin specified.
- 411 ERR_NORECIPIENT: No recipient specified.
- 412 ERR_NOTEXTTOSEND: No text to send.
- 413 ERR_NOTOPLEVEL: No toplevel specified.
- 414 ERR_WILDTOPLEVEL: Wildcard in toplevel domain.
- 421 ERR_UNKNOWNCOMMAND: Unknown command.
- 422 ERR_NOMOTD: MOTD (Message of the Day) file is missing.
- 431 ERR_NONICKNAMEGIVEN: No nickname given.
- 432 ERR_ERRONEUSNICKNAME: Erroneous nickname.
- 433 ERR_NICKNAMEINUSE: Nickname is already in use.
- 436 ERR_NICKCOLLISION: Nickname collision.
- 441 ERR_USERNOTINCHANNEL: User is not in channel.
- 442 ERR_NOTONCHANNEL: Not currently on the channel.
- 443 ERR_USERONCHANNEL: User already on channel.
- 444 ERR_NOLOGIN: User not logged in.
- 445 ERR_SUMMONDISABLED: SUMMON command disabled.
- 446 ERR_USERSDISABLED: USERS command disabled.
- 451 ERR_NOTREGISTERED: Not registered.
- 461 ERR_NEEDMOREPARAMS: Not enough parameters.
- 462 ERR_ALREADYREGISTERED: Already registered.
- 463 ERR_NOPERMFORHOST: No permission for host.
- 464 ERR_PASSWDMISMATCH: Password mismatch.
- 465 ERR_YOUREBANNEDCREEP: You are banned from this server.
- 467 ERR_KEYSET: Channel key already set.
- 471 ERR_CHANNELISFULL: Channel is full.
- 472 ERR_UNKNOWNMODE: Unknown mode.
- 473 ERR_INVITEONLYCHAN: Invite only channel.
- 474 ERR_BANNEDFROMCHAN: Banned from channel.
- 475 ERR_BADCHANNELKEY: Bad channel key.
- 481 ERR_NOPRIVILEGES: Insufficient privileges.
- 482 ERR_CHANOPRIVSNEEDED: Channel operator privileges needed.
- 483 ERR_CANTKILLSERVER: Cannot kill server connection.
- 491 ERR_NOOPERHOST: No operator/host mask supplied.
- 501 ERR_UMODEUNKNOWNFLAG: Unknown MODE flag.
- 502 ERR_USERSDONTMATCH: Cannot change mode for other users.
```