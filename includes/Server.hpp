#pragma once
#include <string>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <netinet/in.h>

class Server
{
	public:
		class ServerException: public std::exception
		{
			public:
				const char *what(void) const throw() {return (strerror(errno));}
		};

		Server(int port, std::string passwd);
		~Server(void);

		const int &getFd(void) const {return (_fd);}
		const struct sockaddr_in &getAddr(void) const {return (_addr);}
	
	private:
		int _fd;
		int _port;
		std::string _passwd;
		struct sockaddr_in _addr;
};