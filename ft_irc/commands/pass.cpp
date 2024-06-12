#include "server.hpp"

bool	Server::check_pass(std::string pass)
{
	return pass == _password;
}

void	Server::parse_pass(std::string &password)
{
	size_t pos = _line.find("PASS") + 5;
	if (pos != std::string::npos)
	{
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
		reply(client, ERR_ALREADYREGISTERED(this->_sock.ip));
		return;
	}

	std::string password;
	parse_pass(password);
	if (password.empty())
	{
		reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "PASS"));
		return;
	}
	if (!check_pass(password))
	{
		reply(client, ERR_PASSWDMISMATCH(this->_sock.ip));
		return;
	}
	client->setAuth(true);
	reply(client, "381 :You are now logged in");
	std::cout << "PASS COMMAND\n";
}
