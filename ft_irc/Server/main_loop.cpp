#include "server.hpp"

void	Server::main_loop()
{
	while (true)
	{
		int n = epoll_wait(event_fd, _events, 200, -1);
		if (n == -1)
		{
			std::cerr << "Error(EPOLL)\n";
			break;
		}
		for (int i = 0; i < n; ++i)
		{
			if (_events[i].data.fd == _sock.fd)
				connect_client();
			else
			{
				int fd = _events[i].data.fd;
				std::map<int, Client*>::iterator it = _clients.find(fd);
				if (it->second && it != _clients.end())
				{
					(*it->second).setStatus(1);
					reading(*it->second);
					if ((*it->second).get_status() == false)
					{
						close(fd);
						epoll_ctl(event_fd, EPOLL_CTL_DEL, fd, &_event);
						n_events--;
						continue;
					}
				}
			}
		}
	}
}

void	Server::reading(Client& cli)
{
	memset(_buf, 0, BUF_SIZE);

	int r = recv(cli.get_fd(), _buf, BUF_SIZE, 0);
	if (!r)
	{
		cli.setStatus(0);
		_message = "QUIT\r\n";
		quit(cli);
	}
	else
	{
		_message.append(_buf);
		if (_message.find("\n") != std::string::npos)
		{
			process_input(cli);
			_message.erase();
		}
	}
}
