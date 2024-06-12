#include "server.hpp"

// Function to delete every client and channel
void    Server::delete_all()
{
    for (size_t i = 0; i < _clients.size(); i++)
        if (_clients[i])
        {
            remove_from_epoll(_clients[i]->get_fd());
            delete _clients[i];
        }
    _clients.clear();
    for (size_t i = 0; i < _channels.size(); i++)
        if (_channels[i]->get_name() != "")
            delete &_channels[i];
    close(_sock.fd);
    std::cout << "Server has been closed\n";
    exit(0);
}