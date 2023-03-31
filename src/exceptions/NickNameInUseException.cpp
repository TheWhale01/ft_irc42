#include "exception.hpp"

NickNameInUseException::NickNameInUseException(std::string const &str): _error_msg(new std::string(str)) {}
NickNameInUseException::~NickNameInUseException(void) throw() {delete _error_msg;}

const char *NickNameInUseException::what(void) const throw()
{
	_error_msg->insert(0, "ERROR ");
	_error_msg->insert(_error_msg->length(), " :Nickname is already in use\r\n");
	return (_error_msg->c_str());
}