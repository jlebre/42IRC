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

void		Server::invite(Client *client)
{
    std::cout << "INVITE COMMAND\n";
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "INVITE"));
        return ;
    }
    std::string invitedNick, channel_name;
    parse_invite(invitedNick, channel_name);
    
    if (invitedNick.empty() || channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "INVITE"));
        return ;
    }

    Channel channel;

    try {
        channel = find_channel(channel_name);
    } catch (std::exception &e) {
        reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, channel.get_name()));
        return ;
    }

    if (!check_client_on_channel(client->getNick(), channel.get_name()))
    {
        reply(client, ERR_NOTONCHANNEL(this->_sock.ip, channel.get_name()));
        return ;
    }

    if (!client->is_operator(channel))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(this->_sock.ip, channel.get_name()));
        return ;
    }

    try{
        find_client(invitedNick);
    } catch (std::exception &e) {
        reply(client, ERR_NOSUCHNICK(this->_sock.ip, invitedNick));
        return ;
    }
    Client *invited(find_client(invitedNick));

    if (check_client_on_channel(invitedNick, channel.get_name()))
    {
        reply(client, ERR_USERONCHANNEL(this->_sock.ip, invitedNick, channel.get_name()));
        return ;
    }

    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i]->get_name() == channel_name)
            _channels[i]->add_invited(invited);
    }
    reply(invited, ":" + client->getNick() + " INVITE " + invitedNick + " " + channel_name);
}
