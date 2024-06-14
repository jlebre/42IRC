#ifndef REPLIES_HPP
# define REPLIES_HPP

# define RPL_WELCOME(nick)								    ":localhost 001 " + nick + " :Welcome to the Internet Relay Network, " + nick       
# define RPL_YOURHOST(nick)								    ":localhost 002 " + nick + " :Your host is localhost running version 0.1"	
# define RPL_CREATED(nick)								    ":localhost 003 " + nick + " :This server was created on fri Jun 14 2024"		
# define RPL_MYINFO(nick)								    ":localhost 004 " + nick + " :localhost 0.1"								

// REPLIES
# define RPL_CHANNELMODEIS(nick, channel, modes)			":localhost 324 " + nick + " "	+ channel + " " + modes
# define RPL_NOTOPIC(nick, channel)						    ":localhost 332 " + nick + " "	+ channel + " :No topic is set"
# define RPL_TOPIC(nick, channel, topic)					":localhost 332 " + nick + " "	+ channel + " :" + topic
# define RPL_INVITING(nick, invited, channel)			    ":" + nick + " INVITING " + invited + " " + channel	
# define RPL_NAMREPLY(nick, channel, list)				    ":localhost 353 " + nick + " = " + channel + " :" + list
# define NOUSER	                                            "FT_IRC Network: That user doesn't exist"
# define RPL_ENDOFNAMES(nick, channel)					    ":localhost 366 " + nick + " " + channel + " :End of /NAMES list."	
# define JOIN_REPLY(nick, user, channel)				    ":" + nick + "!" + user + "@localhost JOIN :" + channel

// ERRORS
# define ERR_NOSUCHNICK(client, nickname)					(":localhost 401 " + client + nickname + " :No such nick/channel")									
# define ERR_NOSUCHCHANNEL(client, channel)					(":localhost 403 " + client + " " + channel + " :No such channel")									
# define ERR_NONICKNAMEGIVEN(client)						(":localhost 431 " + client + " :No nickname given")												
# define ERR_ERRONEUSNICKNAME(client, nickname)				(":localhost 432 " + client + " " + nickname + " :Erroneus nickname")								
# define ERR_NICKNAMEINUSE(client, nickname)				(":localhost 433 " + client + " " + nickname + " :Nickname is already in use")						
# define ERR_USERNOTINCHANNEL(client, nickname, channel)	(":localhost 441 " + client + " " + nickname + " " + channel + " :That user is not on that channel")
# define ERR_NOTONCHANNEL(client, channel)					(":localhost 442 " + client + " " + channel + " :You're not on that channel")						
# define ERR_USERONCHANNEL(client, nickname, channel)		(":localhost 443 " + client + " " + nickname + " " + channel + " :is already on channel")			
# define ERR_NOTREGISTERED(nickname)						(":localhost 451 " + nickname + " :You have not registered")										
# define ERR_NEEDMOREPARAMS(channel, nick, command)			(":localhost 461 " + nick + " " + channel + " " + command + " :Not enough parameters")				
# define ERR_ALREADYREGISTERED(client)						(":localhost 462 " + client + " :You may not reregister")											
# define ERR_PASSWDMISMATCH(client)							(":localhost 464 " + client + " :Password incorrect")												
# define ERR_CHANNELISFULL(client, channel) 				(":localhost 471 " + client + " " + channel + " :Cannot join channel (+l)")							
# define ERR_INVITEONLYCHAN(client, channel) 				(":localhost 473 " + client + " " + channel + " :Cannot join channel (+i)")							
# define ERR_BADCHANNELKEY(client, channel)					(":localhost 475 " + client + " " + channel + " :Password incorrect")								
# define ERR_CHANOPRIVSNEEDED(client, channel)				(":localhost 482 " + client + " " + channel + " :You're not channel operator")						
# define ERR_UMODEUNKNOWNFLAG(client)						(":localhost 501 " + client + " :Unknown MODE flag")												

#endif