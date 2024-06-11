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

void Server::kick(Client *client) {
    std::cout << "KICK COMMAND\n";

    if (!client->getRegistered()) {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "KICK"));
        return;
    }

    std::string reason = "";
    std::string channel;
    std::string nick;

    parse_kick(channel, nick, reason);

    if (channel.empty() || nick.empty()) {
        reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "KICK"));
        return;
    }

    Channel *channel_obj;
    if (check_if_channel_exists(channel)) {
        channel_obj = get_channel(channel);
    } else {
        reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, channel));
        return;
    }

    if (!is_operator(client, channel)) {
        reply(client, ERR_CHANOPRIVSNEEDED(this->_sock.ip, channel));
        return;
    }

    if (!check_client_on_channel(nick, channel)) {
        reply(client, "441 " + nick + " " + channel + " :They aren't on that channel");
        return;
    }

    Client *target_client = find_client(nick);
    if (target_client == NULL) {
        reply(client, "441 " + nick + " " + channel + " :They aren't on that channel");
        return;
    }

    channel_obj->remove_client(target_client);
    target_client->removeChannel(channel_obj);

    std::string kickMessage = "442 " + nick + " " + channel + " :Kicked by " + client->getNick();
    if (!reason.empty())
        kickMessage += " (" + reason + ")";

    reply(client, kickMessage);
    reply(target_client, "You have been kicked from " + channel + " by " + client->getNick() + (reason.empty() ? "" : (" (" + reason + ")")));
}