#include "../Server/server.hpp"

bool run = true;

void handleSignal(int signo) {
	(void)signo;
	run = false;
}

int main(int argc, char **argv)
{
	Server irc;
	signal(SIGINT, handleSignal);
	signal(SIGTERM, handleSignal);
	signal(SIGQUIT, handleSignal);
	irc.parse(argc, argv);
	return 0;
}