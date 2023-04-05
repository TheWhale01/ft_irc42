#include "irc.hpp"

bool quit(Client &client, Server &serv, std::vector<std::string> const &args)
{
	std::string quit_msg = (args.size() ? args[0] : "");

	size_t i = 0;
	while (i < serv._pollfds.size() && serv._pollfds[i].fd != client.getPoll().fd)
		i++;
	std::cout << "(info) >> Client " << serv._pollfds[i].fd << " disconnected." << std::endl;
	// Send message to all clients in channel.
	close(serv._pollfds[i].fd);
	serv._pollfds.erase(serv._pollfds.begin() + i);
	serv._clients.erase(serv._clients.begin() + (i - 1));
	return (true);
}