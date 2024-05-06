#include "server.hpp"

void    Server::parse(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return;
	}
    //if (!is_num)
    // std::cerr << "Port should be a numeric value\n";
    _sock.port = std::atoi(argv[1]);
    if (_sock.port < 1024)
        std::cerr << "Port should be a number between 1024 and 65534\n";
    _password = argv[2];
    _sock.ip = "127.0.0.1";
    _max_clients = MAX_CLIENTS;
    n_events = 1;
    init_socket();
    std::cout << "Socket successfully initiated\n";
    init_poll();
    std::cout << "Poll successfully initiated\n";
	main_loop();
}
