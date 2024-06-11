#include "channel.hpp"

// Getters

std::string Channel::get_name() const
{
    return _name;
}

std::string Channel::get_topic() const
{
    return _topic;
}

std::string Channel::get_password() const
{
    return _password;
}

t_modes Channel::get_mode() const
{
    return _mode;
}

std::vector<Client*> Channel::get_members() const
{
    return _members;
}

std::vector<Client*> Channel::get_invited() const
{
    return _invited;
}

std::vector<Client*> Channel::get_operators() const
{
    return _operators;
}

// Setters

void Channel::set_name(std::string name)
{
    _name = name;
}

void Channel::set_topic(std::string topic)
{
    _topic = topic;
}

void Channel::set_password(std::string password)
{
    _password = password;
}

void Channel::set_mode(t_modes mode)
{
    _mode = mode;
}
