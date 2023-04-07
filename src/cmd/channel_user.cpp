#include "irc.hpp"

std::string format_reply(Client const &client, std::string const &code, std::string const &name)
{
	return (":" + client.getServerName() + " " + code + " " + client.getNickName() + " " + name + " :");
}

std::string print_user(Client const &client, Channel const &channel)
{
	std::string answer = ":" + client.getServerName() + " 353 " + client.getNickName() + " = " + channel.getChannelName() + " :";
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].second._operator == 1)
			answer += "@" + channel.getChannelMembers()[i].first.getNickName();
		else
			answer += channel.getChannelMembers()[i].first.getNickName();
		if (i + 1 != channel.getChannelMembers().size())
			answer += " ";
	}
	answer += "\r\n" + format_reply(client, "366", channel.getChannelName()) + "End of NAMES list\r\n";
	return (answer);
}

void create_channel(Client &client, Server &serv, std::string const &name)
{
	Channel	new_channel(name);
	new_channel.addMemberToChannel(client, 2);
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
		channel.addMemberToChannel(client, 0);
		answer = format_msg(client) + "JOIN " + channel.getChannelName() + "\r\n";
	}
	if (channel.getChannelTopic().empty())
		answer += format_msg(client) + format_reply(client, "331", channel.getChannelName()) + "No topic is set.\r\n";
	else
		answer += format_msg(client) + format_reply(client, "332", channel.getChannelName()) + channel.getChannelTopic() + "\r\n";
	std::cout << answer << std::endl;
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