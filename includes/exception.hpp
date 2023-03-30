#include <errno.h>
#include <cstring>
#include <stdexcept>

class ServerException: public std::exception
{
	public:
		const char *what(void) const throw() {return (strerror(errno));}
};

class ClientCouldNotConnectException: public std::exception
{
	public:
		const char *what(void) const throw() {return ("Client could not connect.");}
};