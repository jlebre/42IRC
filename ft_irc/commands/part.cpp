#include "server.hpp"

std::string leave_message(std::vector<std::string> tmp, int it){
    std::string str;
    while(it < (int)tmp.size()){
        str = str.append(tmp[it].c_str());
        if(it + 1 < (int)tmp.size())
            str = str.append(" ");
        it++;
    }
    return str;
}

bool Server::check_if_is_mods(std::string str){
    for (int i = 0; i < (int)_channels.size(); i++){
        if (str == _channels[i]->get_name()){
            std::vector<Client*> members = _channels[i]->get_members();
            for (int j = 0; j < (int)members.size(); j++){
                if (members[j]->is_operator(_channels[i]))
                    return (true);    
            }
        }
    }
    return (false);
}

void Server::remove_channel(std::string str){
    std::vector<Channel*>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); ++it) {
        if ((*it)->get_name() == str) {
            delete *it;
            _channels.erase(it);
            break; 
        }
    }
}

void Server::part(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return;
    }

    std::string channel_name;
    std::string reason = "";

    size_t end = _line.find("\n");
    if (end != std::string::npos && _line.at(end - 1) == '\r') 
        end = end - 1;

    std::string cut = _line.substr(5, end - 5);

    size_t space_pos = cut.find(" ");
    if (space_pos != std::string::npos) 
    {
        channel_name = cut.substr(0, space_pos);
        reason = cut.substr(space_pos + 1);
    } 
    else 
    {
        channel_name = cut;
    }

    if (channel_name.empty())
    {
        reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "PART"));
        return;
    }

    Channel *channel;
    if (check_if_channel_exists(channel_name)) 
    {
        channel = get_channel(channel_name);
    } 
    else 
    {
        reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
        return;
    }

    if (!check_client_on_channel(client->getNick(), channel_name)) 
    {
        reply(client, ERR_NOTONCHANNEL(client->getNick(), channel_name));
        return;
    }

    std::string message = ":" + client->getNick() + " PART " + channel_name;
    if (!reason.empty())
        message += " :" + reason;

    bool wasOperator = false;
    if (is_operator(client, channel_name))
        wasOperator = true;

    client->removeChannel(channel);
    channel->remove_client(client);
    channel->remove_invited(client);
    channel->remove_operator(client);
    reply(client, message);

    if (channel->get_members().empty())
    {
        remove_channel(channel_name);
    }
    else
    {
        if (wasOperator && channel->get_operators().empty())
        {
            std::vector<Client*> clients = channel->get_members();
            for (size_t j = 0; j < clients.size(); j++)
            {
                if (clients[j]->getNick() != client->getNick())
                {
                    channel->add_operator(clients[j]);
                    break;
                }
            }
        }
        for (size_t i = 0; i < channel->get_members().size(); ++i)
            reply(channel->get_members()[i], message);
    }
    std::cout << "PART COMMAND\n";
}
