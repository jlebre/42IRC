#include "server.hpp"

/*
Usage:
/join <#channel>

Message to Client:
:<nick> JOIN <channel>
*/

// Pode juntar a mais do que 1 canal de uma vez

bool check_if_is_channel(std::string str){
    const char *tmp;
    tmp = str.c_str();
    if (tmp[0] == '#')
        return true;
    return false;
}


void		Server::join(Client& client)
{
    std::cout << "JOIN COMMAND\n";
    if (client.getRegistered() == false)
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }
    bool channel_exists = false;
    int size = (int)parsed_message.size();
    for (int i = 1; i < size; ++i){
        if (check_if_is_channel(parsed_message[i]) == false)
            continue;
        for (size_t x = 0; x < _channels.size(); x++){
            if(_channels[x].get_name() == parsed_message[i]){
                channel_exists = true;
                std::string message = ":" + client.getNick() + " JOIN " + parsed_message[i];
                reply_all(message);
            }
        }
        if (channel_exists == false){
            Channel channel;
            channel.set_name(parsed_message[i]);
            channel.add_client(client);
            channel.add_operator(client);
            channel.set_topic("");
            _channels.push_back(channel);
            std::string message = ":" + client.getNick() + " JOIN " + parsed_message[i];
            reply_all(message);
        }
        
    }
}