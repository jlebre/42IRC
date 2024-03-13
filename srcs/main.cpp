#include "server.hpp"

int main(int argc, char **argv)
{
	IRCServer irc;
	irc.start(argc, argv);
	return 0;
}