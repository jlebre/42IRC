# 42IRC
This project is about creating an IRC server.
\
Using HexChat (an actual IRC client) to connect to the server and test it.

Internet is ruled by solid standards protocols that allow connected computers to interact with each other.
\
It’s always a good thing to know.

[Intro](#intro)

[Setup](#setup)

[Epoll](#epoll)

[Classes](#classes)

[ReplyCodes](#irc-numeric-reply-codes)

## Intro

### What is an IRC
### What is IRC?
Internet Relay Chat (IRC) is a protocol for real-time text communication over the internet. It facilitates group (many-to-many) communication in discussion forums called channels, as well as one-on-one (private) messaging.

### Key Features
1. **Channels**: These are chat rooms that can be joined by multiple users. Channels are usually prefixed with a `#` (e.g., `#example`).
2. **Private Messaging**: Users can send direct messages to each other.
3. **Nicknames**: Users identify themselves with unique nicknames.
4. **Servers and Networks**: IRC operates on a client-server model where users connect to an IRC server, which may be part of a larger network of servers.

## Setup

Install HexChat
Setup HexChat

```
git clone https://www.github.com/jlebre/42IRC.git
cd 42IRC/ft_irc
make a
```

"make a" deletes all files, compiles the program, and runs it in port 6667 and using "hello" as password.

#

## Allowed functions description

**socket:** This function creates a new socket of a specified type,
such as a stream socket or a datagram socket, and returns a
file descriptor for that socket.


**close:** The `close` function is used to close a file descriptor, 
including those associated with sockets.


**setsockopt:** This function sets options associated with a socket options 
could include things like timeout values, buffer sizes, or socket behavior.


**getsockname:** This function retrieves the local address of a socket,
which is assigned to it by the operating system when the socket
is created or bound.


**getprotobyname:** This function retrieves protocol information
associated with a given protocol name, such as "tcp" or "udp".


**gethostbyname:** This function retrieves host information corresponding
to a given hostname, such as IP address.


**getaddrinfo:** This function provides a protocol-independent way to
get address information, such as IP address and port number,
for a given hostname and service.


**freeaddrinfo:** This function frees memory allocated by `getaddrinfo`
when it's no longer needed.


**bind:** The `bind` function associates a socket with a specific address
(IP address and port number) on the local machine.


**connect:** This function is used by a client to establish a connection
to a remote server using a specified socket.


**listen:** This function marks a socket as passive, indicating that it 
will be used to accept incoming connection requests.


**accept:** This function is called on a listening socket to accept
a new incoming connection, creating a new socket for 
communication with the client.


**htons:** This function converts a 16-bit unsigned integer from host 
byte order to network byte order (short).


**htonl:** Similar to `htons`, but for 32-bit unsigned integers (long).


**ntohs:** This function converts a 16-bit unsigned integer from network 
byte order to host byte order.


**ntohl:** Similar to `ntohs`, but for 32-bit unsigned integers.


**inet_addr:** This function converts a string representing an
IPv4 address into a binary form (32-bit integer).


**inet_ntoa:** This function converts an IPv4 address in binary form
to a string representation.


**send:** This function sends data over a connected socket.


**recv:** This function receives data from a connected socket.


**signal:** This function sets a signal handler for a specific signal,
allowing the program to respond to signals such as interrupts or
termination requests.


**sigaction:** Similar to `signal`, but provides more control over signal
handling behavior.


**lseek:** This function changes the current file offset of an open file.


**fstat:** This function retrieves information about an open file,
such as file size, permissions, and type.


**fcntl:** This function performs various operations on openfile descriptors,
such as duplicating descriptors or changing their properties.


**poll:** This function waits for events on a set of file descriptors,
allowing a program to multiplex I/O operations.

## Step by step

The main function:
```cpp
int main(int argc, char **argv)
{
	Server irc;
	irc.parse(argc, argv);
	return 0;
}
```
This function creates a Server object and sends the arguments to parse.

```cpp
void    Server::parse(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return;
	}
    _sock.port = std::atoi(argv[1]);
    if (_sock.port < 1024)
        std::cerr << "Port should be a number between 1024 and 65534\n";
    _password = argv[2];
    _sock.ip = "127.0.0.1";
    _max_clients = MAX_CLIENTS;
    n_events = 1;
    init_socket();
    init_poll();
	main_loop();
}
```

Here we check wether the number of arguments is correct, we attribute values to _sock.port and to _password.

Then we init the socket.

What is a Socket?

A socket is one endpoint of a two way communication link between two programs running on the network. The socket mechanism provides a means of inter-process communication (IPC) by establishing named contact points between which the communication take place. 


Function call:

**Socket()** -> To create a socket.

**Bind()** -> It is a socket identification like a telephone number to contact.

**Listen()** -> Ready to recieve a connection.

**Connect()** -> Ready to act as a sender.

**Accept()** -> Confirmation, it is like accepting to recieve a call from a sender.

**Write()** -> To send data.

**Read()** -> To recieve data.

**Close()** -> To close a connection.

```cpp
void Server::init_socket()
{
	// CREATE SOCKET
	_sock.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
	if (_sock.fd == -1)
	{
		std::cerr << "Error: (Create Socket) " << std::strerror(errno) << std::endl;
		exit(1);
	}

	// BIND SOCKET
	struct sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr(_sock.ip.c_str());
	_addr.sin_port = htons(_sock.port);

	if (bind(_sock.fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
	{
		std::cerr << "Error: (Bind) " << std::strerror(errno) << std::endl;
		exit(1);
	}

	// LISTEN SOCKET
	if (listen(_sock.fd, _max_clients) == -1)
	{
		std::cerr << "Error: (Listen) " << std::strerror(errno) << std::endl;
		exit(1);
	}
	std::cout << "Listening on " << _sock.fd << std::endl;
}
```

#

## EPOLL
Similar to poll(), but it is more efficient in handling a large number of fds.

### Functions
1. int epoll_create1(int flags):
\
Create an epoll instance and returns the file descriptor referring to that instance.

2. int epoll_ctl(int epfd, int option, int fd, struct epoll_event *event):
\
Manages the list of file descriptors that the epoll instance should monitor.
    "option" can be EPOLL_CTL_ADD, EPOLL_CTL_MOD, EPOLL_CTL_DEL.

```
**EPOLL_CTL_ADD:**
Add an entry to the interest list of the epoll file
descriptor, epfd.  The entry includes the file descriptor,
fd, a reference to the corresponding open file description.

**EPOLL_CTL_MOD:**
Change the settings associated with fd in the interest
list to the new settings specified in event.

**EPOLL_CTL_DEL:**
Remove (deregister) the target file descriptor fd from the
interest list.  The event argument is ignored and can be
NULL (but see BUGS below).
```

3. int epoll_wait(int epfd, struct epoll_event *events, int max_events, int timeout):
\
Waits for events on the epoll instance.

```cpp
void	Server::init_poll()
{
	_event.events = EPOLLIN | EPOLLOUT;
	_event.data.fd = _sock.fd;
	_events[0].data.fd = _sock.fd;

	event_fd = epoll_create1(0);

	epoll_ctl(event_fd, EPOLL_CTL_ADD, _sock.fd, &_event);

	memset(&_events, 0, sizeof(_events));
}
```
```
**EPOLLIN:**
Available for read operations.

**EPOLLOUT:**
Available for write operations.
```

#

# Classes
## Server Class

To send a message to the client we use the function reply, that takes as parameters the address of the client and the message to be sent.

```cpp
void   Server::reply(Client *client, std::string msg)
{
    msg += "\r\n";
    send(client->get_fd(), msg.c_str(), msg.length(), 0);
}
```

## Client Class

## Channel Class
A channel is a named group of one or more clients which will all receive messages addressed to that channel.
The channel is created implicitly when the first client joins it, and the channel ceases to exist when the last client leaves it.
While channel exists, any client can reference the channel using the name of the channel.


Channels names are strings (beginning with a '&' or '#' character) of length up to 200 characters.
Apart from the the requirement that the first character being either '&' or '#'; the only restriction on a channel name is that it may not contain any spaces (' '), a control G (^G or ASCII 7), or a comma (',' which is used as a list item separator by the protocol).

#

## Commands

The protocol for each command will follow the same principles almost everytime.

First, check to see if the Client is registered.
If not, send reply 451.

Second, separate the the command.

Third, apply the changes to all members.

1. INVITE:
   - Purpose: Invites a user to a specific channel.
   - Server Considerations: Check if the user issuing the command has the necessary privileges to invite others to the channel. Verify if the channel exists and if the invited user is allowed to join.
   - Usage: `/invite <nick> <#channel>`
   - Server-to-Client Message: `:server_name INVITE invited_user :channel_name`

2. JOIN:
   - Purpose: Joins a user to a specific channel.
   - Server Considerations: Check if the channel exists and if the user has the necessary permissions to join. Notify other users in the channel about the new user.
   - Usage:``/join <#channel>``
   - Server-to-Client Message: `:user!user@host JOIN :#channel`

3. KICK:
   - Purpose: Removes a user from a channel.
   - Server Considerations: Verify if the user issuing the kick command has the necessary privileges. Notify the kicked user and the channel about the action.
   - Usage:`/kick <#channel> <nick> [<reason>]`
   - Server-to-Client Message: `:server_name KICK channel_name kicked_user :reason`

4. MODE:
   - Purpose: Sets modes (e.g., user modes or channel modes).
   - Server Considerations: Validate the mode changes requested by the user. Update the mode settings accordingly.
   - Usage:`/mode <#channel> <mode> [<mode params>]`
   - Server-to-Client Message: `:server_name MODE target parameters`

5. NICK:
   - Purpose: Changes a user's nickname.
   - Server Considerations: Check if the new nickname is valid and not already in use. Notify other users about the nickname change. Nickname can have a maximum length of nine characters.
   - Usage:`/nick <newnick>`
   - Server-to-Client Message: `:old_nick NICK new_nick`

6. PART:
   - Purpose: Removes a user from a channel.
   - Server Considerations: Verify if the user is in the specified channel and handle the removal accordingly.
   - Usage:`/part <#channel> [<message>]`
   - Server-to-Client Message: `:user!user@host PART #channel`

7. PASS:
   - Purpose: Sets a password for connection.
   - Server Considerations: Authenticate users based on the provided password.
   - Usage:`/pass <password>`
   - Server-to-Client Message: Not typically used for server-to-client communication.

8. PRIVMSG:
   - Purpose: Sends a private message to a user or a message to a channel.
   - Server Considerations: Deliver the message to the intended recipient(s) based on the target specified.
   - Usage:`/privmsg <target> <message>`
   - Server-to-Client Message: `:sender PRIVMSG target :message_text`

9. QUIT:
   - Purpose: Disconnects a user from the IRC server.
   - Server Considerations: Handle the disconnection gracefully and notify other users about the quit message.
   - Usage:`/quit [<message>]`
   - Server-to-Client Message: `:user!user@host QUIT :Quit message`

10. TOPIC:
   - Purpose: Sets or retrieves the topic of a channel.
   - Server Considerations: Validate the topic change and notify users in the channel about the new topic.
   - Usage:`/topic <#channel> [<newtopic>]`
   - Server-to-Client Message: `:server_name TOPIC #channel :new_topic`

11. USER:
   - Purpose: Registers a new user with the server.
   - Server Considerations: Authenticate the user and set initial user attributes.
   - Usage:`/user <username> <hostname> <servername> <realname>`
   - Server-to-Client Message: Not typically used for server-to-client communication.

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

#

### Usefull links and files

[IRC_Chat_Protocol](https://datatracker.ietf.org/doc/html/rfc1459)

[IRC_Client_Protocol](https://datatracker.ietf.org/doc/html/rfc2812)

[IRC_Server_Protocol](https://datatracker.ietf.org/doc/html/rfc2813)

#

jlebre