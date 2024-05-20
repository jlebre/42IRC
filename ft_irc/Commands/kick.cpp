#include "server.hpp"

bool	Server::check_on_channel(std::string nick)
{
    std::map<int, Client*>::iterator it;
    for (it = _clients.begin(); it != _clients.end(); it++)
        if (it->second && it->second->getNick() == nick)
            return true;
    return false;
   
}

bool	Server::check_on_server(std::string nick, std::string channel)
{
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i].get_name() == channel)
        {
            for (size_t j = 0; j < _channels[i].get_clients().size(); j++)
            {
                if (_channels[i].get_clients()[j].getNick() == nick)
                    return true;
            }
        }
    }
    return false;
}

void		Server::kick(Client& client)
{
    std::cout << "KICK COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, "451 :You are not registered");
        return ;
    }

    std::string reason = "";
    std::string channel;
    std::string nick;

    size_t i = _message.find("KICK");
    if (i != std::string::npos)
    {
        std::string kick;
        kick = _message;
        kick.erase(i, 5);
        kick = kick.substr(i);
        kick = kick.substr(0, kick.find("\r\n"));
        if (kick.empty())
            reply(client, "461 :Need more parameters");
        else
        {
            size_t j = kick.find(" ");
            if (j != std::string::npos)
            {
                channel = kick.substr(0, j);
                nick = kick.substr(j + 1);
                size_t k = nick.find(" ");
                if (k != std::string::npos)
                {
                    reason = nick.substr(k + 1);
                    nick = nick.substr(0, k);
                }
            }
            else
                reply(client, "461 :Need more parameters");
        }
    }
    if (channel.empty() || nick.empty())
        reply(client, "461 :Need more parameters");
    else if (check_on_channel(nick) == false)
        reply(client, "441 " + nick + " " + channel + " :They aren't on that channel");
    else if (check_on_server(nick, channel) == false)
        reply(client, "441 " + nick + " " + channel + " :They aren't on that channel");
    else
    {
        reply_all(":" + client.getNick() + " KICK " + channel + " " + nick + " :" + reason);
        reply(client, "442 " + nick + " " + channel + " :Kicked by " + client.getNick());
    }
}
