#include "channel.hpp"

Channel::Channel()
{
}

Channel::~Channel()
{
}

Channel::Channel(const Channel &src)
{
    (void)src;
}

Channel &Channel::operator=(const Channel &src)
{
    (void)src;
    return *this;
}

void Channel::init_channel(std::string channel_name)
{
    this->_channel_name = channel_name;
}

void Channel::shutdown_channel()
{
    while (!_clients.empty())
    {
        delete _clients.back();
        _clients.pop_back();
        //Need to remove from Client
    }

    //Remove invite clients
}

void Channel::add_user(Client *client)
{
    ClientIterator it;

    _clients.push_back(client);
    //Check invite list
}

void Channel::kick_user(Client *client)
{
    ClientIterator it;

    it = std::find(_clients.begin(), _clients.end(), client);
    _clients.erase(it);

    //If kicked is admin create new admin
}
