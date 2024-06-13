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
        if (compare_channel_name(_channels[i]->get_name(),channel))
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
        if (compare_channel_name(client->getChannels()[i]->get_name(), channel))
            for (size_t j = 0; j < client->getChannels()[i]->get_operators().size(); j++)
                if (client->getChannels()[i]->get_operators()[j]->getNick() == client->getNick())
                    return true;
    return false;
}

void Server::parse_kick(std::string &channel, std::string &nick, std::string &reason)
{
    size_t pos = _line.find("KICK") + 5;
    if (pos != std::string::npos)
    {
        _line = _line.substr(pos);
        pos = _line.find_first_of(" \r\n");
        if (pos != std::string::npos)
        {
            channel = _line.substr(0, pos);
            _line = _line.substr(pos + 1);
            pos = _line.find_first_of(" \r\n");
            if (pos != std::string::npos)
            {
                nick = _line.substr(0, pos);
                _line = _line.substr(pos + 1);
                pos = _line.find_first_of("\r\n");
                if (pos != std::string::npos)
                    reason = _line.substr(0, pos);
                else
                    reason = _line;
            }
        }
    }
    else
    {
        channel.clear();
        nick.clear();
        reason.clear();
    }
}

void Server::kick(Client *client)
{

    if (!client->getRegistered()) {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return;
    }

    std::string reason = "";
    std::string channel;
    std::string nick;

    parse_kick(channel, nick, reason);

    if (channel.empty() || nick.empty()) {
        reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "KICK"));
        return;
    }

    Channel *channel_obj;
    if (check_if_channel_exists(channel)) {
        channel_obj = get_channel(channel);
    } else {
        reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel));
        return;
    }

    if (!is_operator(client, channel)) {
        reply(client, ERR_CHANOPRIVSNEEDED(client->getNick(), channel));
        return;
    }

    if (!check_client_on_channel(nick, channel)) {
        reply(client, ERR_NOTONCHANNEL(client->getNick(), channel));
        return;
    }

    Client *target_client = find_client(nick);
    if (target_client == NULL) {
        reply(client, NOUSER);
        return;
    }

    channel_obj->remove_client(target_client);
    target_client->removeChannel(channel_obj);

    std::string kickMessage = ":" + nick + " KICK " + channel + " " + target_client->getNick();
    if (!reason.empty())
        kickMessage += " " + reason;

    for (size_t i = 0; i < channel_obj->get_members().size(); i++)
        reply(channel_obj->get_members()[i], kickMessage);
    std::cout << "KICK COMMAND\n";
}