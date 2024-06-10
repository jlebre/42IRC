#include "server.hpp"

/*
Usage:
/mode <#channel> <mode> [<mode params>]

Message to Client:
:<nick> MODE <channel> <mode> [<mode params>]
*/

void	Server::ChannelMode(Client *c, Channel *ch, mode_struct *modes) {
	(void)c;
	(void)ch;
	if (modes->type[1] == 'i')
		std::cout << "MODE INVITE" << std::endl;
	else if (modes->type[1] == 't')
		std::cout << "MODE TOPIC" << std::endl;
	else if (modes->type[1] == 'k')
		std::cout << "MODE KEY" << std::endl;
	else if (modes->type[1] == 'o')
		std::cout << "MODE OPERATOR" << std::endl;
	else if (modes->type[1] == 'l')
		std::cout << "MODE LIMIT" << std::endl;
	else if (modes->type[1] == 'b')
		std::cout << "MODE BAN" << std::endl;
	else if (modes->type[1] == 'v')
		std::cout << "MODE VOICE" << std::endl;
	else if (modes->type[1] == 'm')
		std::cout << "MODE MODERATED" << std::endl;
	else
		std::cout << "MODE UNKNOWN" << std::endl;
}

mode_struct parse_mode(std::vector<std::string> message) {
	mode_struct modes = {"", "", ""};
	size_t pos = message.size() - 1;
	if (pos > 3)
		pos = 3;
	switch (pos)
	{
	case 3:
		modes.param = message[3];
		// Intentional fall-through
	case 2:
		modes.type = message[2];
		// Intentional fall-through
	case 1:
		modes.channel = message[1];
		break;
	}
	return modes;
}

bool checkType(std::string type) {
	if (type.size() != 2)
		return false;
	if (type[0] != '+' && type[0] != '-')
		return false;
	return true;
}

bool Server::checkPermission(Channel &ch) {
	(void)ch;
	return true;
}



void		Server::mode(Client *client)
{
	std::cout << std::endl << "MODE" << std::endl << "---" << std::endl;
	mode_struct modes = parse_mode(parsed_message);
	std::cout << "channel: " << modes.channel << std::endl;
	std::cout << "type: " << modes.type << std::endl;
	std::cout << "param: " << modes.param << std::endl;
    if (modes.channel.empty())
	{
		reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "MODE"));
		return ;
	}
    try{
        find_channel(modes.channel);
    }catch(const std::exception &e){
		reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, modes.channel));
        return ;
    }
    Channel &channel = find_channel(modes.channel);
    if (!check_client_on_channel(client->getNick(), modes.channel))
    {
        reply(client, ERR_NOTONCHANNEL(this->_sock.ip, channel.get_name()));
        return ;
    }
	if (modes.type.empty())
	{
		reply(client, RPL_CHANNELMODEIS(this->_sock.ip, channel.get_name(), modes.type));
		return ;
	}
	if (!checkType(modes.type))
	{
		reply(client, ERR_UMODEUNKNOWNFLAG(this->_sock.ip));
		return ;
	}
	if (!checkPermission(channel))
	{
		std::cout << "FALTA FAZER" << std::endl;
	}
	if (modes.channel[0] == '#')
		ChannelMode(client, &channel, &modes);

}