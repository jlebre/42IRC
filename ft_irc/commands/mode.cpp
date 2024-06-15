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
		if (compare_channel_name(_channels[i]->get_name(),channel_name))
			return _channels[i];
	}
	throw std::exception();
}

void Server::mode(Client *client)
{
    if (!client->getRegistered())
    {
        reply(client, ERR_NOTREGISTERED(client->getNick()));
        return;
    }
    std::string channel_name = parsed_message[1];
    Channel *channel;

    if (check_if_channel_exists(channel_name))
        channel = get_channel(channel_name);
    else
    {
        reply(client, ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
        return;
    }

    if (!check_client_on_channel(client->getNick(), channel_name))
    {
        reply(client, ERR_NOTONCHANNEL(client->getNick(), channel_name));
        return;
    }


    for (size_t i = 2; i < parsed_message.size(); i++)
    {
        t_modes mode = channel->get_mode();
    
        std::string new_mode = parsed_message[i];
        if (!checkType(new_mode))
        {
            reply(client, ERR_UMODEUNKNOWNFLAG(client->getNick()));
            return;
        }

        if (!is_operator(client, channel_name))
        {
            reply(client, ERR_CHANOPRIVSNEEDED(client->getNick(), channel_name));
            return;
        }
    
        bool ver = (new_mode[0] == '+');

        if (new_mode[1] == 'i')
            mode._invite = ver;
        else if (new_mode[1] == 't')
            mode._topic = ver;
        else if (new_mode[1] == 'k')
        {
            if (ver && parsed_message.size() > i + 1)
            {
                mode._key = true;
                std::string password = parsed_message[++i];
                if (password.length() < 1 || password.length() > 16)
                {
                    std::cerr << "Password should be between 1 and 16 characters\n";
                    return ;
                }
                if (password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
                {
                    std::cerr << "Password should contain only alphanumeric characters\n";
                    return ;
                }
                mode._key_password = password;
            }
            else if (!ver)
            {
                mode._key = false;
                mode._key_password.clear();
            }
            new_mode = new_mode + " " + parsed_message[i];
        }
        else if (new_mode[1] == 'l')
        {
            if (ver && parsed_message.size() > i + 1)
            {
                mode._limit = true;
                std::string limit = parsed_message[++i];
                if (limit.find_first_not_of("0123456789") != std::string::npos)
                {
                    std::cout << "Limit should be a number" << std::endl;
                    return ;
                }
                int limit_i = atoi(limit.c_str());
                if (limit_i < 1 || limit_i > 200)
                {
                    std::cerr << "Limit should be a number between 1 and 200\n";
                    return ;
                }
                mode._nb = limit_i;
            }
            else if (!ver)
            {
                mode._limit = false;
                mode._nb = 0;
            }
            new_mode = new_mode + " " + parsed_message[i];
        }
        else if (new_mode[1] == 'o')
        {
            if (parsed_message.size() > i + 1)
            {
                std::string target_nick = parsed_message[++i];
				Client *new_operator;
				if (check_if_client_exists(target_nick))
					new_operator = find_client(target_nick);
				else
				{
					reply(client, ERR_NOSUCHNICK(client->getNick(), target_nick));
					return ;
				}
                if (ver)
                {
                    channel->add_operator(new_operator);
                    update_list(channel);
                }
                else
                {
                    if (client->getNick() == new_operator->getNick())
                    {
                        reply(client, "You can't remove yourself from operator list");
                        return;
                    }
                    channel->remove_operator(new_operator);
                    update_list(channel);
                }
                new_mode = new_mode + " " + target_nick;
            }
            else
            {
                reply(client, ERR_NEEDMOREPARAMS(channel_name, client->getNick(), "MODE"));
                return;
            }
        }
        else
            reply(client, ERR_UMODEUNKNOWNFLAG(client->getNick()));
        channel->set_mode(mode);
        for (size_t i = 0; i < channel->get_members().size(); i++)
            reply(channel->get_members()[i], RPL_CHANNELMODEIS(client->getNick(), channel_name, new_mode));
    }
    //std::cout << std::endl << "MODE" << std::endl;
}
