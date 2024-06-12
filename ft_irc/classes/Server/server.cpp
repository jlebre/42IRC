#include "server.hpp"

Server::Server(){}

Server::Server(const Server &src)
{
    (void)src;
}

Server &Server::operator=(const Server &src)
{
    (void)src;
    return (*this);
}

Server::~Server()
{
    if (_sock.fd != -1)
        close(_sock.fd);

    std::map<int, Client*>::iterator it;
    for (it = _clients.begin(); it != _clients.end(); it++)
        if (it->second)
            delete it->second;
    _clients.clear();
}

int Server::get_fd()
{
	return (_sock.fd);
}
