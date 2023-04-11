#include "irc.hpp"

void send_to_user(Client const &client, std::string const &message)
{
	std::cout << "message top one member: " << message << std::endl;
	send(client.getPoll().fd, message.c_str(), message.length(), 0);
}

void send_to_members_in_chan(Channel const &channel, std::string const &message, std::string const &sender)
{
	std::cout << "message all members: " << message << std::endl;
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

void Server::privmsg(Client &client, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args.size() < 2 || args[1].empty())
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args[0][0] == '#' || args[0][0] == '&')
	{
		Channel const &channel = search_channel(args[0], this->getChannels());
		if (channel.getChannelName().empty())
			throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
		std::pair<Client, bool>	const &member = search_user_in_channel(client, channel);
		if (member.first.getNickName().empty())
			throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
		send_to_members_in_chan(channel, format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n", member.first.getNickName());
	}
	else
	{
		Client const &cli = search_client(args[0], this->getClients());
		if (cli.getNickName().empty())
			throw (NoSuchNickException(client.getServerName(), client.getNickName(), args[0]));
		send_to_user(cli, format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n");
	}
}

void Server::notice(Client &client, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		return ;
	if (args.size() < 2 || args[1].empty())
		return ;
	if (args[0][0] == '#' || args[0][0] == '&')
	{
		Channel const &channel = search_channel(args[0], this->getChannels());
		if (channel.getChannelName().empty())
			return ;
		std::pair<Client, bool>	const &member = search_user_in_channel(client, channel);
		if (member.first.getNickName().empty())
			return ;
		send_to_members_in_chan(channel, format_msg(client) + "NOTICE " + args[0] + " :" + args[1] + "\r\n", member.first.getNickName());
	}
	else
	{
		Client const &cli = search_client(args[0], this->getClients());
		if (cli.getNickName().empty())
			return ;
		send_to_user(cli, format_msg(client) + "NOTICE " + args[0] + " :" + args[1] + "\r\n");
	}
}
