#include "server.hpp"

bool	Server::valid_pass(std::string pass)
{
    if (pass == _password)
        return true;
    return false;
}

void	Server::pass(Client& client)
{
	std::cout << "PASS COMMAND\n";
	if (client.getAuth() == true)
		reply(client, "462 :Unauthorized command (already registered)");
	else
	{
		size_t i = _message.find("PASS");
		if (i != std::string::npos)
		{
			std::string password;
			password = _message;
			password.erase(i, 5);
			password = password.substr(i);
			password = password.substr(0, password.find("\r\n"));
			if (password.empty())
				reply(client, "461 :Need more parameters");
			client.setAuth(valid_pass(password));
			if (client.getAuth() == false && _message.compare(""))
				reply(client, "464 :Password incorrect");
			else
				reply(client, "381 :You are now logged in");
		}
	}
}
