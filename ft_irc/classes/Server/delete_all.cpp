#include "server.hpp"

// Function to delete every client and channel
void    Server::delete_all()
{
    for (size_t i = 0; i < _clients.size(); i++)
        if (_clients[i])
            delete _clients[i];
    _clients.clear();
    for (size_t i = 0; i < _channels.size(); i++)
        if (_channels[i]->get_name() != "")
            delete &_channels[i];
    close(_sock.fd);
    for (size_t i = 0; i < n_events; i++)
        close(_events[i].data.fd);
    std::cout << "Server has been closed\n";
    exit(0);
}