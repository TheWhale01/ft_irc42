#include "irc.hpp"

class Server;

class Client
{
	public:
		Client(Server &serv);
		~Client() {}

		const pollfd_t &getPoll(void) const;
		const bool &getRegist(void) const;
		void setRegist(bool val);

	private:
		pollfd_t 	_poll;
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		bool		_regist;
};