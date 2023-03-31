#include <errno.h>
#include <cstring>
#include <stdexcept>

class ServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class ClientCouldNotConnectException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class CommandNotFoundException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class KillServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};