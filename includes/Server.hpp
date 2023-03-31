#pragma once
#include "irc.hpp"

class Server
{
	public:
		socklen_t addrlen;
		sockaddr_in_t client_addr;

		Server(int port, std::string passwd);
		~Server(void);

		const pollfd_t &getPoll(void) const {return (_poll);}
		const sockaddr_in_t &getAddr(void) const {return (_addr);}
		const std::string &getPasswd(void) const {return (_passwd);}

		void run(void);
	
	private:
		int _bytes;
		char _buff[BUFF_SIZE + 1];
		pollfd_t _poll;
		std::string _passwd;
		sockaddr_in_t _addr;
		std::vector<pollfd_t> _clients;
};