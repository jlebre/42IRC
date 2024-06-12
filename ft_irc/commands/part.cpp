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

void		Server::part(Client *client)
{
    if (!client->getRegistered()) {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return;
    }

    std::string reason = "";
    std::string channel;
    std::string nick;

    parse_kick(channel, nick, reason);

    if (channel.empty() || nick.empty()) {
        reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "KICK"));
        return;
    }

    Channel *channel_obj;
    if (check_if_channel_exists(channel)) {
        channel_obj = get_channel(channel);
    } else {
        reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel));
        return;
    }

    if (!is_operator(client, channel)) {
        reply(client, ERR_CHANOPRIVSNEEDED(client->getNick(), channel));
        return;
    }

    if (!check_client_on_channel(nick, channel)) {
        reply(client, ERR_NOTONCHANNEL(client->getNick(), channel));
        return;
    }

    Client *target_client = find_client(nick);
    if (target_client == NULL) {
        reply(client, NOUSER);
        return;
    }

    channel_obj->remove_client(target_client);
    target_client->removeChannel(channel_obj);

    std::string kickMessage = ":" + nick + " KICK " + channel + " " + target_client->getNick();
    if (!reason.empty())
        kickMessage += " " + reason;

    for (size_t i = 0; i < channel_obj->get_members().size(); i++)
        reply(channel_obj->get_members()[i], kickMessage);

    ///
    
    std::string msg = ":" + client->getNick() + " PART " + parsed_message[1] + " :" + leave_message(parsed_message, 2);
    reply_on_all_channels(msg, client);
    if (find_channel(parsed_message[1]).get_members().size() == 0)
        remove_channel(parsed_message[1]);
    else if(!check_if_is_mods(parsed_message[1]))
        find_channel(parsed_message[1]).add_operator(client);
    find_channel(parsed_message[1]).remove_client(client);
    client->removeChannel(&find_channel(parsed_message[1]));
    std::cout << "PART COMMAND\n";
}
