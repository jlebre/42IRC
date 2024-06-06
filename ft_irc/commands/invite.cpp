#include "server.hpp"

/*
Usage:
/invite <nick> <#channel>

Message to Client:
:<nick> INVITE <nick> :<channel>
*/

// Check if Client is on channel
bool Server::check_client_on_channel(std::string nick, std::string channel_name)
{
    std::vector<Channel>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); it++)
    {
        if (it->get_name() == channel_name)
        {
            std::vector<Client*> members = it->get_members();
            for (int i = 0; i < (int)members.size(); i++)
                if (members[i]->getNick() == nick)
                    return true;
        }
    }
    return false;
}

void        Server::parse_invite(std::string &invitedNick, std::string &channel_name)
{
    // Remove "INVITE"
    _message = _message.substr(_message.find(" ") + 1);
    
    // Get "invitedNick"
    size_t pos = _message.find(" ");
    if (pos != std::string::npos)
    {
        invitedNick = _message.substr(0, pos);
        _message = _message.substr(pos + 1);
    }

    // Get "channel_name"
    pos = _message.find(" ");
    if (pos != std::string::npos)
    {
        channel_name = _message.substr(0, pos);
        _message = _message.substr(pos + 1);
    }
    else
    {
        channel_name = _message;
        _message.clear();
    }
}

void		Server::invite(Client& client)
{
    std::cout << "INVITE COMMAND\n";
    if (!client.getRegistered())
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }
    std::string invitedNick, channel_name;
    parse_invite(invitedNick, channel_name);
    
    if (invitedNick.empty() || channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS);
        return ;
    }

    Channel channel;

    try {
        channel = find_channel(channel_name);
    } catch (std::exception &e) {
        reply(client, ERR_NOSUCHCHANNEL);
        return ;
    }

    if (!check_client_on_channel(client.getNick(), channel.get_name()))
    {
        reply(client, ERR_NOTONCHANNEL);
        return ;
    }

    if (!client.is_operator(channel))
    {
        reply(client, ERR_CHANOPRIVSNEEDED);
        return ;
    }

    Client *invited = find_client(invitedNick);
    if (!invited)
    {
        reply(client, ERR_NOSUCHNICK);
        return ;
    }

    if (check_client_on_channel(invitedNick, channel.get_name()))
    {
        reply(client, ERR_USERONCHANNEL);
        return ;
    }

    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i].get_name() == channel_name)
            _channels[i].add_invited(*invited);
    }

    reply(*invited, ":" + client.getNick() + " INVITING " + invited->getNick() + " " + channel_name);
}


/*
Check if the client is registered

Parse message
/invite <nick> <#channel>


*/