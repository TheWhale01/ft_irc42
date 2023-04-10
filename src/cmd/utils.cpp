#include "irc.hpp"

std::string format_msg(Client const &client)
{
	return (":" + client.getNickName() + "!" + client.getUserName() + "@" + client.getServerName() + " ");
}

Channel const &search_channel(std::string const &name, std::vector<Channel> const &channel)
{
	Channel const &notfound = Channel();
	for (size_t i = 0; i < channel.size(); i++)
		if (channel[i].getChannelName() == name)
			return (channel[i]);
	return (notfound);
}

Client const &search_client(std::string const &name, std::vector<Client> const &clients)
{
	Client const &notfound = Client();
	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].getNickName() == name)
			return (clients[i]);
	return (notfound);
}

std::string const search_user_in_channel(Client const &client, Channel const &channel)
{
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].first.getNickName() == client.getNickName())
			return (channel.getChannelMembers()[i].first.getNickName());
	}
	return (std::string());
}