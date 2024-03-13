#include "server.hpp"

void close_port(t_env *e)
{
	std::cout << "Closing port: " << e->port << std::endl;
	close(e->port);
}

void send_info(t_env *e)
{
	std::string user = "test";
	std::string nick = "test";
	std::string user_message = "USER " + std::string(user) + " 0 * :" + std::string(user) + "\r\n";
	std::string nick_message = "NICK " + std::string(nick) + "\r\n";
	send(e->port, "Hello", 5, 0);
	send(e->port, user_message.c_str(), user_message.length(), 0);
	send(e->port, nick_message.c_str(), nick_message.length(), 0);
}