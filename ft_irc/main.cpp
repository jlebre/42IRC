#include "../Server/server.hpp"

bool run = true;

void handleSignal(int signo) {
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
		
	Server irc;
	signal(SIGINT, handleSignal);
	signal(SIGTSTP, handleSignal);
	signal(SIGTERM, handleSignal);
	signal(SIGQUIT, handleSignal);
	irc.parse(argv);
	return 0;
}