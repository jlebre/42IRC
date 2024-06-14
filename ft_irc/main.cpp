#include "../Server/server.hpp"

bool run = true;

void handleSignal(int signo)
{
	(void)signo;
	run = false;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	std::string port = argv[1];
	if (port.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cout << "Port should be a number" << std::endl;
		return 1;
	}
	int port_i = atoi(port.c_str());
    if (port_i < 1024 || port_i > 65534)
	{
		std::cerr << "Port should be a number between 1024 and 65534\n";
		return 1;
	}
		
	Server irc;
	signal(SIGINT, handleSignal);
	signal(SIGTSTP, handleSignal);
	signal(SIGTERM, handleSignal);
	signal(SIGQUIT, handleSignal);
	irc.parse(argv);
	return 0;
}