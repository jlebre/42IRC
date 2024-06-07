#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "../includes/replies.hpp"
# include "../includes/libs.hpp"
# include "../Channel/channel.hpp"

class Channel;

class Client
{
	private: 
		struct sockaddr_in  _addr;
		socklen_t           _addr_size;
		std::string         _nickname;
		std::string         _username;
		std::string         _realname;
		int                 _fd;
		int                 _id;
		bool                _status;
		bool                _auth;
		bool                _registered;
		std::vector<Channel*> _channels_im_in;

	public:
		Client(struct sockaddr_in addr, socklen_t addr_size, int fd);
		Client(const Client &src);
		Client &operator=(const Client &src);
		~Client();

		static Client *newClient(sockaddr_in addr, socklen_t addr_size, int fd);

		// GETTERS
		int 					get_id();
		int 					get_fd();
		int 					get_status();
		std::string 			getNick();
		std::string 			getUser();
		std::string 			getReal();
		struct sockaddr_in		getAddr();
		bool					getAuth();
		bool					getRegistered();
		std::vector<Channel*> 	getChannels() const;

		// SETTERS
		void setStatus(bool status);
		void setNick(std::string nick);
		void setUser(std::string user);
		void setReal(std::string real);
		void setAddr(struct sockaddr_in addr);
		void setAuth(bool auth);
		void setRegistered(bool registered);
		void addChannel(Channel *channel);
		void removeChannel(Channel *channel);

		// CHECK
		bool is_operator(Channel& channel);
};

#endif