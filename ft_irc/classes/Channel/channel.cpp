#include "channel.hpp"

Channel::Channel()
{
    _name = "";
    _password = "";
    _mode._invite = false;
    _mode._key = false;
    _mode._moderated = false;
    _mode._limit = false;
}

Channel::Channel(std::string name) : _name(name) {
    _password = "";
    _mode._invite = false;
    _mode._key = false;
    _mode._moderated = false;
    _mode._limit = false;
}

Channel::Channel(std::string name, std::string password) : _name(name), _password(password) {
    _mode._invite = false;
    _mode._key = false;
    _mode._moderated = false;
    _mode._limit = false;
}

Channel::~Channel()
{
}

Channel::Channel(const Channel &src)
{
    *this = src;
}

Channel &Channel::operator=(const Channel &src)
{
    _name = src.get_name();
    _topic = src.get_topic();
    _password = src.get_password();
    _mode = src.get_mode();
    _limit = src.get_limit();
    _clients = src.get_clients();
    _invited = src.get_invited();
    _operators = src.get_operators();

    return *this;
}

void Channel::add_client(Client& client)
{
    _clients.push_back(client);
}

void Channel::add_invited(Client& client)
{
    _invited.push_back(client);
}

void Channel::add_operator(Client& client)
{
    _operators.push_back(client);
}

Channel & Server::find_channel(std::string channel_name)
{
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i].get_name() == channel_name)
            return _channels[i];
    }
    throw std::exception();
}