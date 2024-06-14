#include "server.hpp"

void print_new_client(int fd)
{
	std::cout << " __________________________" << std::endl;
	std::cout << "|      \033[1;32mNew Client #" << fd << "\033[0m       |\n";
}

void print_added()
{
	std::cout << "|      Added to Poll       |" << std::endl;
	std::cout << "|__________________________|" << std::endl;
}

void	Server::connect_client()
{
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(addr);

	memset(&addr, 0, sizeof(addr));
	int fd = accept(_sock.fd, (struct sockaddr *)&addr, &addr_size);
	if (fd != -1)
	{
		_clients[fd] = Client::newClient(addr, addr_size, fd);
		print_new_client(fd);
		fcntl(fd, F_SETFL, O_NONBLOCK);
		struct epoll_event event;
		event.events = EPOLLIN;
		event.data.fd = fd;
		if (epoll_ctl(event_fd, EPOLL_CTL_ADD, fd, &event) != -1)
			print_added();
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
