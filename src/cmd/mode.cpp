#include "irc.hpp"

void Server::mode(Client &client, std::vector<std::string> const &args)
{
	if (args.size() == 1)
		return ;
	if (args[1] == "+i")
		return ;
	(void) client;
	iter_channel channel = search_channel(args[0]);
	(*channel).setChannelmode(args[1]);
}
