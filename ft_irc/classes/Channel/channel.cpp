#include "channel.hpp"

Channel::Channel()
{
    _name = "";
    _password = "";
    _mode._invite = false;
    _mode._key = false;
    _mode._limit = false;
    _mode._nb = 0;
    _mode._topic = true;
}

Channel::Channel(std::string name) : _name(name) {
    _password = "";
    _mode._invite = false;
    _mode._key = false;
    _mode._key_password = "";
    _mode._limit = false;
    _mode._nb = 0;
    _mode._topic = true;
}

Channel::Channel(std::string name, std::string password) : _name(name), _password(password) {
    _mode._invite = false;
    _mode._key = false;
    _mode._key_password = "";
    _mode._limit = false;
    _mode._nb = 0;
    _mode._topic = true;
}

Channel::~Channel()
{
    _members.clear();
    _invited.clear();
    _operators.clear();
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
    _members = src.get_members();
    _invited = src.get_invited();
    _operators = src.get_operators();

    return *this;
}

void Channel::add_client(Client *client)
{
    _members.push_back(client);
}

void Channel::add_invited(Client *client)
{
    _invited.push_back(client);
}

void Channel::add_operator(Client *client)
{
    _operators.push_back(client);
}

void Channel::remove_client(Client *client)
{
    std::vector<Client*>::iterator it = std::find(_members.begin(), _members.end(), client);
    if (it != _members.end())
        _members.erase(it);
}

void Channel::remove_operator(Client *client)
{
    std::vector<Client*>::iterator it = std::find(_operators.begin(), _operators.end(), client);
    if (it != _operators.end())
        _operators.erase(it);
}

void Channel::remove_invited(Client *client)
{
    std::vector<Client*>::iterator it = std::find(_invited.begin(), _invited.end(), client);
    if (it != _invited.end())
        _invited.erase(it);
}

void    Channel::change_nickname(std::string old_nick, std::string new_nick)
{
    for (size_t i = 0; i < _members.size(); i++)
    {
        if (!_members[i]->getNick().compare(old_nick.c_str()))
            _members[i]->setNick(new_nick);
    }

    for (size_t i = 0; i < _invited.size(); i++)
    {
        if (!_invited[i]->getNick().compare(old_nick.c_str()))
            _invited[i]->setNick(new_nick);
    }

    for (size_t i = 0; i < _operators.size(); i++)
    {
        if (!_operators[i]->getNick().compare(old_nick.c_str()))
            _operators[i]->setNick(new_nick);
    }
}