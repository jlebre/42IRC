#include "../Server/server.hpp"

int main(int argc, char **argv)
{
	Server irc;
	try{
		irc.parse(argc, argv);

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}