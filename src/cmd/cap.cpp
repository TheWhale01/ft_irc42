#include "irc.hpp"

void Server::cap(Client &client, std::vector<std::string> const &args)
{
	if (!args.size())
		return ;
	if (args[0] == "LS")
		send(client.getPoll().fd, "", 0, 0);
}