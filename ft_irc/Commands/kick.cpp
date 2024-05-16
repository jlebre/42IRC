#include "server.hpp"

bool	Server::check_on_channel(std::string nick)
{
    std::map<int, Channel*>::iterator it;
    std::map<int, Channel*>::iterator ti;
    for (it = _channels.begin(); it != _channels.end(); it++)
        if (it->second->get_name() == channel)
            for (ti = _channels.begin(); ti != _channels.end(); ti++)
                if (it->second->get_clients().at(ti->first).getNick() == nick)
                    return true;
    return false;
}

bool	Server::check_on_server(std::string nick, std::string channel)
{
    std::map<int, Client*>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); it++)
        if (it-> second && it->second->get_name() == nick)
            return true;
    return false;
}

void		Server::kick(Client& client)
{
    (void)client;
    std::cout << "KICK COMMAND\n";
}
