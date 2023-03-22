#include "irc.hpp"
#include "Server.hpp"

Server::Server(int port, std::string passwd): _port(port), _passwd(passwd)
{
	_addr.sin_family = AF_INET;
	_fd = socket(_addr.sin_family, SOCK_STREAM, 0);
	if (_fd == -1)
		throw (Server::ServerException());
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(_port);
	if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw (Server::ServerException());
	if (listen(_fd, SIM_USERS) == -1)
		throw (Server::ServerException());
	std::cout << "Server started on port: " << _port << std::endl;
	return ;
}