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
    std::string new_topic = leave_message(parsed_message, 2);
    if (channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "TOPIC"));
        return;
    }
    
    Channel channel;
    
    try {
        channel = find_channel(channel_name);
    } catch (std::exception &e) {
        reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, channel.get_name()));
        return;
    }

    if (!is_operator(client, channel_name))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(this->_sock.ip, channel.get_name()));
        return;
    }

    if (!check_client_on_channel(client->getNick(), channel_name))
    {
        reply(client, ERR_NOTONCHANNEL(this->_sock.ip, channel.get_name()));
        return;
    }

    if (new_topic.empty())
        reply(client, "332 " + client->getNick() + " " + channel_name + " :" + channel.get_topic());
    else
    {
        if (!client->is_operator(channel))
        {
            reply(client, ERR_CHANOPRIVSNEEDED(this->_sock.ip, channel.get_name()));
            return;
        }
        channel.set_topic(new_topic);
        reply_on_channel(":" + client->getNick() + " TOPIC " + channel_name + " :" + new_topic, channel, client);
    }
}