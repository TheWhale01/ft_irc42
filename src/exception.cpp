#include "exception.hpp"

const char *ServerException::what(void) const throw() {return (strerror(errno));}
const char *ClientCouldNotConnectException::what(void) const throw() {return ("Client could not connect.");}
const char *CommandNotFoundException::what(void) const throw() {return ("Command not found.");}