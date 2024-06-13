#include "server.hpp"

void		Server::privmsg(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return ;
    }

    if (parsed_message.size() < 3)
    {
        reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "PRIVMSG"));
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
            reply(client, ERR_NOSUCHCHANNEL(client->getNick(), target));
            return ;
        }

        if (!check_client_on_channel(client->getNick(), target))
        {
            reply(client, ERR_NOTONCHANNEL(client->getNick(), channel->get_name()));
            return;
        }
        if (message.empty())
        {
            //reply(client, ERR_NOTEXTTOSEND(client->getNick()));
            return;
        }
        for (size_t i = 0; i < channel->get_members().size(); i++)
        {
            if (channel->get_members()[i]->getNick() != client->getNick())
                reply(channel->get_members()[i], ":" + client->getNick() + " PRIVMSG " + target + " " + message);
        }
    }
    else // If target is a client
    {
        if (check_if_client_exists(target))
        {
            Client *targetClient = find_client(target);
            reply(targetClient, ":" + client->getNick() + " PRIVMSG " + target + " " + message);
        }
        else
            reply(client, ERR_NOSUCHNICK(client->getNick(), target));
        std::cout << "PRIVMSG COMMAND\n";
    }
}
