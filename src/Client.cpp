#include "irc.hpp"
#include "Client.hpp"

Client::Client(Server &serv)
{
	_poll.fd = accept(serv.getPoll().fd, (struct sockaddr *)(&(serv.client_addr)), &(serv.addrlen));
	if (_poll.fd < 0)
		throw (ClientCouldNotConnectException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	std::cout << "(info) >> Client " << _poll.fd << " connected." << std::endl;
}