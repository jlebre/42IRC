#include "server.hpp"

/*
void Server::execute(MsgVector& messages, Client* cli)
{
	(void)messages;
	(void)cli;
	N_CommandsIterator it;
	std::string cmd;
	MsgVector msg;

	if (messages.empty())
		return;
	cmd = messages[0];
	messages.erase(messages.begin());

	it = _commands.find(cmd);
	if (it == _commands.end())
	{
		//Send error message
		return;
	}

	if (cli->is_registered())
	{
		it->second->set_command(messages, cli);
		it->second->execute(*this, messages, cli);
		return;
	}

	if (cmd == "PASS")
	{
		it->second->set_command(messages, cli);
		it->second->execute(*this, messages, cli);
		return;
	}
	else if (cmd == "NICK" || cmd == "USER")
	{
		it->second->set_command(messages, cli);
		it->second->execute(*this, messages, cli);
		return;
	}
	//cli->send_msg_to_client(cli, msg);
}
*/