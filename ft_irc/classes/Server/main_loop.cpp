#include "server.hpp"

void Server::print_info()
{
	std::cout << "\033[1;32mIRC Server started:\033[0m\n";
	std::cout << " __________________________" << std::endl;
	std::cout << "|      Listening on: " << _sock.fd << "     |" << std::endl;
	std::cout << "|__________________________|" << std::endl;
}

void	Server::main_loop()
{
	print_info();
	while (run)
	{
		int n = epoll_wait(event_fd, _events, 200, -1);
		if (n == -1)
		{
			if (errno == EINTR)
				continue;
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
					it->second->setStatus(1);
					reading(it->second);
					if (!it->second->get_status())
					{
						epoll_ctl(event_fd, EPOLL_CTL_DEL, fd, &_events[i]);
						close(fd);
						close(it->first);
						delete it->second;
						_clients.erase(it);
						n_events--;
						it = _clients.begin();
						continue;
					}
				}
			}
		}
	}
	delete_all();
}

void Server::ParseCommand()
{
    std::string token;
    size_t start = 0, end = 0;
    while ((end = _message.find(' ', start)) != std::string::npos)
	{
        token = _message.substr(start, end - start);
        parsed_message.push_back(token);
        start = end + 1;
    }
    token = _message.substr(start);
	size_t end1 = token.find_first_of(" \r\n", 0);
    token = token.substr(0, end1 - 0);
  	parsed_message.push_back(token);
}

void	Server::reading(Client *cli)
{
	memset(_buf, 0, BUF_SIZE);

	int r = recv(cli->get_fd(), _buf, BUF_SIZE, 0);
	if (!r)
	{
		cli->setStatus(0);
		_message = "QUIT\r\n";
		quit(cli);
	}
	else
	{
		_message.append(_buf);
		if (_message.find("\n") != std::string::npos)
		{
			ParseCommand();
			process_input(cli);
			parsed_message.clear();
			_message.clear();
		}
	}
}
