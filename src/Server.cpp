#include "irc.hpp"

Server::Server(int port, std::string passwd): _passwd(passwd)
{
	_addr.sin_family = AF_INET;
	_poll.fd = socket(_addr.sin_family, SOCK_STREAM, 0);
	if (_poll.fd == -1)
		throw (ServerException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);
	if (bind(_poll.fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw (ServerException());
	if (listen(_poll.fd, SIM_USERS) == -1)
		throw (ServerException());
	_clients.push_back(_poll);
	std::cout << "Server started on port: " << ntohs(_addr.sin_port) << std::endl;
	return ;
}

Server::~Server(void)
{
	for (size_t i = 0; i < _clients.size(); i++)
		close(_clients[i].fd);
	close(_poll.fd);
	return ;
}

void Server::run(void)
{
	while (true)
	{
		if (poll(_clients.data(), _clients.size(), -1) < 0)
			throw (ServerException());
		for (size_t i = 0; i < _clients.size(); i++)
		{
			if (_clients[i].revents & POLLIN)
			{
				if (_clients[i].fd == _poll.fd)
				{
					pollfd_t new_client;
					new_client.fd = accept(_poll.fd, (struct sockaddr *)&client_addr, &addrlen);
					if (new_client.fd == -1)
					{
						std::cerr << "(error) >> Client could not connect." << std::endl;
						break ;
					}
					new_client.events = POLLIN;
					new_client.revents = 0;
					_clients.push_back(new_client);
					std::cout << "(info) >> Client connected." << std::endl;
				}
				else
				{
					_bytes = recv(_clients[i].fd, _buff, BUFF_SIZE, 0);
					if (_bytes <= 0)
					{
						std::cout << "(info) >> Client " << _clients[i].fd << " disconnected." << std::endl;
						close(_clients[i].fd);
						_clients.erase(_clients.begin() + i);
						i--;
					}
					else
					{
						_buff[_bytes] = '\0';
						std::cout << "(Client: " << _clients[i].fd << ") >> " << _buff << std::endl;
						for (size_t j = 1; j < _clients.size(); j++)
							if (j != i)
								send(_clients[j].fd, _buff, _bytes, 0);
					}
				}
			}
		}
	}
}