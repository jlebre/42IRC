#include "server.hpp"

/*
Usage:
/join <#channel>

Message to Client:
:<nick> JOIN <channel>
*/

// Pode juntar a mais do que 1 canal de uma vez

// Adicionar mais checks
// Se tem # no meio e caracteres proibidos
bool check_if_is_channel(std::string str){
    const char *tmp;
    tmp = str.c_str();
    if (tmp[0] == '#')
        return true;
    return false;
}

bool Server::check_if_channel_exists(std::string name)
{
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i] && (_channels[i]->get_name() == name))
            return true;
    }
    return false;
}

void		Server::join(Client& client)
{
    std::cout << "JOIN COMMAND\n";
    if (!client.getRegistered())
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }
    for (size_t i = 1; i < parsed_message.size(); i++)
    {
        std::string channel_name = parsed_message[i];
        std::cout << "PARSED: " << parsed_message[i] << std::endl;
        if (check_if_is_channel(channel_name))
        {
            std::cout << "IS CHANNEL" << std::endl;
            if (!check_if_channel_exists(channel_name))
            {
                std::cout << "Does not exist" << std::endl;
                Channel *new_channel = new Channel;
                new_channel->set_name(channel_name);
                new_channel->add_client(client);
                new_channel->add_operator(client);
                new_channel->set_topic("");
                _channels.push_back(new_channel);
                reply_all(":" + client.getNick() + " JOIN " + channel_name);
            }
            else
            {
                std::cout << "Exists" << std::endl;
                for (size_t j = 0; j < _channels.size(); j++){
                    std::cout << "jadasdsa\n";
                    if (_channels[i]->get_name() == channel_name)
                    {
                        _channels[i]->add_client(client);
                        reply_all(":" + client.getNick() + " JOIN " + channel_name);
                        break;
                    }
                }
            }
        }
    }
}   