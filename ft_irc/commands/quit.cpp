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
    int fd = client->get_fd();
    if (_clients.find(fd) == _clients.end())
    {
        std::cerr << "Error: Client not found\n";
        return;
    }
    if (epoll_ctl(event_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
        std::cerr << "Error(EPOLL_CTL_DEL)\n";
    close(fd);
    _clients.erase(fd);
    std::cout << "Client #" << fd << " disconnected and removed from epoll\n";
}

void Server::quit(Client *client)
{
    std::cout << "QUIT COMMAND\n";
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "QUIT"));
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
    reply_all(":" + nick + " QUIT :" + leave_message(parsed_message, 1), client);
    client->setStatus(false);
    delete_client(nick);
    if (wasOperator)
    {
        for (size_t i = 0; i < channels.size(); i++)
        {
            if (is_operator(client, channels[i]->get_name()))
            {
                std::vector<Client*> clients = channels[i]->get_members();
                for (size_t j = 0; j < clients.size(); j++)
                {
                    if (clients[j]->getNick() != nick)
                    {
                        channels[i]->add_operator(clients[j]);
                        break;
                    }
                }
            }
        }
    }
}

