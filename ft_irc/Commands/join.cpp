#include "server.hpp"

void		Server::join(Client& client)
{
    std::cout << "JOIN COMMAND\n";

    Channel channel;

    //Get the name after # from the message. Message is _message.
    std::string channel_name = _message.substr(_message.find("#") + 1);

    channel.set_name(channel_name);
    channel.add_client(client);
    channel.add_operator(client);
    channel.set_topic("");
    _channels.push_back(channel);

    //Send message to all clients in the channel
    std::string message = ":" + client.getNick() + " JOIN " + channel_name + "\n";
    reply_all(message);
}
