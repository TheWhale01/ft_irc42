#include "irc.hpp"

Client::Client(Server &serv) : _regist(0)
{
	_poll.fd = accept(serv.getPoll().fd, (struct sockaddr *)(&(serv.client_addr)), &(serv.addrlen));
	if (_poll.fd < 0)
		throw (ClientCouldNotConnectException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	std::cout << "(info) >> Client " << _poll.fd << " connected." << std::endl;
}

const pollfd_t &Client::getPoll(void) const
{
	return (this->_poll);
}

const bool &Client::getRegist(void) const
{
	return (this->_regist);
}

void Client::setRegist(bool val)
{
	this->_regist = val;
}

void Client::setUserName(std::string const &username) {_username = username;}
void Client::setNickName(std::string const &nickname) {_nickname = nickname;}
void Client::setRealName(std::string const &realname) {_realname = realname;}
void Client::setHostName(std::string const &hostname) {_hostname = hostname;}
void Client::setServerName(std::string const &servername) {_servername = servername;}