#include "server.hpp"

/*
Usage:
/mode <#channel> <mode> [<mode params>]

Message to Client:
:<nick> MODE <channel> <mode> [<mode params>]
*/

//# define ERR_NOTREGISTERED(client, server) (":" + server + " 451 " + client + " :You have not registered" + "\r\n")



void Server::ChannelMode(Client &c, mode_struct modes){
	// if (!c.getRegistered()) {
	//	reply(c, ERR_NOTREGISTERED);
	// 	return ;
	// }
	if (modes.type[0] == "+" || modes.type[0] == "-")
		changeMode(c, modes);
}

void Server::mode(Client &client)
{
	std::cout << std::endl << "MODE" << std::endl << "---" << std::endl;
	mode_struct modes = {"", "", ""};
	size_t pos = parsed_message.size() - 1;
	if (pos > 3)
		pos = 3;
	switch (pos)
	{
	case 3:
		modes.param = parsed_message[3];
		// Intentional fall-through
	case 2:
		modes.type = parsed_message[2];
		// Intentional fall-through
	case 1:
		modes.channel = parsed_message[1];
		break;
	}
	if (modes.channel[0] == '#')
		ChannelMode(client, modes);
	//std::cout << "Channel->" << modes.channel << " Type->" << modes.type << " Param->" << modes.param << std::endl;
	std::string message = ":" + client.getNick() + " MODE " + client.getNick() + " :" + modes.type + "\r\n";
    reply_all(message);
}