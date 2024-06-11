#include "server.hpp"

void		Server::topic(Client *client)
{
    std::cout << "TOPIC COMMAND\n";
    if (client->getRegistered() == false)
    {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "TOPIC"));
        return ;
    }

    std::string channel_name = "";
    if (parsed_message.size() > 1)
        channel_name = parsed_message[1];
    if (channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "TOPIC"));
        return;
    }
    std::string new_topic = leave_message(parsed_message, 2);
    
    Channel *channel;
    
    if (check_if_channel_exists(channel_name))
        channel = get_channel(channel_name);
    else
    {
        reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, channel_name));
        return;
    }

    if (channel->get_mode()._topic && !is_operator(client, channel_name))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(this->_sock.ip, channel->get_name()));
        return;
    }

    if (!check_client_on_channel(client->getNick(), channel_name))
    {
        reply(client, ERR_NOTONCHANNEL(this->_sock.ip, channel->get_name()));
        return;
    }

    if (new_topic.empty())
        reply(client, "332 " + client->getNick() + " " + channel_name + " " + channel->get_topic());
    else
    {
        channel->set_topic(new_topic);
        if (new_topic[0] != ':')
        new_topic = ":" + new_topic;
        size_t pos = new_topic.find_first_of("\r\n");
		if (pos != std::string::npos)
			new_topic = new_topic.substr(0, pos);
        reply(client, ":" + client->getNick() + " TOPIC " + channel_name + " " + new_topic);
        reply_on_channel(":" + client->getNick() + " TOPIC " + channel_name + " " + new_topic, channel, client);
    }
}