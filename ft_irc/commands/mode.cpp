#include "server.hpp"

bool checkType(std::string type) {
	if (type.size() != 2)
		return false;
	if (type[0] != '+' && type[0] != '-')
		return false;
	return true;
}

Channel	*Server::get_channel(std::string channel_name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i]->get_name() == channel_name)
			return _channels[i];
	}
	throw std::exception();
}

void Server::mode(Client *client)
{
    std::cout << std::endl << "MODE" << std::endl;

    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(this->_sock.ip, "MODE"));
        return;
    }
    if (parsed_message.size() < 2)
    {
        reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "MODE"));
        return;
    }
    std::string channel_name = parsed_message[1];
    Channel *channel;
    
    if (check_if_channel_exists(channel_name))
        channel = get_channel(channel_name);
    else
    {
        reply(client, ERR_NOSUCHCHANNEL(this->_sock.ip, channel_name));
        return;
    }

    if (!check_client_on_channel(client->getNick(), channel_name))
    {
        reply(client, ERR_NOTONCHANNEL(this->_sock.ip, channel_name));
        return;
    }

    t_modes mode = channel->get_mode();

    if (!is_operator(client, channel_name))
    {
        reply(client, ERR_CHANOPRIVSNEEDED(this->_sock.ip, channel_name));
        return;
    }

    for (size_t i = 2; i < parsed_message.size(); i++)
    {
        std::string new_mode = parsed_message[i];
        if (!checkType(new_mode))
        {
            reply(client, ERR_UNKNOWNMODE(this->_sock.ip, new_mode));
            return;
        }

        bool ver = (new_mode[0] == '+');

        if (new_mode[1] == 'i')
        {
            std::cout << "MODE INVITE" << std::endl;
            mode._invite = ver;
        }
        else if (new_mode[1] == 't')
        {
            std::cout << "MODE TOPIC" << std::endl;
            mode._topic = ver;
        }
        else if (new_mode[1] == 'k')
        {
            if (ver && parsed_message.size() > i + 1)
            {
                mode._key = true;
                mode._key_password = parsed_message[++i];
                std::cout << "MODE KEY SET" << std::endl;
            }
            else if (!ver)
            {
                mode._key = false;
                mode._key_password.clear();
                std::cout << "MODE KEY UNSET" << std::endl;
            }
        }
        else if (new_mode[1] == 'l')
        {
            if (ver && parsed_message.size() > i + 1)
            {
                mode._limit = true;
                mode._nb = std::atoi(parsed_message[++i].c_str());
                std::cout << "MODE LIMIT SET" << std::endl;
            }
            else if (!ver)
            {
                mode._limit = false;
                mode._nb = 0;
                std::cout << "MODE LIMIT UNSET" << std::endl;
            }
        }
        else if (new_mode[1] == 'o')
        {
            std::cout << "MODE OPERATOR" << std::endl;
            if (parsed_message.size() > i + 1)
            {
                std::string target_nick = parsed_message[++i];
				Client *new_operator;
				if (check_if_client_exists(target_nick))
					new_operator = find_client(target_nick);
				else
				{
					reply(client, ERR_NOSUCHNICK(this->_sock.ip, target_nick));
					return ;
				}
                if (ver)
                {
                    std::cout << "MODE OPERATOR ADD" << std::endl;
                    channel->add_operator(new_operator);
                }
                else
                {
                    std::cout << "MODE OPERATOR REMOVE" << std::endl;
                    channel->remove_operator(new_operator);
                }
            }
            else
            {
                reply(client, ERR_NEEDMOREPARAMS(this->_sock.ip, "MODE"));
                return;
            }
        }
        else
            std::cout << "MODE UNKNOWN" << std::endl;
        channel->set_mode(mode);
        reply(client, MODE_CHANNELMSG(channel_name, new_mode));
    }
}

