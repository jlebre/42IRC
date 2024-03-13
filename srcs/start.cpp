#include "server.hpp"

void IRCServer::start(int argc, char **argv)
{
	t_env e;

	if (parser(&e, argc, argv))
		return ;
	std::cout << "IRCServer start" << std::endl;
	create_socket(e.port);
	std::cout << "Socket created: " << e.port << std::endl;
	if (listen(_sock, 5) < 0)
	{
		std::cerr << "Error: (Start) " << std::strerror(errno) << std::endl;
		return;
	}
	main_loop(&e);
}

void IRCServer::create_socket(int port)
{
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;

	_sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(_sock, (sockaddr *)&_addr, sizeof(_addr));
	if (_sock == -1)
	{
		std::cerr << "Error: (Create Socket) " << std::strerror(errno) << std::endl;
		return;
	}
	return;
}

void    IRCServer::main_loop(t_env *e)
{
	std::cout << "Main Loop" << std::endl;
	while (true)
	{
		int client = accept(e->port, NULL, NULL);
		if (client < 0)
			continue;
		handleClient(client);
	}
}

void    IRCServer::handleClient(int client)
{
	_clients.push_back(client);
	std::cout << "Client connected: " << client << std::endl;
}
