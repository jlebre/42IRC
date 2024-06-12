#include "server.hpp"

// Check if Client is on channel
bool Server::check_client_on_channel(std::string nick, std::string channel_name)
{
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i]->get_name() == channel_name)
        {
            std::vector<Client*> members = _channels[i]->get_members();
            for (size_t i = 0; i < members.size(); i++)
                if (members[i]->getNick() == nick)
                    return true;
        }
    }
    return false;
}

void Server::parse_invite(std::string &invitedNick, std::string &channel_name)
{
    size_t pos = _message.find("INVITE") + 7;  // Move past "INVITE "
    if (pos != std::string::npos)
    {
        _message = _message.substr(pos);
        pos = _message.find_first_of(" \r\n");
        if (pos != std::string::npos)
        {
            invitedNick = _message.substr(0, pos);
            _message = _message.substr(pos + 1);
            pos = _message.find_first_of(" \r\n");
            if (pos != std::string::npos)
                channel_name = _message.substr(0, pos);
            else
                channel_name = _message;
        }
        else
        {
            invitedNick.clear();
            channel_name.clear();
        }
    }
    else
    {
        invitedNick.clear();
        channel_name.clear();
    }
}

void		Server::invite(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return ;
    }
    std::string invitedNick, channel_name;
    parse_invite(invitedNick, channel_name);
    
    if (invitedNick.empty() || channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS(channel_name, client->getNick(), "INVITE"));
        return ;
    }

    Channel *channel;

    if (check_if_channel_exists(channel_name))
		channel = get_channel(channel_name);
	else
	{
		reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
		return ;
	}

    if (!check_client_on_channel(client->getNick(), channel->get_name()))
    {
        reply(client, ERR_NOTONCHANNEL(client->getNick(), channel_name));
        return ;
    }

    if (!client->is_operator(channel))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(client->getNick(), channel->get_name()));
        return ;
    }

    Client *invited;
    if (check_if_client_exists(invitedNick))
        invited = find_client(invitedNick);
    else
    {
        reply(client, NOUSER);
        return ;
    }

    if (check_client_on_channel(invitedNick, channel->get_name()))
    {
        reply(client, ERR_USERONCHANNEL(client->getNick(), invitedNick, channel_name));
        return ;
    }
    channel->add_invited(invited);
    reply(invited, RPL_INVITING(client->getNick(), invited->getNick(), channel_name));
    std::cout << "INVITE COMMAND\n";
}
