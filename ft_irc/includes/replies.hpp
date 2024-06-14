#ifndef REPLIES_HPP
# define REPLIES_HPP

# define NEED_AUTHENTICATION	"FT_IRC Network: Type PASS to enter the servers password\n"
# define RPL_WELCOME(nick)								    ":ircserv.42.fr 001 " + nick + " :Welcome to the Internet Relay Network, " + nick       
# define RPL_YOURHOST(nick)								    ":ircserv.42.fr 002 " + nick + " :Your host is ircserv.42.fr running version 001.1"	
# define RPL_CREATED(nick)								    ":ircserv.42.fr 003 " + nick + " :This server was created on fri Jun 14 2024"		
# define RPL_MYINFO(nick)								    ":ircserv.42.fr 004 " + nick + " :ircserv.42.fr 001.1"								

// REPLIES
# define RPL_CHANNELMODEIS(nick, channel, modes)			":ircserv.42.fr 324 " + nick + " "	+ channel + " " + modes
# define RPL_NOTOPIC(nick, channel)						    ":ircserv.42.fr 332 " + nick + " "	+ channel + " :No topic is set"
# define RPL_TOPIC(nick, channel, topic)					":ircserv.42.fr 332 " + nick + " "	+ channel + " :" + topic
# define RPL_INVITING(nick, invited, channel)			    ":" + nick + " INVITING " + invited + " " + channel	
# define RPL_NAMREPLY(nick, channel, list)				    ":ircserv.42.fr 353 " + nick + " = " + channel + " :" + list
# define NOUSER	                                            "FT_IRC Network: That user doesn't exist"
# define RPL_ENDOFNAMES(nick, channel)					    ":ircserv.42.fr 366 " + nick + " " + channel + " :End of /NAMES list."	
# define JOIN_REPLY(nick, channel)						    ":" + nick + "!" + nick + "@ircserv.42.fr JOIN " + channel

// ERRORS
# define ERR_NOSUCHNICK(client, nickname)					(":ircserv.42.fr 401 " + client + nickname + " :No such nick/channel")									
# define ERR_NOSUCHCHANNEL(client, channel)					(":ircserv.42.fr 403 " + client + " " + channel + " :No such channel")									
# define ERR_NONICKNAMEGIVEN(client)						(":ircserv.42.fr 431 " + client + " :No nickname given")												
# define ERR_ERRONEUSNICKNAME(client, nickname)				(":ircserv.42.fr 432 " + client + " " + nickname + " :Erroneus nickname")								
# define ERR_NICKNAMEINUSE(client, nickname)				(":ircserv.42.fr 433 " + client + " " + nickname + " :Nickname is already in use")						
# define ERR_USERNOTINCHANNEL(client, nickname, channel)	(":ircserv.42.fr 441 " + client + " " + nickname + " " + channel + " :That user is not on that channel")
# define ERR_NOTONCHANNEL(client, channel)					(":ircserv.42.fr 442 " + client + " " + channel + " :You're not on that channel")						
# define ERR_USERONCHANNEL(client, nickname, channel)		(":ircserv.42.fr 443 " + client + " " + nickname + " " + channel + " :is already on channel")			
# define ERR_NOTREGISTERED(nickname)						(":ircserv.42.fr 451 " + nickname + " :You have not registered")										
# define ERR_NEEDMOREPARAMS(channel, nick, command)			(":ircserv.42.fr 461 " + nick + " " + channel + " " + command + " :Not enough parameters")				
# define ERR_ALREADYREGISTERED(client)						(":ircserv.42.fr 462 " + client + " :You may not reregister")											
# define ERR_PASSWDMISMATCH(client)							(":ircserv.42.fr 464 " + client + " :Password incorrect")												
# define ERR_CHANNELISFULL(client, channel) 				(":ircserv.42.fr 471 " + client + " " + channel + " :Cannot join channel (+l)")							
# define ERR_INVITEONLYCHAN(client, channel) 				(":ircserv.42.fr 473 " + client + " " + channel + " :Cannot join channel (+i)")							
# define ERR_BADCHANNELKEY(client, channel)					(":ircserv.42.fr 475 " + client + " " + channel + " :Password incorrect")								
# define ERR_CHANOPRIVSNEEDED(client, channel)				(":ircserv.42.fr 482 " + client + " " + channel + " :You're not channel operator")						
# define ERR_UMODEUNKNOWNFLAG(client)						(":ircserv.42.fr 501 " + client + " :Unknown MODE flag")												

#endif