#include "client.hpp"

// SETTERS
void Client::setStatus(bool status)
{
    _status = status;
}

void Client::setNick(std::string nick)
{
    _nickname = nick;
}

void Client::setUser(std::string user)
{
    _username = user;
}

void Client::setReal(std::string real)
{
    _realname = real;
}

void Client::setAddr(struct sockaddr_in addr)
{
    _addr = addr;
}

void Client::setAuth(bool auth)
{
    _auth = auth;
}

void Client::setRegistered(bool registered)
{
    _registered = registered;
}

// GETTERS
int Client::get_id()
{
    return (_id);
}

int Client::get_fd()
{
    return (_fd);
}

int Client::get_status()
{
    return (_status);
}

std::string Client::getNick()
{
    return (_nickname);
}

std::string Client::getUser()
{
    return (_username);
}

std::string Client::getReal()
{
    return (_realname);
}

struct sockaddr_in Client::getAddr()
{
    return (_addr);
}

bool Client::getAuth()
{
    return (_auth);
}

bool Client::getRegistered()
{
    return (_registered);
}