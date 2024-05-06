#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "../includes/libs.hpp"
# include "../Server/server.hpp"

# define COMMAND_FUNCTIONS { \
    &Server::pass, \
    &Server::nick, \
    &Server::user, \
    &Server::join, \
    &Server::part, \
    &Server::quit, \
    &Server::privmsg, \
    &Server::mode, \
    &Server::topic, \
    &Server::kick, \
    &Server::invite \
}

#endif