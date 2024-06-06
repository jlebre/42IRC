#include "server.hpp"

void	Server::connect_client()
{
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(addr);

	memset(&addr, 0, sizeof(addr));
	int fd = accept(_sock.fd, (struct sockaddr *)&addr, &addr_size);
	if (fd != -1)
	{
		_clients[fd] = Client::newClient(addr, addr_size, fd);
		std::cout << "New Client #" << fd << " -> ";
		fcntl(fd, F_SETFL, O_NONBLOCK);
		struct epoll_event event;
		event.events = EPOLLIN;
		event.data.fd = fd;
		if (epoll_ctl(event_fd, EPOLL_CTL_ADD, fd, &event) != -1)
			std::cout << "Added to Poll\n";
		else
		{
			std::cerr << "Error:(Adding to Poll)\n";
			return;
		}
		_events[n_events] = event;
		n_events++;
		_clients[fd]->setAddr(addr);
	}
}
