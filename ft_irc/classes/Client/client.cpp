#include "client.hpp"

Client::Client(struct sockaddr_in addr, socklen_t addr_size, int fd): _addr(addr), _addr_size(addr_size), _fd(fd)
{
    _auth = false;
    _registered = false;
    _status = false;
    _username = "";
    _realname = "";
    _nickname = "";
}

Client::Client(const Client &src)
{
    (void)src;
}

Client &Client::operator=(const Client &src)
{
    (void)src;
    return (*this);
}

Client::~Client()
{
}

Client *Client::newClient(struct sockaddr_in addr, socklen_t addr_size, int fd)
{
    return new Client(addr, addr_size, fd);
}
