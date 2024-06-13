#include "server.hpp"

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
            std::string user = "";
            std::cout << _line << std::endl;
            if (parsed_message.size() > 1)
                user = parsed_message[1];
            if (user.empty())
                reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "USER"));
            else
            {
                if (!client->getNick().empty())
                {
                    user = "~" + user;
                    client->setUser(user);
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
