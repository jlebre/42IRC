#include "server.hpp"

void		Server::topic(Client& client)
{
    std::cout << "TOPIC COMMAND\n";
    if (!client.getRegistered())
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }

    std::string channel_name = ""; 
    std::string topic = leave_message(parsed_message, 2);

    if (parsed_message.size() > 1)
        channel_name = parsed_message[1];

    if (channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS);
        return;
    }

    Channel channel;
    
    std::cout << "Channel name: " << channel_name << std::endl;

    try {
        channel = find_channel(channel_name);
    } catch (std::exception &e) {
        reply(client, ERR_NOSUCHCHANNEL);
        return;
    }

    if (!check_client_on_channel(client.getNick(), channel.get_name()))
    {
        reply(client, ERR_NOTONCHANNEL);
        return;
    }

    if (topic.empty())
        reply(client, "332 " + client.getNick() + " " + channel_name + " :" + channel.get_topic());
    else
    {
        if (!client.is_operator(channel))
        {
            reply(client, ERR_CHANOPRIVSNEEDED);
            return;
        }
        channel.set_topic(topic);
        reply(client, ":" + client.getNick() + " TOPIC " + channel_name + " :" + topic);
    }
}
