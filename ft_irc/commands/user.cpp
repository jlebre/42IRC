#include "server.hpp"

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
            size_t i = _message.find("USER");
            if (i != std::string::npos)
            {
                std::string user = _message;
                user.erase(i, 5);
                user = user.substr(i);
                user = user.substr(0, user.find(" "));
                //user = "~" + user;
                if (user.empty())
                    reply(client, ERR_NEEDMOREPARAMS);
                else
                {
                    size_t j = _message.find(":");
                    std::string real = _message;
                    real.erase(j, 1);
                    real = real.substr(j);
                    real = real.substr(0, real.find("\r\n"));
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
}
