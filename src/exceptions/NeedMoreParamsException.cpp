#include "exception.hpp"

NeedMoreParamsException::NeedMoreParamsException(std::string const &str): _error_msg(new std::string(str)) {}
NeedMoreParamsException::~NeedMoreParamsException(void) throw() {delete _error_msg;}

const char *NeedMoreParamsException::what(void) const throw()
{
	_error_msg->insert(0, "ERROR ");
	_error_msg->insert(_error_msg->length(), " :Not enough parameters\r\n");
	return (_error_msg->c_str());
}