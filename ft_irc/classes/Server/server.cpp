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
    std::map<int, Client*>::iterator it;
    for (it = _clients.begin(); it != _clients.end(); it++)
        if (it->second)
            delete it->second;
    _clients.clear();
    close(_sock.fd);
}

int Server::get_fd()
{
	return (_sock.fd);
}

void Server::delete_client(std::string nick)
{
    std::map<int, Client*>::iterator it;
    for (it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->second && it->second->getNick() == nick)
        {
            delete it->second;
            _clients.erase(it);
            break;
        }
    }
}

