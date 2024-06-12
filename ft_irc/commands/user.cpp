#include "server.hpp"

void    Server::parse_user(std::string &user, std::string &real)
{
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
        reply(client, ERR_PASSWDMISMATCH(this->_sock.ip));
    else
    {
        if (client->getRegistered())
            reply(client, ERR_ALREADYREGISTERED(this->_sock.ip));
        else
        {
            std::string user, real;
            parse_user(user, real);
            if (user.empty())
                reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "USER"));
            else
            {
                user = "~" + user;
                client->setReal(real);
                client->setUser(user);
                if (!client->getNick().empty())
                {
                    client->setRegistered(true);
                    reply(client, "001 :Welcome to the Internet Relay Network " + client->getNick() + "!\n" + user + "@" + "127.0.0.1");
                }
            }
        }
    }
    std::cout << "USER COMMAND\n";
}
