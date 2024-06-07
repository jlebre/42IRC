#include "server.hpp"

void Server::delete_client(std::string nick)
{
    Client *client = find_client(nick);
    std::vector<Channel*> channels = client->getChannels();
    for (size_t i = 0; i < channels.size(); i++)
    {
        Channel channel = find_channel(channels[i]->get_name());
        channel.remove_client(client);
        client->removeChannel(&channel);
    }
}

void		Server::quit(Client *client)
{
    std::cout << "QUIT COMMAND\n";
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED);
        return ;
    }
    client->setStatus(false);
    delete_client(client->getNick());
    std::cout << "Client " << client->getNick() << " has quit\n";
    reply_all(":" + client->getNick() + " QUIT : " + leave_message(parsed_message, 1), client);
    delete client;
} 
