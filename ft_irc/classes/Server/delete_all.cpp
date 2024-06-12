#include "server.hpp"

// Function to delete every client and channel
void    Server::delete_all()
{
    for (size_t i = 0; i < _clients.size(); i++)
        delete _clients[i];
    _clients.clear();
    for (size_t i = 0; i < _channels.size(); i++)
        delete &_channels[i];
    _channels.clear();
    for (int i = 0; i < n_events; i++)
    {
        epoll_ctl(event_fd, EPOLL_CTL_DEL, _events[i].data.fd, &_events[i]);
        close(_events[i].data.fd);
    }
    epoll_ctl(event_fd, EPOLL_CTL_DEL, _sock.fd, &_event);
    close(_sock.fd);
    close(event_fd);
    std::cout << "Server has been closed\n";
    exit(0);
}