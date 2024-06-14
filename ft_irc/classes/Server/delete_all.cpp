#include "server.hpp"

void Server::delete_all()
{
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->first != event_fd)
            close(it->first);
        if (it->second)
            delete it->second;
    }
    _clients.clear();

    for (size_t i = 0; i < _channels.size(); i++)
        if (_channels[i])
            delete _channels[i];
    _channels.clear();
    close(event_fd);
    std::cout << "\nAll clients have been disconnected\n";
    std::cout << "All channels have been deleted\n";
    std::cout << "Poll has been closed\n";
    std::cout << "\033[1;32mServer has been successfully closed!\033[0m \n";
}
