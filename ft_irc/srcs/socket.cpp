#include "server.hpp"

void IRCServer::createsocket(t_env *e)
{
	e->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (e->sock == -1)
	{
		std::cerr << "Error: (Create Socket) " << std::strerror(errno) << std::endl;
		exit(1);
	}

	sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(e->port);

	if (bind(e->sock, (sockaddr *)&_addr, sizeof(_addr)) == -1)
	{
		std::cerr << "Error: (Bind) " << std::strerror(errno) << std::endl;
		close(e->sock);
		exit(1);
	}
}

/*
Creates a socket and binds it to the port
*/