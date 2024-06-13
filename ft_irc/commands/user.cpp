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
            std::string user = "", realname = "";
            if (parsed_message.size() > 2)
            {
                user = parsed_message[1];
                realname = leave_message(parsed_message, 2);
            }
            if (user.empty() || realname.empty())
                reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "USER"));
            else
            {
                if (!client->getNick().empty())
                {
                    user = "~" + user;
                    client->setUser(user);
                    client->setRegistered(true);
                    reply(client, RPL_WELCOME(client->getNick()));
                }
            }
        }
    }
    std::cout << "USER COMMAND\n";
}
