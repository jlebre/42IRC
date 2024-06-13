#include "server.hpp"

bool	Server::check_pass(std::string pass)
{
	return pass == _password;
}

void	Server::pass(Client *client)
{
	if (client->getAuth())
	{
		reply(client, ERR_ALREADYREGISTERED(client->getUser()));
		return;
	}
	std::string password = "";
	if (parsed_message.size() > 1)
		password = parsed_message[1];
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
