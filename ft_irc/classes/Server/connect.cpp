#include "server.hpp"

void Server::disconnect_client(int fd)
{
    if (_clients.find(fd) == _clients.end())
    {
        std::cerr << "Error: Client not found\n";
        return;
    }
    if (epoll_ctl(event_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
        std::cerr << "Error(EPOLL_CTL_DEL)\n";
    close(fd);
    _clients.erase(fd);
    std::cout << "Client #" << fd << " disconnected and removed from epoll\n";
}


void Server::connect_client()
{
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(addr);

    memset(&addr, 0, sizeof(addr));
    int fd = accept(_sock.fd, (struct sockaddr *)&addr, &addr_size);
    if (fd != -1)
    {
        fcntl(fd, F_SETFL, O_NONBLOCK);  // Set the client socket to non-blocking
        _clients[fd] = Client::newClient(addr, addr_size, fd);
        std::cout << "New Client #" << fd << std::endl;

        struct epoll_event event;
        event.events = EPOLLIN;
        event.data.fd = fd;
        if (epoll_ctl(event_fd, EPOLL_CTL_ADD, fd, &event) != -1)
        {
            std::cout << "Added to Poll\n";
            _events[n_events] = event;
            n_events++;
            _clients[fd]->setAddr(addr);
        }
        else
        {
            std::cerr << "Error:(Adding to Poll)\n";
            disconnect_client(fd);  // Cleanup if adding to poll fails
        }
    }
    else
        std::cerr << "Error: Accepting client connection\n";
}

/*
void	Server::connect_client()
{
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(addr);

	memset(&addr, 0, sizeof(addr));
	int fd = accept(_sock.fd, (struct sockaddr *)&addr, &addr_size);
	if (fd != -1)
	{
		_clients[fd] = Client::newClient(addr, addr_size, fd);
		std::cout << "New Client #" << fd << std::endl;
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
*/
