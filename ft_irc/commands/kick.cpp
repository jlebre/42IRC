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
        if (_channels[i]->get_name() == channel)
        {
            for (size_t j = 0; j < _channels[i]->get_members().size(); j++)
            {
                if (_channels[i]->get_members()[j]->getNick() == nick)
                    return true;
            }
        }
    }
    return false;
}

bool    Server::is_operator(Client *client, std::string channel)
{
    for (size_t i = 0; i < client->getChannels().size(); i++)
        if (client->getChannels()[i]->get_name() == channel)
            for (size_t j = 0; j < client->getChannels()[i]->get_operators().size(); j++)
                if (client->getChannels()[i]->get_operators()[j]->getNick() == client->getNick())
                    return true;
    return false;
}

void		Server::kick(Client *client)
{
    std::cout << "KICK COMMAND\n";
    if (client->getRegistered() == false)
    {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "KICK"));
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
            reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "KICK"));
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
                reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "KICK"));
        }
    }

    if (!is_operator(client, channel))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(this->_sock.ip, channel));
        return ;
    }
    if (channel.empty() || nick.empty())
        reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "KICK"));
    else if (!check_on_channel(nick))
        reply(client, "441 " + nick + " " + channel + " :They aren't on that channel");
    else if (!check_on_server(nick, channel))
        reply(client, "441 " + nick + " " + channel + " :They aren't on that channel");
    else
        reply(client, "442 " + nick + " " + channel + " :Kicked by " + client->getNick());
}
