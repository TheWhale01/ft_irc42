#include "exception.hpp"

ErroneusNickNameException::ErroneusNickNameException(std::string const &str): _error_msg(new std::string(str)) {}
ErroneusNickNameException::~ErroneusNickNameException(void) throw() {delete _error_msg;}

const char *ErroneusNickNameException::what(void) const throw()
{
	_error_msg->insert(0, "ERROR ");
	_error_msg->insert(_error_msg->length(), " :Erroneus nickname\r\n");
	return (_error_msg->c_str());
}