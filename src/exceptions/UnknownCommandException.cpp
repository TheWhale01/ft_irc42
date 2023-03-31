#include "exception.hpp"

UnknownCommandException::UnknownCommandException(std::string const &str): _error_msg(new std::string(str)) {}
UnknownCommandException::~UnknownCommandException(void) throw() {delete _error_msg;}

const char *UnknownCommandException::what(void) const throw()
{
	_error_msg->insert(0, "ERROR ");
	_error_msg->insert(_error_msg->length(), " :Unkown command\r\n");
	return (_error_msg->c_str());
}