#include "server.hpp"

void Server::delete_all()
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        close(it->first);
        delete it->second;
    }
    _clients.clear();

    for (size_t i = 0; i < _channels.size(); i++)
        delete _channels[i];
    _channels.clear();
    close(event_fd);
   std::cout << "Server has been closed\n";
}
