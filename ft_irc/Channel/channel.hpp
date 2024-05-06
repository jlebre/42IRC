#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../Client/client.hpp"
# include "../Server/server.hpp"
# include "../includes/libs.hpp"

class Client;

typedef std::vector<Client*> ClientVector;
typedef ClientVector::iterator ClientIterator;

class Channel
{
    private:
        ClientVector _clients;
        std::string _channel_name;
        //mode_attr

    public:
        Channel();
        ~Channel();
        Channel(const Channel &src);
        Channel &operator=(const Channel &src);

        void init_channel(std::string channel_name);
        void shutdown_channel();
        void add_user(Client *client);
        void kick_user(Client *client);
};

#endif