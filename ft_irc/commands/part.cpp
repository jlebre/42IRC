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
                if (members[j]->is_operator(*_channels[i]) == true)
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

void		Server::part(Client& client)
{
    std::cout << "PART COMMAND\n";
    //std::vector<Client*> members = find_channel(parsed_message[1]);

    std::string msg = ":" + client.getNick() + " PART " + parsed_message[1] + " :" + leave_message(parsed_message, 2);
    reply_on_all_channels(msg, client);
    ////// se nao existir mais gente fechar o channel
    if (find_channel(parsed_message[1]).get_members().size() == 0){
        remove_channel(parsed_message[1]);
    }
    //////se a pessoa que bazar for a unica com mods dar a outra pessoa;
    else if(check_if_is_mods(parsed_message[1]) == false){
        find_channel(parsed_message[1]).add_operator(client);
    }
    ///ver se a mais casos coninhas

    
}
