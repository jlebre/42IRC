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
    if (this == &src)
        return (*this);
    _addr = src._addr;
    _addr_size = src._addr_size;
    _nickname = src._nickname;
    _username = src._username;
    _realname = src._realname;
    _fd = src._fd;
    _id = src._id;
    _status = src._status;
    _auth = src._auth;
    _registered = src._registered;
    _channels_im_in = src._channels_im_in;

    return *this;
}

Client::~Client()
{
    _channels_im_in.clear();
}

Client *Client::newClient(struct sockaddr_in addr, socklen_t addr_size, int fd)
{
    return new Client(addr, addr_size, fd);
}

Client *Server::find_client(std::string nick)
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i] && (_clients[i]->getNick() == nick))
            return _clients[i];
    }
    return NULL;
}

bool Client::is_operator(Channel *channel)
{
    std::vector<Client*> operators = channel->get_operators();
    for (size_t i = 0 ; i < operators.size() ; i++)
    {
        if (operators[i]->getNick() == _nickname)
            return true;
    }
    return false;
}

void Client::addChannel(Channel *channel)
{
    _channels_im_in.push_back(channel);
}

void Client::removeChannel(Channel *channel)
{
    std::vector<Channel*>::iterator it = std::find(_channels_im_in.begin(), _channels_im_in.end(), channel);
    if (it != _channels_im_in.end())
        _channels_im_in.erase(it);
}
