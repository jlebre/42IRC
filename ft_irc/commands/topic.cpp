#include "server.hpp"

void		Server::topic(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return ;
    }

    std::string channel_name = "";
    if (parsed_message.size() > 1)
        channel_name = parsed_message[1];
    if (channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS(client->getNick(), channel_name, "TOPIC"));
        return;
    }
    std::string new_topic = leave_message(parsed_message, 2);
    
    Channel *channel;
    
    if (check_if_channel_exists(channel_name))
        channel = get_channel(channel_name);
    else
    {
        reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
        return;
    }

    if (channel->get_mode()._topic && !is_operator(client, channel_name))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(client->getNick(), channel->get_name()));
        return;
    }

    if (!check_client_on_channel(client->getNick(), channel_name))
    {
        reply(client, ERR_NOTONCHANNEL(client->getNick(), channel->get_name()));
        return;
    }

    if (new_topic.empty())
        reply(client, RPL_NOTOPIC(client->getNick(), channel_name));
    else
    {
        if (new_topic.length() > 390)
            new_topic = new_topic.substr(0, 390);
        channel->set_topic(new_topic);
        if (new_topic[0] != ':')
        new_topic = ":" + new_topic;
        size_t pos = new_topic.find_first_of("\r\n");
		if (pos != std::string::npos)
			new_topic = new_topic.substr(0, pos);
        reply(client, RPL_TOPIC(client->getNick(), channel_name, new_topic));
        for (size_t i = 0; i < channel->get_members().size(); i++)
        {
            if (new_topic.empty())
                reply(client, RPL_NOTOPIC(client->getNick(), channel_name));
            else
            reply(client, RPL_TOPIC(client->getNick(), channel_name, new_topic));
        }
        std::cout << "TOPIC COMMAND\n";
    }
}