#include "irc.hpp"

class Server;

class Client
{
	public:
		Client(Server &serv);
		~Client() {}

		const pollfd_t &getPoll(void) const {return (_poll);}

	private:
		pollfd_t _poll;
		std::string _username;
		std::string _nickname;
		std::string _realname;
};