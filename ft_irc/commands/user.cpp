#include "server.hpp"

void    Server::parse_user(std::string &user, std::string &real)
{
    // Find "USER"
    _line = _line.substr(_line.find("USER") + 5);

    // Remove "USER"
    _line = _line.substr(_line.find(" ") + 1);

    // Get "user" and "real" (if it exists)
    size_t pos = _line.find(":");
    if (pos != std::string::npos)
    {
        user = _line.substr(0, pos);
        real = _line.substr(pos + 1);
        real = real.substr(0, real.find("\r\n"));
    }
    else
    {
        pos = _line.find(" ");
        if (pos != std::string::npos)
        {
            user = _line.substr(0, pos);
            real = _line.substr(pos + 1);
            real = real.substr(0, real.find("\r\n"));
        }
        else
        {
            user = _line.substr(0, _line.size() - 2);
            real = "";
		    _line.clear();
        }
    }
    
}

void		Server::user(Client& client)
{
    std::cout << "USER COMMAND\n";
    if (client.getAuth() == false)
        reply(client, ERR_PASSWDMISMATCH);
    else
    {
        if (client.getRegistered() == true)
            reply(client, ERR_ALREADYREGISTERED);
        else
        {
            std::string user, real;
            parse_user(user, real);
            user = "~" + user;
            if (user.empty())
                reply(client, ERR_NEEDMOREPARAMS);
            else
            {
                client.setReal(real);
                client.setUser(user);
                if (client.getNick().empty() == false)
                {
                    client.setRegistered(true);
                    reply(client, "001 :Welcome to the Internet Relay Network " + client.getNick() + "!\n" + user + "@" + "127.0.0.1");
                }
            }
        }
    }
}
