#include "irc.hpp"

std::string format_reply(Client const &client, std::string const &code, std::string const &name)
{
	if (name.empty())
		return (":" + client.getServerName() + " " + code + " " + client.getNickName() + " :");
	return (":" + client.getServerName() + " " + code + " " + client.getNickName() + " " + name + " :");
}

std::string format_msg(Client const &client)
{
	return (":" + client.getNickName() + "!" + client.getUserName() + "@" + client.getServerName() + " ");
}

Channel *search_channel(std::string const &name, std::vector<Channel> const &channel)
{
	for (size_t i = 0; i < channel.size(); i++)
		if (channel[i].getChannelName() == name)
			return (channel[i]);
	return (NULL);
}

Client *search_client(std::string const &name, std::vector<Client> const &clients)
{
	for (size_t i = 0; i < clients.size(); i++)
		if (clients)
			return (clients[i]);
	return (NULL);
}

iter_member search_user_in_channel(Client const &client, Channel const &channel)
{
	for (iter_member it = _channe.; i < channel.; i++)
	{
		if (channel->getChannelMembers()[i].first.getNickName() == client.getNickName())
			return (channel.getChannelMembers()[i]);
	}
	return (NULL);
}