#include "server.hpp"

void Server::init_socket()
{
	// CREATE SOCKET
	_sock.fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
	if (_sock.fd == -1)
	{
		std::cerr << "Error: (Create Socket) " << std::strerror(errno) << std::endl;
		exit(1);
	}

	// BIND SOCKET
	struct sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr(_sock.ip.c_str());
	_addr.sin_port = htons(_sock.port);

	if (bind(_sock.fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
	{
		std::cerr << "Error: (Bind) " << std::strerror(errno) << std::endl;
		exit(1);
	}

	// LISTEN SOCKET
	if (listen(_sock.fd, _max_clients) == -1)
	{
		std::cerr << "Error: (Listen) " << std::strerror(errno) << std::endl;
		exit(1);
	}
	std::cout << "Listening on " << _sock.fd << std::endl;
}
