#include "irc.hpp"

std::string print_user(Client const &client, Channel const &channel)
{
	std::string answer = ":" + client.getServerName() + " " + RPL_NAMREPLY + " " + client.getNickName() + " = " + channel.getChannelName() + " :";
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].second == 1)
			answer += "@" + channel.getChannelMembers()[i].first.getNickName();
		else
			answer += channel.getChannelMembers()[i].first.getNickName();
		if (i + 1 != channel.getChannelMembers().size())
			answer += " ";
	}
	answer += "\r\n" + format_reply(client, RPL_ENDOFNAMES, channel.getChannelName()) + "End of /NAMES list\r\n";
	return (answer);
}

void create_channel(Client &client, Server &serv, std::string const &name)
{
	Channel	new_channel(name);
	new_channel.addMemberToChannel(client, true);
	serv._channels.push_back(new_channel);
	std::string answer = format_msg(client) + "JOIN " + name + "\r\n";
	answer += print_user(client, new_channel);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void check_channel_syntax(Client const &client, std::string const &channel)
{
	std::string charset = " ,\a";
	if (channel.size() > 200)
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), channel));
	if (channel[0] != '&' && channel[0] != '#')
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), channel));
	for (size_t i = 0; i < channel.length(); i++)
		if (charset.find(channel[i]) != std::string::npos)
			throw (NoSuchChannelException(client.getServerName(), client.getNickName(), channel));
}

bool check_already_in_chan(std::string const &nickname, Channel const &channel)
{
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
		if (channel.getChannelMembers()[i].first.getNickName() == nickname)
			return (1);
	return (0); 
}

void join_channel(Client &client, Channel &channel)
{
	std::string answer;
	if (!check_already_in_chan(client.getNickName(), channel))
	{
		channel.addMemberToChannel(client, false);
		answer = format_msg(client) + "JOIN " + channel.getChannelName() + "\r\n";
		send_to_members_in_chan(channel, answer, client.getNickName());
	}
	if (!channel.getChannelTopic().empty())
		answer += format_reply(client, RPL_TOPIC, channel.getChannelName()) + channel.getChannelTopic() + "\r\n";
	answer += print_user(client, channel);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

bool join(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() != 1)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "JOIN"));
	check_channel_syntax(client, args[0]);
	for (size_t i = 0; i < serv.getChannels().size(); i++)
	{
		if (serv.getChannels()[i].getChannelName() == args[0])
		{
			join_channel(client, serv._channels[i]);
			return (1);
		}
	}
	create_channel(client, serv, args[0]);
	return (1);
}

bool part(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "PART"));
	Channel const &channel = search_channel(args[0], serv.getChannels());
	if (channel.getChannelName().empty())
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
	std::pair<Client, bool> const &member = search_user_in_channel(client, channel);
	if (member.first.getNickName().empty())
		throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
	if (args.size() >= 2)
		send_to_members_in_chan(channel, format_msg(client) + "PART " + args[0] + " :" + args[1] + "\r\n",  member.first.getNickName());
	else
		send_to_members_in_chan(channel, format_msg(client) + "PART " + args[0] + " :" + client.getNickName() + "\r\n",  member.first.getNickName());
	for (size_t i = 0; i < serv.getChannels().size(); i++)
	{
		if (serv.getChannels()[i].getChannelName() == args[0])
		{
			serv._channels[i].deleteChannelMember(member.first.getNickName());
			if (channel.getChannelMembers().size() == 0)
				serv._channels.erase(serv._channels.begin() + i);
			return (1);
		}
	}
	return (1);
}