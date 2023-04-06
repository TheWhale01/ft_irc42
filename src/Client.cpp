#include "irc.hpp"

Client::Client(Server &serv) : _nickname(""), _regist(false)
{
	_poll.fd = accept(serv.getPoll().fd, (struct sockaddr *)(&(serv.client_addr)), &(serv.addrlen));
	if (_poll.fd < 0)
		throw (ClientCouldNotConnectException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	_can_co = false;
	std::cout << "(info) >> Client " << _poll.fd << " connected." << std::endl;
}

Client::~Client(void) {}

const bool &Client::getRegist(void) const {return (_regist);}
const pollfd_t &Client::getPoll(void) const {return (_poll);}
const std::string &Client::getNickName(void) const {return (_nickname);}
const std::string &Client::getUserName(void) const {return (_username);}
const std::string &Client::getServerName(void) const {return (_servername);}

void Client::setRegist(bool val) {_regist = val;}
void Client::setUserName(std::string const &username) {_username = username;}
void Client::setNickName(std::string const &nickname) {_nickname = nickname;}
void Client::setRealName(std::string const &realname) {_realname = realname;}
void Client::setHostName(std::string const &hostname) {_hostname = hostname;}
void Client::setServerName(std::string const &servername) {_servername = servername;}