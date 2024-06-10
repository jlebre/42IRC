#include "server.hpp"

// Quando tem " :" funciona no nc
// Quando não tem " :" funciona no Hexchat

void		Server::privmsg(Client *client)
{
    std::cout << "PRIVMSG COMMAND\n";
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
        Channel channel;
        try {
            channel = find_channel(target);
        } catch (std::exception &e) {
            reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, channel.get_name()));
            return;
        }
        channel = find_channel(target);

        if (!check_client_on_channel(client->getNick(), target))
        {
            reply(client, ERR_NOTONCHANNEL(this->_sock.ip, channel.get_name()));
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
        try {
            Client *targetClient(find_client(target));
            reply(targetClient, ":" + client->getNick() + " PRIVMSG " + target + " " + message);
        } catch (std::exception &e) {
            reply(client, ERR_NOSUCHNICK(this->_sock.ip, target));
            return;
        }

    }
}
