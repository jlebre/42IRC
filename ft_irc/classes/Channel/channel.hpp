#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../Client/client.hpp"
# include "../Server/server.hpp"
# include "../includes/replies.hpp"
# include "../includes/libs.hpp"

class Client;

typedef struct s_modes
{
    bool _invite;
    bool _key;
    std::string _key_password;
    bool _limit;
    size_t _nb;
    bool _topic;
} t_modes;

class Channel
{
    private:
        std::vector<Client*> _members;
        std::vector<Client*> _invited;
        std::vector<Client*> _operators;
        std::string         _name;
        std::string         _password;
        std::string         _topic;
        t_modes             _mode;
        
    public:
        Channel();
        Channel(std::string name);
        Channel(std::string name, std::string password);
        ~Channel();
        Channel(const Channel &src);
        Channel &operator=(const Channel &src);

        void add_client(Client *client);
        void add_invited(Client *client);
        void add_operator(Client *client);
        void remove_operator(Client *client);
        void remove_client(Client *client);

        //Getters
        std::string get_name() const;
        std::string get_topic() const;
        std::string get_password() const;
        t_modes get_mode() const;
        std::vector<Client*> get_members() const;
        std::vector<Client*> get_invited() const;
        std::vector<Client*> get_operators() const;

        //Setters
        void set_name(std::string name);
        void set_topic(std::string topic);
        void set_password(std::string password);
        void set_mode(t_modes mode);
};

#endif