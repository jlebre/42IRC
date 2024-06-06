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

void		Server::part(Client& client)
{
    std::cout << "PART COMMAND\n";

    std::string msg = ":" + client.getNick() + " PART " + parsed_message[1] + " :" + leave_message(parsed_message, 2); 
    reply_all_on_channel(msg, client);
}
