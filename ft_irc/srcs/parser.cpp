#include "server.hpp"

int    IRCServer::parser(t_env *e, int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	std::cout << "Port: " << std::atoi(argv[1]) << std::endl;
	e->port = std::atoi(argv[1]);
	if (e->port == -1)
		return 1;
	e->maxfd = MAX_CLIENTS;
	for (int i = 0; i < e->maxfd; i++)
		e->fds[i].type = 0;
	return 0;
}

/*
	std::cout << "Password: " << argv[2] << std::endl;
	e->vars.password = argv[2];
*/