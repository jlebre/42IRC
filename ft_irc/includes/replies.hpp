#ifndef REPLIES_HPP
# define REPLIES_HPP

# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")

# define RPL_WELCOME(user_id, nickname) (":localhost 001 " + nickname + " :Welcome to the Internet Relay Network " + user_id)
# define RPL_YOURHOST(client, servername, version) (":localhost 002 " + client + " :Your host is " + servername + " (localhost), running version " + version)
# define RPL_CREATED(client, datetime) (":localhost 003 " + client + " :This server was created " + datetime)
# define RPL_MYINFO(client, servername, version, user_modes, chan_modes, chan_param_modes) (":localhost 004 " + client + " " + servername + " " + version + " " + user_modes + " " + chan_modes + " " + chan_param_modes)
# define RPL_ISUPPORT(client, tokens) (":localhost 005 " + client + " " + tokens " :are supported by this server")

# define ERR_NOTREGISTERED(client, command) (":" + client + " 451 " + command + " :You have not registered")
# define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command")

// INVITE
# define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + " :Cannot join channel (+i)")
# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters.")
# define ERR_NOSUCHCHANNEL(client, channel) (":localhost 403 " + client + " " + channel + " :No such channel")
# define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :The user is not on this channel.")
# define ERR_USERONCHANNEL(client, nick, channel) (":localhost 443 " + client + " " + nick + " #" + channel + " :Is already on channel")
# define RPL_INVITING(user_id, client, nick, channel) (user_id + " 341 " + client + " " + nick + " #" + channel)
# define RPL_INVITE(user_id, invited, channel) (user_id + " INVITE " + invited + " " + channel)

// JOIN
# define RPL_JOIN(user_id, channel) (user_id + " JOIN :#" +  channel)
# define ERR_BANNEDFROMCHAN(client, channel) ("474 " + client + " " + channel + " :Cannot join channel (+b)")
# define ERR_BADCHANNELKEY(client, channel) ("475 " + client + " " + channel + " :Cannot join channel (+k)")

// KICK
# define ERR_USERNOTINCHANNEL(client, nickname, channel) ("441 " + client + " " + nickname + " #" + channel + " :They aren't on that channel")
# define ERR_CHANOPRIVSNEEDED(client, channel) ("482 " + client + " " +  channel + " :You're not channel operator")
# define RPL_KICK(user_id, channel, kicked, reason) (user_id + " KICK " + channel + " " + kicked + " " + reason)

// KILL
# define ERR_NOPRIVILEGES(client) ("481 " + client + " :Permission Denied- You're not an IRC operator")
# define RPL_KILL(user_id, killed, comment) (user_id + " KILL " + killed + " " + comment)

// MODE
/* user mode */
# define ERR_UNKNOWNMODE(client, mode) (":localhost 472 " + client + " " + mode + " :is unknown mode char to me")
# define MODE_USERMSG(client, mode) (":" + client + " MODE " + client + " :" + mode)
# define ERR_UMODEUNKNOWNFLAG(client) (":localhost 501 " + client + " :Unknown MODE flag")
# define ERR_USERSDONTMATCH(client) ("502 " + client + " :Cant change mode for other users")
# define RPL_UMODEIS(client, mode) (":localhost 221 " + client + " " + mode)
/* channel mode */
# define MODE_CHANNELMSG(channel, mode) (":localhost MODE " + channel + " " + mode)
# define MODE_CHANNELMSGWITHPARAM(channel, mode, param) (":localhost MODE " + channel + " " + mode + " " + param)
# define RPL_CHANNELMODEIS(client, channel, mode) (":localhost 324 " + client + " " + channel + " " + mode)
# define RPL_CHANNELMODEISWITHKEY(client, channel, mode, password) (":localhost 324 " + client + " " + channel + " " + mode + " " + password)
# define ERR_CANNOTSENDTOCHAN(client, channel) ("404 " + client + " " + channel + " :Cannot send to channel")
# define ERR_CHANNELISFULL(client, channel) ("471 " + client + " " + channel + " :Cannot join channel (+l)")
//# define ERR_CHANOPRIVSNEEDED(client, channel) (":localhost 482 " + client + " #" + channel + " :You're not channel operator")
# define ERR_INVALIDMODEPARAM(client, channel, mode, password) ("696 " + client + " " + channel + " " + mode + " " + password + " : password must only contained alphabetic character")
# define RPL_ADDVOICE(nickname, username, channel, mode, param) (":" + nickname + "!" + username + "@localhost MODE " + channel + " " + mode + " " + param)

// MOTD
# define ERR_NOSUCHSERVER(client, servername) (":localhost 402 " + client + " " + servername + " :No such server")
# define ERR_NOMOTD(client) (":localhost 422 " + client + " :MOTD File is missing")
# define RPL_MOTDSTART(client, servername) (":localhost 375 " + client + " :- " + servername + " Message of the day - ")
# define RPL_MOTD(client, motd_line) (":localhost 372 " + client + " :" + motd_line)
# define RPL_ENDOFMOTD(client) (":localhost 376 " + client + " :End of /MOTD command.")


// NAMES
# define RPL_NAMREPLY(client, symbol, channel, list_of_nicks) (":localhost 353 " + client + " " + symbol + " " + channel + " :" + list_of_nicks)
# define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " " + channel + " :End of /NAMES list.")

// NICK
# define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :There is no nickname.")
# define ERR_ERRONEUSNICKNAME(client, nickname) (":localhost 432 " + client + " " + nickname + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nickname) (":localhost 433 " + client + " " + nickname + " :Nickname is already in use.")
# define RPL_NICK(oclient, uclient, client) (":" + oclient + "!" + uclient + "@localhost NICK " +  client)

// NOTICE
# define RPL_NOTICE(nick, username, target, message) (":" + nick + "!" + username + "@localhost NOTICE " + target + " " + message)

// OPER
# define ERR_NOOPERHOST(client) ("491 " + client + " :No O-lines for your host")
# define RPL_YOUREOPER(client) ("381 " + client + " :You are now an IRC operator")

// PART
# define RPL_PART(user_id, channel, reason) (user_id + " PART " + channel + " " + (reason.empty() ? "." : reason ))

// PASS
# define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect.")

// PING
# define RPL_PONG(user_id, token) (user_id + " PONG " + token)

// QUIT
# define RPL_QUIT(user_id, reason) (user_id + " QUIT :Quit: " + reason)
# define RPL_ERROR(user_id, reason) (user_id + " ERROR :" + reason)

// PRIVMSG
# define ERR_NOSUCHNICK(client, target) ("401 " + client + " " + target + " :No such nick/channel")
# define ERR_NORECIPIENT(client) ("411 " + client + " :No recipient given PRIVMSG")
# define ERR_NOTEXTTOSEND(client) ("412 " + client + " :No text to send")
# define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!" + username + "@localhost PRIVMSG " + target + " " + message)

// TOPIC
# define RPL_TOPIC(client, channel, topic) (":localhost 332 " + client + " " + channel + " " + topic)
# define RPL_NOTOPIC(client, channel) (":localhost 331 " + client + " " + channel + " :No topic is set")

// USER
# define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not reregister.")

#endif