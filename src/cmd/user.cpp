#include "irc.hpp"

bool user(Client &client, Server const &serv, std::vector<std::string> const &args)
{
	// RFC 1459
	(void)serv;
	if (args.size() < 4)
	{
		std::cerr << "(error) >> " << ERR_NEEDMOREPARAMS << " need more params." << std::endl;
		return (false);
	}
	if (client.getRegist())
	{
		std::cerr << "(error) >> " << ERR_ALREADYREGISTRED << " user already registered." << std::endl;
		return (false);
	}
	client.setUserName(args[0]);
	client.setHostName(args[1]);
	client.setServerName(args[2]);
	client.setRealName(args[3]);
	return (true);
}