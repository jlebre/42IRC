#include "server.hpp"

/*
Usage:
/pass <password>

Message to Client:
:PASS <password>
*/

bool	Server::check_pass(std::string pass)
{
    if (pass == _password)
        return true;
    return false;
}

void	Server::pass(Client& client)
{
	std::cout << "PASS COMMAND\n";
	if (client.getAuth() == true)
		reply(client, ERR_ALREADYREGISTERED);
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
				reply(client, ERR_NEEDMOREPARAMS);
			client.setAuth(check_pass(password));
			if (client.getAuth() == false && _message.compare(""))
				reply(client, ERR_PASSWDMISMATCH);
			else
				reply(client, "381 :You are now logged in");
		}
	}
}
 //std::string msg = "PASS " + password;  