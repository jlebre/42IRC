#ifndef REPLIES_HPP
# define REPLIES_HPP

# define RPL_WELCOME "001 :Welcome to the Internet Relay Network"
# define ERR_NOSUCHNICK "401 :No such nick"
# define ERR_NOSUCHCHANNEL "403 :No such channel"
# define ERR_UNKNOWNCOMMAND "421 :Unknown command"
# define ERR_NOTONCHANNEL "442 :You're not on that channel"
# define ERR_NOTREGISTERED "451 :You are not registered"
# define ERR_NEEDMOREPARAMS "461 :Need more parameters"
# define ERR_ALREADYREGISTERED "462 :Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH "464 :Password incorrect"
# define ERR_RESTRICTED "484 :Your connection is restricted!"
# define ERR_NOPRIVILEGES "481 :Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED "482 :You're not channel operator"
# define ERR_USERONCHANNEL "443 :is already on channel"
# define ERR_NONICKNAMEGIVEN "431 :No nickname given"
# define ERR_ERRONEUSNICKNAME "432 :Erroneous nickname"
# define ERR_NICKNAMEINUSE "433 :Nickname is already in use"
# define ERR_ERRONEUSUSERNAME "501 :Erroneous username"
# define ERR_ERRONEUSREALNAME "502 :Erroneous realname"
# define ERR_ERRONEUSMODES "501 :Unknown MODE flag"
# define ERR_USERSDONTMATCH "502 :Cannot change mode for other users"
# define ERR_NOTEXTTOSEND "412 :No text to send"

#endif