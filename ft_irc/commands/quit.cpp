#include "server.hpp"

void Server::delete_client(std::string nick)
{
    Client *client = find_client(nick);
    std::vector<Channel*> channels = client->getChannels();
    for (size_t i = 0; i < channels.size(); i++)
    {
        Channel *channel = get_channel(channels[i]->get_name());
        channel->remove_client(client);
        client->removeChannel(channel);
    }
}

void Server::quit(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return;
    }
    std::string nick = client->getNick();
    std::vector<Channel*> channels = client->getChannels();
    bool wasOperator = false;
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (is_operator(client, channels[i]->get_name()))
        {
            wasOperator = true;
            break;
        }
    }
    std::cout << "Client " << nick << " has quit\n";
    for (size_t i = 0; i < channels.size(); i++)
    {
        Channel *channel = get_channel(channels[i]->get_name());
        channel->remove_client(client);
        client->removeChannel(channel);
        channel->remove_operator(client);
        channel->remove_invited(client);
        for (size_t j = 0; j < channel->get_members().size(); j++)
            reply(channel->get_members()[j], ":" + nick + " PART " + channel->get_name() + " :" + leave_message(parsed_message, 1));
        if (wasOperator && channel->get_operators().empty())
        {
            std::vector<Client*> clients = channel->get_members();
            for (size_t j = 0; j < clients.size(); j++)
            {
                if (clients[j]->getNick() != nick)
                {
                    channel->add_operator(clients[j]);
                    break;
                }
            }
        }
    }
    client->setStatus(false);
    std::cout << "QUIT COMMAND\n";
}

