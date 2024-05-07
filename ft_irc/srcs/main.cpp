#include "../Server/server.hpp"

int main(int argc, char **argv)
{
	Server irc;
	irc.parse(argc, argv);
	return 0;
}