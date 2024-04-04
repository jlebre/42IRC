#include "server.hpp"

IRCServer::IRCServer(){}

IRCServer::~IRCServer(){}

void IRCServer::start(int argc, char **argv)
{
	t_env e;

	if (parser(&e, argc, argv))
		return ;
	std::cout << "IRCServer start" << std::endl;

	createsocket(&e);
	std::cout << "Socket created: " << e.sock << std::endl;

	if (listen(e.sock, MAX_CLIENTS) == -1)
	{
		std::cerr << "Error: (Start) " << std::strerror(errno) << std::endl;
		exit(1);
	}
	main_loop(&e);
}

/*
Parses the command line arguments
Creates a socket and binds it to the port
Listens for incoming connections
Starts the main loop
*/