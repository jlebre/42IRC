#include "server.hpp"

void    Server::parse(int port, std::string password)
{
    _sock.port = port;
    _password = password;
    _sock.ip = "127.0.0.1";
    _max_clients = MAX_CLIENTS;
    n_events = 5;
    init_socket();
    init_poll();
	main_loop();
}
