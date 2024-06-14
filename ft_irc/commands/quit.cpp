#include "server.hpp"

void    print_quit(std::string nick)
{
    std::cout << " __________________________" << std::endl;
	std::cout << "|  \033[1;31mClient " << nick << " has quit\033[0m  |\n";
	std::cout << "|__________________________|" << std::endl;
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
    print_quit(nick);
    for (size_t i = 0; i < channels.size(); i++)
    {
        Channel *channel = get_channel(channels[i]->get_name());
        if (check_client_on_channel(nick, channel->get_name()))
        {
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
                            update_list(channel);
                            break;
                        }
                    }
                }
            }
            for (size_t j = 0; j < channel->get_members().size(); j++)
                reply(channel->get_members()[j], ":" + nick + " PART " + channel->get_name() + " :" + reason);
        }
    }
    if (!channel_names.empty())
        for (size_t i = 0; i < channel_names.size(); i++)
            remove_channel(channel_names[i]);
    channel_names.clear();
    //std::cout << "QUIT COMMAND\n";
}

