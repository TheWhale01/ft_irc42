#include "irc.hpp"

bool cap(Client &client, Server &serv, std::vector<std::string> const &args)
{
	(void)serv;
	if (!args.size())
		return (false);
	if (args[0] == "LS")
		send(client.getPoll().fd, "", 0, 0);
	return (true);
}