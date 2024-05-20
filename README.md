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
Internet Relay Chat

## Setup
```
git clone https://www.github.com/jlebre/42IRC.git
cd 42IRC/ft_irc
make a
```

"make a" deletes all files, compiles the program, and runs it in port 6667 and using "hello" as password.

#

## Step by step
### Setup Server Socket

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
EPOLL_CTL_ADD:
Add an entry to the interest list of the epoll file
descriptor, epfd.  The entry includes the file descriptor,
fd, a reference to the corresponding open file description.

EPOLL_CTL_MOD:
Change the settings associated with fd in the interest
list to the new settings specified in event.

EPOLL_CTL_DEL:
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
EPOLLIN:
Available for read operations.

EPOLLOUT:
Available for write operations.
```

#

# Classes
## Server Class

To send a message to the client we use the function reply, that takes as parameters the address of the client and the message to be sent.

```cpp
void   Server::reply(Client &client, std::string msg)
{
    msg += "\r\n";
    send(client.get_fd(), msg.c_str(), msg.length(), 0);
}
```

## Client Class

## Channel Class

#

## Commands

The protocol for each command will follow the same principles almost everytime.

First, check to see if the Client is registered.
If not, send reply 451.

Second, separate the the command.

Third, apply the changes to all members.

### Invite
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " INVITE " + invitedNick + " :" + channel_name;  
```

### Join
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " JOIN " + channel_name;  
```

### Kick
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " KICK " + channel_name + " " + clientToKickNick + " :" + reason;  
```

### Mode
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " MODE " + channel_name + " " + mode;  

```

### Nick
Message sent to the client:
```cpp
std::string msg = ":" + oldNick + " NICK :" + newNick;  
```

### Part
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " PART " + channel_name + " :" + reason;  
```

### Pass
Message sent to the client:
```cpp
std::string msg = "PASS " + password;  
```

### Privmsg
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " PRIVMSG " + target + " :" + message;  
```

### Quit
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " QUIT :" + reason;  
```

### Topic
Message sent to the client:
```cpp
std::string msg = ":" + clientNick + " TOPIC " + channel_name + " :" + topic;  
```

### User
Message sent to the client:
```cpp
std::string msg = "USER " + username + " 0 * :" + realname;  
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