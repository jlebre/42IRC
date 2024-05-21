#include "server.hpp"

std::string	Server::read()
{
	std::string msg;
	char buf[BUF_SIZE];
	int r = BUF_SIZE - 1;

	while (1)
	{
		memset(buf, 0, BUF_SIZE);
		r = recv(_sock.fd, buf, BUF_SIZE, 0);
		if (r <= 0)
			break;
		msg += buf;
	}
	return (msg);
}
