#include "irc.hpp"

void Server::pass(Client &client, std::vector<std::string> const &args)
{
	if (args.size() != 1)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "PASS"));
	if (client.getRegist())
		throw (AlreadyRegistredException(client.getServerName(), client.getNickName()));
	if (this->getPasswd() != *args.begin())
		std::cerr << "(error) >> Password incorrect\n";
}