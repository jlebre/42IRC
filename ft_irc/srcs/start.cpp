#include "server.hpp"

/*
#	In this file:
#	Start
#	Create socket
#	Main loop
#	Handle client
*/

void IRCServer::start(int argc, char **argv)
{
	t_env e;

	if (parser(&e, argc, argv))
		return ;
	std::cout << "IRCServer start" << std::endl;
	create_socket(e.port);
	std::cout << "Socket created: " << _sock << std::endl;
	if (listen(_sock, 5) < 0)
	{
		std::cerr << "Error: (Start) " << std::strerror(errno) << std::endl;
		exit(1);
	}
	main_loop(&e);
}

void IRCServer::create_socket(int port)
{
	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (_sock == -1)
	{
		std::cerr << "Error: (Create Socket) " << std::strerror(errno) << std::endl;
		exit(1);
	}

	sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);

	if (bind(_sock, (sockaddr *)&_addr, sizeof(_addr)) == -1)
	{
		std::cerr << "Error: (Bind) " << std::strerror(errno) << std::endl;
		close(_sock);
		exit(1);
	}

	_fds[0].fd = _sock;
	_fds[0].events = POLLIN;
	return;
}

void    IRCServer::main_loop(t_env *e)
{
	(void)e;
	std::cout << "Main Loop" << std::endl;
	while (true)
	{
		activity(e);
	}
}

void	IRCServer::activity(t_env *e)
{
	int activity = poll(_fds.data(), _fds.size(), -1);
	if (activity < 0)
	{
		std::cerr << "Error: (Activity) " << std::strerror(errno) << std::endl;
		exit(1);
	}

	if (_fds[0].revents & POLLIN)
		check_clients();
	for (size_t i = 1; i < _clients.size() + 1; ++i)
	{
		if (_fds[i].revents & POLLIN)
		{
			e->r = recv(_fds[i].fd, _buf, BUF_SIZE, 0);
			if (e->r < 0)
			{
				std::cerr << "Error: (Activity) " << std::strerror(errno) << std::endl;
				break ;
			}
			else if (e->r == 0)
			{
				std::cout << "Client #" << _fds[i].fd << " disconnected" << std::endl;
				close(_fds[i].fd);
				_fds.erase(_fds.begin() + i);
			}
			else
			{
				std::cout << "Received: " << _buf << std::endl;
				for (size_t  j = 1; j < _fds.size(); j++)
				{
					if (j != i)
						send(_fds[j].fd, _buf, e->r, 0);
				}
			}
		}
	}
}

void    IRCServer::check_clients()
{
	std::cout << "Waiting for client..." << std::endl;
	int client = accept(_sock, NULL, NULL);
	if (client)
		handleClient(client);
}

void    IRCServer::handleClient(int client)
{
	_clients.push_back(client);
	std::cout << "Client #" << client << " connected!\n";
}
