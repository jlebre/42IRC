#include "server.hpp"

/*
Usage:
/topic <#channel> [<newtopic>]

Message to Client:
:<nick> TOPIC <channel> :<newtopic>
*/

void        Server::parse_topic(std::string &channel_name, std::string &new_topic)
{
    // Remove "TOPIC"

    size_t pos = _message.find(" ") + 1;
    _message = _message.substr(pos);

    // Channel name
    pos = _message.find(" ") + 1;
    if (pos != std::string::npos)
    {
        channel_name = _message.substr(0, pos);
        _message = _message.substr(pos + 1);
    }
    else
    {
        channel_name = _message;
        _message.clear();
        return;
    }

    // New topic
    pos = _message.find(" ");
    if (pos != std::string::npos)
    {
        new_topic = _message.substr(0, pos);
        _message = _message.substr(pos + 1);
    }
    else
    {
        new_topic = _message;
        _message.clear();
        return;
    }
}

void		Server::topic(Client& client)
{
    std::cout << "TOPIC COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }

    std::string channel_name, new_topic;
    parse_topic(channel_name, new_topic);
    if (channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS);
        return;
    }

    Channel channel;
    
    try {
        channel = find_channel(channel_name);
    } catch (std::exception &e) {
        reply(client, ERR_NOSUCHCHANNEL);
        return;
    }

    if (check_client_on_channel(client.getNick(), channel.get_name()) == false)
    {
        reply(client, ERR_NOTONCHANNEL);
        return;
    }

    if (new_topic.empty())
        reply(client, "332 " + client.getNick() + " " + channel_name + " :" + channel.get_topic());
    else
    {
        if (client.is_operator(channel) == false)
        {
            reply(client, ERR_CHANOPRIVSNEEDED);
            return;
        }
        channel.set_topic(new_topic);
        reply(client, ":" + client.getNick() + " TOPIC " + channel_name + " :" + new_topic);
    }
}

//std::string msg = ":" + clientNick + " TOPIC " + channel_name + " :" + topic;  
//client.getNick()