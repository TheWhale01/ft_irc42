#include "irc.hpp"

Bot::Bot(void)
{
	setClientMode('i');
	_regist = true;
	_username = "bot";
	_nickname = "bot";
	_realname = "Super Bot";
	_hostname = "127.0.0.1";
	_servername = "irc.fckdup-server.com";
	_domain_name = "api.open-meteo.com";
}

Bot::~Bot(void) {}

void Bot::weather()
{
	addrinfo_t *addr;
	std::stringstream response;
	std::string request;

	_poll.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_poll.fd == -1)
		throw (ServerException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	bzero(&_hints, sizeof(_hints));
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(_domain_name.c_str(), "80", &_hints, &_server_info))
		throw (ServerException());
	for (addr = _server_info; addr != NULL; addr = addr->ai_next)
		if (connect(_poll.fd, addr->ai_addr, addr->ai_addrlen) != -1)
			break ;
	if (!addr)
	{
		std::cout << "(error) >> Bot could not connect." << std::endl;
		return ;
	}
	freeaddrinfo(_server_info);
	request = _get_request("/v1/forecast?latitude=48.85&longitude=2.35&current_weather=true&timezone=auto&hourly=cloudcover");
	send(_poll.fd, request.c_str(), request.length(), 0);
	std::cout << "(debug) >> request sent !" << std::endl;
	while (true)
	{
		if (poll(&_poll, 1, TIMEOUT) > 0)
		{
			size_t bytes = recv(_poll.fd, _buff, BUFF_SIZE, 0);
			if (bytes <= 0)
				break ;
			_buff[bytes] = '\0';
			response << _buff;
		}
	}
	std::cout << response.str() << std::endl;
	close(_poll.fd);
}

std::string Bot::_get_request(std::string endpoint)
{
	std::string request;

	request =
        "GET " + endpoint + " HTTP/1.1\r\n"
		"Host: " + _domain_name + "\r\n"
		"Connection: close\r\n"
		"\r\n";
	return (request);
}