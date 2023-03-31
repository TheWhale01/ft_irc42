#include "irc.hpp"

int pass(Server const &serv, std::vector<std::string> const &args)
{
	return (serv.getPasswd() == args[0]);
}