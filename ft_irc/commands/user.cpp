#include "server.hpp"

void    Server::parse_user(std::string &user)
{
    size_t pos = _line.find("USER");
    if (pos == std::string::npos)
    {
        user = "";
        return;
    }
    
    _line = _line.substr(pos + 5);

    size_t pos2 = _line.find(" ");
    if (pos2 != std::string::npos)
        user = _line.substr(0, pos2);
    else
        user = _line.substr(0, _line.find("\r\n"));
    user = user.substr(0, user.find_last_not_of(" \t\n\r") + 1);
    if (user.length() > MAX_USER_LENGTH)
        user = user.substr(0, MAX_USER_LENGTH);
}

bool    Server::is_valid_user(std::string user)
{
    if (user.empty() || user.size() > MAX_USER_LENGTH)
        return false;
    return user.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") == std::string::npos;
}

void		Server::user(Client *client)
{
    if (!client->getAuth())
        reply(client, ERR_PASSWDMISMATCH(client->getNick()));
    else
    {
        if (client->getRegistered())
            reply(client, ERR_ALREADYREGISTERED(client->getUser()));
        else
        {
            std::string user;
            parse_user(user);
            if (user.empty())
                reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "USER"));
            else
            {
                user = "~" + user;
                client->setUser(user);
                if (!client->getNick().empty())
                {
                    client->setRegistered(true);
                    reply(client, RPL_WELCOME(client->getNick()));
                    reply(client, RPL_YOURHOST(client->getNick()));
                    reply(client, RPL_CREATED(client->getNick()));
                    reply(client, RPL_MYINFO(client->getNick()));
                }
            }
        }
    }
    std::cout << "USER COMMAND\n";
}
