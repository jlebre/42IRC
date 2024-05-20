#include "server.hpp"

/*
Usage:
/join <#channel>

Message to Client:
:<nick> JOIN <channel>
*/

void		Server::join(Client& client)
{
    std::cout << "JOIN COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, "451 :You are not registered");
        return ;
    }
    bool channel_exists = false;
    std::string channel_name = _message.substr(_message.find("#") + 1);
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i].get_name() == channel_name)
        {
            channel_exists = true;
            break ;
        }
    }
    if (channel_exists == false)
    {
        Channel channel;
        channel.set_name(channel_name);
        channel.add_client(client);
        channel.add_operator(client);
        channel.set_topic("");
        _channels.push_back(channel);
        std::string message = ":" + client.getNick() + " JOIN " + channel_name;
        reply_all(message);
    }
    else
    {
        for (size_t i = 0; i < _channels.size(); i++)
        {
            if (_channels[i].get_name() == channel_name)
            {
                _channels[i].add_client(client);
                std::string message = ":" + client.getNick() + " JOIN " + channel_name;
                reply_all(message);
                break ;
            }
        }
    }
}
