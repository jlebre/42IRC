#include "server.hpp"

int    Server::check_command(std::string line)
{
	std::string commands[] = { \
	"PASS", \
	"NICK", \
	"USER", \
	"JOIN", \
	"PART", \
	"QUIT", \
	"PRIVMSG", \
	"MODE", \
	"TOPIC", \
	"KICK", \
	"INVITE"
	};

	for (int i = 0 ; i < 11 ; i++)
		if (line.find(commands[i]) != std::string::npos)
			return i;
	return -1;
}

void    Server::process_input(Client& cli)
{
	//std::cout << "Processing input: " << _message << std::endl;
	size_t begin = 0;
	size_t end = _message.find("\n");

	while (end != std::string::npos)
	{
		std::string line = _message.substr(begin, end);

		int command = check_command(line);
		if (command != -1)
		{
			void    (Server::*commands[11])(Client &cli) = { \
			&Server::pass, \
			&Server::nick, \
			&Server::user, \
			&Server::join, \
			&Server::part, \
			&Server::quit, \
			&Server::privmsg, \
			&Server::mode, \
			&Server::topic, \
			&Server::kick, \
			&Server::invite \
			};
			(this->*commands[command])(cli);
		}
		begin = end + 1;
		if (begin != std::string::npos)
			end = _message.find("\n", begin);
		else
			end = begin;
	}
}