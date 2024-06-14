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
    std::string reason = "";
    size_t res = _line.find(":");
    if (res != std::string::npos)
        reason = _line.substr(res + 1);
    std::vector<Channel*> channels = client->getChannels();
    std::vector<std::string> channel_names;
    bool wasOperator = false;
    client->setStatus(false);
    std::cout << "Client " << nick << " has quit\n";
    for (size_t i = 0; i < channels.size(); i++)
    {
        Channel *channel = get_channel(channels[i]->get_name());
        if (is_operator(client, channel->get_name()))
            wasOperator = true;
        reply(client, ":" + nick + " ERROR " + " :" + reason);
        client->removeChannel(channel);
        channel->remove_client(client);
        channel->remove_operator(client);
        channel->remove_invited(client);
        if (channel->get_members().empty())
            channel_names.push_back(channel->get_name());
        else
        {
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
        for (size_t j = 0; j < channel->get_members().size(); j++)
            reply(channel->get_members()[j], ":" + nick + " PART " + channel->get_name() + " :" + reason);
    }
    for (size_t i = 0; i < channel_names.size(); i++)
        remove_channel(channel_names[i]);
    //std::cout << "QUIT COMMAND\n";
}

