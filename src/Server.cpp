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
	_pollfds.push_back(_poll);
	std::cout << "Server started on port: " << ntohs(_addr.sin_port) << std::endl;
	return ;
}

Server::~Server(void)
{
	for (size_t i = 0; i < _pollfds.size(); i++)
		close(_pollfds[i].fd);
	return ;
}

const pollfd_t &Server::getPoll(void) const {return (_poll);}
const sockaddr_in_t &Server::getAddr(void) const {return (_addr);}
const std::string &Server::getPasswd(void) const {return (_passwd);}

void Server::run(void)
{
	while (true)
	{
		if (poll(_pollfds.data(), _pollfds.size(), -1) < 0)
			throw (ServerException());
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents & POLLIN)
			{
				if (_pollfds[i].fd == _poll.fd)
				{
					try
					{
						Client new_client(*this);
						_pollfds.push_back(new_client.getPoll());
						_clients.push_back(new_client);
					}
					catch (const std::exception& e) {std::cerr << e.what() << std::endl;}
				}
				else
				{
					_bytes = recv(_pollfds[i].fd, _buff, BUFF_SIZE, 0);
					if (_bytes <= 0)
					{
						std::cout << "(info) >> Client " << _pollfds[i].fd << " disconnected." << std::endl;
						close(_pollfds[i].fd);
						_pollfds.erase(_pollfds.begin() + i);
						i--;
					}
					else
					{
						_buff[_bytes] = '\0';
						std::cout << "(Client: " << _pollfds[i].fd << ") >> " << _buff;
						for (size_t j = 1; j < _clients.size(); j++)
							if (j != i)
								send(_pollfds[j].fd, _buff, _bytes, 0);
					}
				}
			}
		}
	}
}