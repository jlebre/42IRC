#include "server.hpp"

bool Server::check_nickname(std::string nickname)
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) 
    {
        if (it->second == NULL)
            continue; 

        std::string clientNick = it->second->getNick();
        if (clientNick == nickname)
            return true;
    }
    return false;
}


void    Server::parse_nick(std::string &nickname)
{
    size_t pos = _line.find("NICK");
    if (pos != std::string::npos)
    {
        pos += 5;
        size_t end = _line.find_first_of(" \r\n", pos);
        nickname = _line.substr(pos, end - pos);
    }
    else
        nickname.clear();
}

bool    Server::is_valid_nickname(std::string nickname)
{
    if (nickname.empty() || nickname.size() > 9)
        return false;
    return nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") == std::string::npos;
}

void		Server::nick(Client *client)
{
    if (!client->getAuth())
    {
        reply(client, ERR_PASSWDMISMATCH(client->getNick()));
        return ;
    }
    
    if (_line.find("NICK") == std::string::npos)
	{
		reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "NICK"));
		return;
	}

    std::string nickname = parsed_message[1];
    //parse_nick(nickname);
    if (nickname.empty())
    {
        reply(client, ERR_NONICKNAMEGIVEN(nickname));
        return ;
    }
    if (!is_valid_nickname(nickname))
    {
        reply(client, ERR_ERRONEUSNICKNAME(nickname, nickname));
        return ;
    }
    
    if (check_nickname(nickname))
    {
        reply(client, ERR_NICKNAMEINUSE(nickname, nickname));
        return ;
    }

    if (!client->getRegistered() && !client->getUser().empty())
        client->setRegistered(true);
    else
    {
        std::string old = client->getNick();
        client->setNick(nickname);
        for (size_t i = 0; i < _channels.size(); i++)
        {
            if (check_client_on_channel(old, _channels[i]->get_name()))
            {
                Channel *channel = get_channel(_channels[i]->get_name());
                for (size_t j = 0; j < channel->get_members().size(); j++)
                    reply(channel->get_members()[j], ":" + old + " NICK " + nickname);
            }
        }
    }
    std::cout << "NICK COMMAND\n";
}
