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

void Server::kick(Client *client)
{
    if (!client->getRegistered()) {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return;
    }

    std::string reason = "", channel_name = "", nick = "";
    if (parsed_message.size() > 2)
    {
        channel_name = parsed_message[1];
        nick = parsed_message[2];
        if (parsed_message.size() > 3)
            reason = parsed_message[3];
    }

    if (channel_name.empty() || nick.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "KICK"));
        return;
    }

    Channel *channel;
    if (check_if_channel_exists(channel_name))
        channel = get_channel(channel_name);
    else
    {
        reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
        return;
    }

    if (!is_operator(client, channel->get_name()))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(client->getNick(), channel->get_name()));
        return;
    }

    if (!check_client_on_channel(client->getNick(), channel->get_name()))
    {
        reply(client, ERR_NOTONCHANNEL(client->getNick(), channel->get_name()));
        return;
    }

    Client *target_client = find_client(nick);
    if (target_client == NULL) {
        reply(client, NOUSER);
        return;
    }

    if (!check_client_on_channel(nick, channel->get_name()))
    {
        reply(client, ERR_USERNOTINCHANNEL(client->getNick(), nick, channel->get_name()));
        return;
    }

    std::string kickMessage = ":" + client->getNick() + " KICK " + channel->get_name() + " " + target_client->getNick();
    if (!reason.empty())
        kickMessage += " " + reason;
    
    reply(target_client, kickMessage);
    channel->remove_client(target_client);
    channel->remove_operator(target_client);
    channel->remove_invited(target_client);
    target_client->removeChannel(channel);
    
    if (channel->get_members().empty())
        remove_channel(channel->get_name());

    for (size_t i = 0; i < channel->get_members().size(); i++)
        reply(channel->get_members()[i], kickMessage);
    std::cout << "KICK COMMAND\n";
}