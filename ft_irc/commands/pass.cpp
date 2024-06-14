#include "server.hpp"

bool	Server::check_pass(std::string pass)
{
	return pass == _password;
}

void Server::parse_pass(std::string &password)
{
	if (_line.size() < 5)
	{
		password.clear();
		return;
	}
    size_t pos = _line.find("PASS");
    if (pos != std::string::npos)
    {
        pos += 5;
		_line = _line.substr(pos);
        pos = _line.find_first_of(" \r\n");
        if (pos != std::string::npos)
            password = _line.substr(0, pos);
        else
            password = _line;
    }
    else
        password.clear();
}

void	Server::pass(Client *client)
{
	if (client->getAuth())
	{
		reply(client, ERR_ALREADYREGISTERED(client->getUser()));
		return;
	}

	std::string password = "";
	parse_pass(password);
	if (password.empty())
	{
		reply(client, ERR_NEEDMOREPARAMS("", client->getNick(), "PASS"));
		return;
	}
	if (!check_pass(password))
	{
		reply(client, ERR_PASSWDMISMATCH(client->getUser()));
		return;
	}
	client->setAuth(true);
	std::cout << "PASS COMMAND\n";
}
