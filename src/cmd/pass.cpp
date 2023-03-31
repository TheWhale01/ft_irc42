#include "irc.hpp"

bool pass(Server const &serv, std::string const &pass)
{
	return (serv.getPasswd() == pass);
}