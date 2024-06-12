#include "server.hpp"

bool    Server::check_nickname(std::string nickname)
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) 
        if (it->second->getNick() == nickname)
            return true;
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
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "NICK"));
        return ;
    }
    
    std::string nickname;
    parse_nick(nickname);
    if (nickname.empty())
    {
        reply(client, ERR_NONICKNAMEGIVEN(this->_sock.ip));
        return ;
    }
    if (!is_valid_nickname(nickname))
    {
        reply(client, ERR_ERRONEUSNICKNAME(this->_sock.ip, nickname));
        return ;
    }
    
    if (check_nickname(nickname))
    {
        reply(client, ERR_NICKNAMEINUSE(this->_sock.ip, nickname));
        return ;
    }

    if (!client->getRegistered() && !client->getUser().empty())
    {
        client->setRegistered(true);
        reply(client, "001 :Welcome to the Internet Relay Network " + nickname + "!" + client->getUser() + "@" + "127.0.0.1");
    }
    else
    {
        std::string old = client->getNick();
        client->setNick(nickname);
        for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) 
            reply(it->second, ":" + old + " NICK " + nickname);
    }
    std::cout << "NICK COMMAND\n";
}
