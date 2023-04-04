#include "irc.hpp"

class Server;

class Client
{
	public:
		Client(Server &serv);
		~Client();

		const pollfd_t &getPoll(void) const;
		const bool &getRegist(void) const;

		void setRegist(bool val);
		void setUserName(std::string const &username);
		void setNickName(std::string const &nickname);
		void setRealName(std::string const &realname);
		void setHostName(std::string const &hostname);
		void setServerName(std::string const &servername);

		const std::string &getNickName(void) const ;
		const std::string &getUserName(void) const ;
		const std::string &getServerName(void) const ;

	private:
		pollfd_t 	_poll;
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;
		std::string _hostname;
		std::string _servername;
		bool		_regist;
		bool		_can_co;
};