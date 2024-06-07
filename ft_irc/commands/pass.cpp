#include "server.hpp"

bool	Server::check_pass(std::string pass)
{
	if (pass == _password)
		return true;
	return false;
}

void	Server::parse_pass(std::string &password)
{
	_line = _line.substr(_line.find("PASS") + 5);
	if (_line.find(" ") != std::string::npos)
		password = _line.substr(0, _line.find(" "));
	else if (_line.find("\r") != std::string::npos)
		password = _line.substr(0, _line.find("\r"));
	else if (_line.find("\n") != std::string::npos)
		password = _line.substr(0, _line.find("\n"));
	else
		password = _line;
	_line.clear();
}

void	Server::pass(Client *client)
{
	std::cout << "PASS COMMAND\n";
	if (client->getAuth() == true)
		reply(client, ERR_ALREADYREGISTERED);
	else
	{
		std::string password;
		parse_pass(password);
		if (password.empty())
			reply(client, ERR_NEEDMOREPARAMS);
		client->setAuth(check_pass(password));
		if (client->getAuth() == false)
			reply(client, ERR_PASSWDMISMATCH);
		else
			reply(client, "381 :You are now logged in");
	}
}
