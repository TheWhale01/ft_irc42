#include "irc.hpp"

void Server::_who_user(Client const &client, Client const &target)
{
	std::string msg;

	if (target.getMode() & MODE_I)
		return ;
	msg = ":" + client.getServerName() + " " + RPL_WHOREPLY + " "
		+ client.getNickName() + " " + getChannels(target)[0].getChannelName()
		+ " " + target.getUserName() + " " + target.getServerName() + " "
		+ target.getServerName() + " H :1 " + target.getRealName() + "\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);
}

void Server::who(Client &client, std::vector<std::string> const &args)
{
	std::string msg;
	Client::iterator target;

	target = search_client(args[0]);
	if (target == _clients.end())
	{
		Channel::iter_channel chan = search_channel(args[0]);
		if (chan == _channels.end())
			return ;
		std::vector<std::pair<Client *, int> > members = chan->getChannelMembers();
		for (size_t i = 0; i < members.size(); i++)
			_who_user(client, *(members[i].first));
	}
	else
		_who_user(client, *(*target));
	msg = ":" + client.getServerName() + " " + RPL_ENDOFWHO + " " + client.getNickName()
		+ " " + args[0] + ":End of WHO list\r\n";
	send(client.getPoll().fd, msg.c_str(), msg.length(), 0);
}