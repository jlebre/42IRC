#include "server.hpp"

IRCServer::IRCServer(): _fds(MAX_CLIENTS + 1)
{
	std::cout << "IRCServer constructor" << std::endl;
}

IRCServer::~IRCServer()
{
	std::cout << "IRCServer destructor" << std::endl;
}

void IRCServer::kick(t_env *e, int fd)
{
	(void)e;
	std::cout << "Kicking: " << fd << std::endl;
	close(fd);
	//e->clients.erase(fd);
}

void IRCServer::invite(t_env *e, int fd)
{
	(void)e;
	std::cout << "Inviting: " << fd << std::endl;
	//e->clients.insert(fd);
}

void IRCServer::topic(t_env *e, std::string topic)
{
	(void)e;
	std::cout << "Setting topic: " << topic << std::endl;
	//e->vars.topic = topic;
}

void IRCServer::mode(t_env *e, std::string mode, char flag)
{
	(void)e;
	std::cout << "Setting mode: " << mode << std::endl;
	//e->vars.mode = mode;
	switch (flag)
	{
	case 'i':
		std::cout << "Set/remove Invite-only channel\n";
		break;
	case 't':
		std::cout << " Set/remove the restrictions of the TOPIC command to channel operators\n";
		break;
	case 'k':
		std::cout << "Set/remove the channel key (password)\n";
		break;
	case 'o':
		std::cout << " Give/take channel operator privilege\n";
		break;
	case 'l':
		std::cout << " Set/remove the user limit to channel\n";
		break;
	
	default:
		break;
	}
}
