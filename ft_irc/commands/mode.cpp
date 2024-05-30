#include "server.hpp"

/*
Usage:
/mode <#channel> <mode> [<mode params>]

Message to Client:
:<nick> MODE <channel> <mode> [<mode params>]
*/

void Server::parse_mode(std::string &channel_name, std::string &mode)
{
    std::string::size_type pos = _message.find(" ");
    if (pos != std::string::npos)
    {
        channel_name = _message.substr(0, pos);
        _message = _message.substr(pos + 1);
    }
    pos = _message.find(" ");
    if (pos != std::string::npos)
    {
        mode = _message.substr(0, pos);
        _message = _message.substr(pos + 1);
    }
    else
    {
        mode = _message;
        _message.clear();
    }
}


void		Server::mode(Client& client)
{
    (void)client;
    std::cout << "MODE COMMAND\n";
    std::string channel_name;
    std::string mode;

    parse_mode(channel_name, mode);

}
    //std::string msg = ":" + client.getNick() + " MODE " + channel_name + " " + mode; 


/*
i
t
k
o
l
*/