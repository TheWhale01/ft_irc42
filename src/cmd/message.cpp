#include "irc.hpp"

void send_to_members_in_chan(Client const &client, Channel const &channel, std::string const &name, std::string const &message)
{
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].first.getNickName() == name)
		{
			for (size_t j = 0; j < channel.getChannelMembers().size(); j++)
				send(channel.getChannelMembers()[j].first.getPoll().fd, message.c_str(), message.length(), 0);
			return ;
		}
	}
	throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
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

std::string format_msg(std::string const &nickname, std::string const &username, std::string const &hostname, std::string const &message)
{
	return ("PRIVMSG " + nickname + "!" + username + "@" + hostname + ": " + message);
}

void send_to_user(Client const &client, std::string const &message)
{
	send(client.getPoll().fd, message.c_str(), message.length(), 0);
}

bool privmsg(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args.size() < 2 || args[1].empty())
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args[0][1] == '#' || args[0][1] == '&')
	{
		send_to_members_in_chan(client, search_channel(client, args[0], serv.getChannels()), client.getNickName(), format_msg(client.getNickName(), client.getUserName(), client.getServerName(), args[1]));;
	}
	else
	{
		std::cout <<  format_msg(client.getNickName(), client.getUserName(), client.getServerName(), args[1]) << std::endl;
		send_to_user(search_client(client, args[0], serv.getClients()), format_msg(client.getNickName(), client.getUserName(), client.getServerName(), args[1]));
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