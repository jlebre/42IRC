#include "server.hpp"

void    IRCServer::main_loop(t_env *e)
{
	std::cout << "Main Loop" << std::endl;
	while (true)
	{
		build_fd_set(e);
		std::cout << "after: " << std::endl;
		e->out = select(FD_SETSIZE, &e->fd_read, &e->fd_write, (fd_set *)0, 0); // Last is timer. Add timer so it does not get stuck
		switch (e->out)
		{
			case -1:
				std::cerr << "Error: (Main Loop) " << std::strerror(errno) << std::endl;
				exit(1);
			case 0:
				std::cerr << "Error: (Main Loop) " << std::strerror(errno) << std::endl;
				exit(1);
			default:
				if (FD_ISSET(STDIN_FILENO, &e->fd_read))
				{
					std::cout << "STDIN: "; // Input from server
					fgets(e->buf, BUF_SIZE, stdin);
					std::cout << e->buf << std::endl;
					process_input(e);
					continue;
				}

				if (FD_ISSET(e->sock, &e->fd_read))
					check_clients(e);

				for (size_t i = 0; e->client[i].id; ++i)
				{
					if (FD_ISSET(e->client[i].fd, &e->fd_read))
					{
						std::cout << "Client #" << e->client[i].id << " is ready" << std::endl;
						e->r = recv(e->client[i].fd, _buf, BUF_SIZE, 0);
						std::cout << "Received: " << _buf << std::endl;
						if (e->r < 0)
						{
							std::cerr << "Error: (Activity) " << std::strerror(errno) << std::endl;
							break ;
						}
						else if (e->r == 0)
						{
							std::cout << "Client #" << e->client[i].fd << " disconnected" << std::endl;
							close(e->client[i].fd);
							//e->client.erase(e->client.begin() + i);
						}
						else
						{
							std::cout << "Received: " << _buf << std::endl;
							for (size_t  j = 1;  e->client[j].id ; j++)
							{
								if (j != i)
									send(e->client[j].fd, _buf, e->r, 0);
							}
						}
					}
				}
		}
	}
}
