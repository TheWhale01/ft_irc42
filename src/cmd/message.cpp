#include "irc.hpp"

std::string format_msg(Client const &client) //:<nickname>!<username>@<hostname> "
{
	return (":" + client.getNickName() + "!" + client.getUserName() + "@" + client.getServerName() + " ");
}

Channel const &search_channel(Client const &client, std::string const &name, std::vector<Channel> const &channel)
{
	for (size_t i = 0; i < channel.size(); i++)
		if (channel[i].getChannelName() == name)
			return (channel[i]);
	throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
}

Client const &search_client(Client const &client, std::string const &name, std::vector<Client> const &clients)
{
	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].getNickName() == name)
			return (clients[i]);
	throw (NoSuchNickException(client.getServerName(), client.getNickName(), name));
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

void send_to_user(Client const &client, std::string const &message)
{
	send(client.getPoll().fd, message.c_str(), message.length(), 0);
}

void send_to_members_in_chan(Channel const &channel, std::string const &message, std::string const &sender)
{
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (!sender.empty())
		{
			if (channel.getChannelMembers()[i].first.getNickName() != sender)
				send(channel.getChannelMembers()[i].first.getPoll().fd, message.c_str(), message.length(), 0);
		}
		else
			send(channel.getChannelMembers()[i].first.getPoll().fd, message.c_str(), message.length(), 0);
	}
}

bool privmsg(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args.size() < 2 || args[1].empty())
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args[0][0] == '#' || args[0][0] == '&')
	{
		Channel const &channel = search_channel(client, args[0], serv.getChannels());
		std::string const &nickname = search_user_in_channel(client, channel);
		if (nickname.empty())
			throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
		send_to_members_in_chan(channel, format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n", nickname);
	}
	else
	{
		Client const &cli = search_client(client, args[0], serv.getClients());
		send_to_user(cli, format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n");
	}
	return (1);
}

bool notice(Client &client, Server &serv, std::vector<std::string> const &args)
{
	(void) client;
	(void) serv;
	(void) args;
	return (1);
}