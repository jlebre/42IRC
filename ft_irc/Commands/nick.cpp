#include "server.hpp"

bool    Server::check_nickname(std::string nickname)
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->second->getNick() == nickname)
            return true;
    }
    return false;
}

void		Server::nick(Client& client)
{
    std::cout << "NICK COMMAND\n";
    
    if (client.getAuth() == true)
    {
        size_t i = _message.find("NICK");
        if (i != std::string::npos)
        {
            std::string nickname;
            nickname = _message;
            nickname.erase(i, 5);
            nickname = nickname.substr(i);
            nickname = nickname.substr(0, nickname.find("\r\n"));
            if (nickname.empty())
                reply(client, "431 :No nickname given");
            else if (nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-") != std::string::npos)
                reply(client, "432 :Erroneous nickname");
            else if (nickname.size() > 9)
                reply(client, "432 :Erroneous nickname");
            else if (check_nickname(nickname))
                reply(client, "433 :Nickname is already in use");
            else
            {
                if (client.getRegistered() == false && client.getUser().empty() == false)
                {
                    client.setRegistered(true);
                    reply(client, "001 :Welcome to the Internet Relay Network " + nickname + "!" + client.getUser() + "@" + "127.0.0.1");
                }
                else
                    reply_all(":" + client.getNick() + " NICK " + nickname + "\r\n");
                client.setNick(nickname);
            }
        }
    }
    else
        reply(client, "451 :You have not registered");
}
