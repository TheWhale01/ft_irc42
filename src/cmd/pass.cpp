#include "irc.hpp"

bool pass(Client &client, Server const &serv, std::vector<std::string> const &args)
{
	if (args.size() != 1)
	{
		std::cout << "ERROR 461 : PASS :Not enough parameters\n";
		return (0);
	}
	if (client.getRegist() == 1)
	{
		std::cout << "ERROR 462 : Unauthorized command (already registered)\n";
		return (0);
	}
	if (serv.getPasswd() != *args.begin())
	{
		std::cout << "ERROR : Password incorrect\n";
		return (0);
	}
	return (1);
}

bool nick(Client &client, Server const &serv, std::vector<std::string> const &args)
{
	(void) client;
	(void) serv;
	(void) args;
	// if (args.size == 0)
	// {
	// 	std::cout << "ERROR 431 :No nickname given.\n";
	// 	return (0);
	// }
	// if ()
	// {
	// 	std::cout << "ERROR 432 : " << *args.begin() << " :Erroneus nickname\n";
	// 	return (0);
	// }
	// for (TAB NICKNAME)
	// {
	// 	if (NICKNAME == args && client.fd != fd)
	// 	{
	// 		std::cout << "ERROR 433 : " << *args.begin() << " :Nickname is already in use\n";
	// 		return (0);
	// 	}
	
	// }
	// client.nickname = args;
	return (1);

}