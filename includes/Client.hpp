#include "irc.hpp"

class Client
{
	public:
		Client(Server &serv);
		~Client() {}

		const pollfd_t &getPoll(void) const {return (_poll);}

	private:
		pollfd_t _poll;
		std::string _usrname;
		std::string _nickname;
};