#include "server.hpp"

void    Server::parse_user(std::string &user, std::string &real)
{
    if (_line.size() < 5)
	{
		user.clear();
        real.clear();
		return;
	}

    size_t pos = _line.find("USER");
    if (pos == std::string::npos)
    {
        user = "";
        real = "";
        return;
    }
    
    _line = _line.substr(pos + 5);

    size_t pos2 = _line.find(" :");
    if (pos2 != std::string::npos)
    {
        user = _line.substr(0, pos2);
        real = _line.substr(pos2 + 2);
    }
    else
    {
        user = _line.substr(0, _line.find("\r\n"));
        real = "";
    }
    user = user.substr(0, user.find_last_not_of(" \t\n\r") + 1);
    real = real.substr(0, real.find_last_not_of(" \t\n\r") + 1);
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
            std::string user, real;
            if (parsed_message.size() < 1)
            {
                reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "USER"));
                return;
            }
            parse_user(user, real);
            if (user.empty())
            {
                reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "USER"));
                return;
            }

            user = "~" + user;
            client->setReal(real);
            client->setUser(user);
            if (!client->getRegistered() && !client->getNick().empty())
            {
                client->setRegistered(true);
                reply(client, RPL_WELCOME(client->getNick()));
            }
        }
    }
    std::cout << "USER COMMAND\n";
}
