#include "server.hpp"

void		Server::privmsg(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "PRIVMSG"));
        return ;
    }

    if (parsed_message.size() < 3)
    {
        reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "PRIVMSG"));
        return;
    }

    std::string target = parsed_message[1];
    std::string message = leave_message(parsed_message, 2);
    if (message[0] != ':')
        message = ":" + message;
    // If target is a channel
    if (target[0] == '#')
    {
        Channel *channel;
        
        if (check_if_channel_exists(target))
		    channel = get_channel(target);
        else
        {
            reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, target));
            return ;
        }

        if (!check_client_on_channel(client->getNick(), target))
        {
            reply(client, ERR_NOTONCHANNEL(this->_sock.ip, channel->get_name()));
            return;
        }
        if (message.empty())
        {
            reply(client, ERR_NOTEXTTOSEND(this->_sock.ip));
            return;
        }
        reply_on_channel(":" + client->getNick() + " PRIVMSG " + target + " " + message, channel, client);
    }
    else // If target is a client
    {
        if (check_if_client_exists(target))
        {
            Client *targetClient = find_client(target);
            reply(targetClient, ":" + client->getNick() + " PRIVMSG " + target + " " + message);
        }
        else
            reply(client, ERR_NOSUCHNICK(this->_sock.ip, target));
        std::cout << "PRIVMSG COMMAND\n";
    }
}
