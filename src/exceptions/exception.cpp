#include "exception.hpp"

const char *KillServerException::what(void) const throw() {return ("(info) >> Stopping server.");}
const char *AlreadyRegisteredExcpetion::what(void) const throw() {return ("ERROR :You may not reregister");}
const char *NoNickNameGivenException::what(void) const throw() {return ("ERROR :No nickname given");}
const char *ServerException::what(void) const throw() {return (strerror(errno));}
const char *ClientCouldNotConnectException::what(void) const throw() {return ("(error) >> Client could not connect.");}