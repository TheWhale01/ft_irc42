#include "irc.hpp"

void Server::quit(Client &client, std::vector<std::string> const &args)
{
	std::string quit_msg = (args.size() ? args[0] : "");

	size_t i = 0;
	while (i <this->_pollfds.size() && this->_pollfds[i].fd != client.getPoll().fd)
		i++;
	std::cout << "(info) >> Client " << this->_pollfds[i].fd << " disconnected." << std::endl;
	// Send message to all clients in channel.
	close(this->_pollfds[i].fd);
	this->_pollfds.erase(this->_pollfds.begin() + i);
	this->_clients.erase(this->_clients.begin() + (i - 1));
}