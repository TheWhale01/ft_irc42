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

Channel const &Server::search_channel(std::string const &name, std::vector<Channel> const &channel)
{
	Channel const &notfound = Channel();
	for (size_t i = 0; i < channel.size(); i++)
		if (channel[i].getChannelName() == name)
			return (channel[i]);
	return (notfound);
}

Client const &Server::search_client(std::string const &name, std::vector<Client> const &clients)
{
	Client const &notfound = Client();
	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].getNickName() == name)
			return (clients[i]);
	return (notfound);
}

iter_member Server::search_user_in_channel(Client const &client, Channel &channel)
{
	for (iter_member it = channel. it != channel. it++)
	{
	}
}

// std::pair<Client, bool> const &Server::search_user_in_channel(Client const &client, Channel const &channel)
// {
// 	std::pair<Client, bool> const &notfound = std::pair<Client, bool>();
// 	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
// 	{
// 		if (channel.getChannelMembers()[i].first.getNickName() == client.getNickName())
// 			return (channel.getChannelMembers()[i]);
// 	}
// 	return (notfound);
// }