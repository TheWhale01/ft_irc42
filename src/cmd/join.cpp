#include "irc.hpp"

void Server::create_channel(Client &client, std::string const &name)
{
	Channel	new_channel(name);
	new_channel.addMemberToChannel(client, true);
	_channels.push_back(new_channel);
	std::string answer = format_msg(client) + "JOIN " + name + "\r\n";
	answer += print_all_user(client, new_channel);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void check_channel_syntax(Client const &client, std::string const &channel)
{
	std::string const &charset = " ,\a";
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
		if (channel.getChannelMembers()[i].first->getNickName() == nickname)
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
	answer += print_all_user(client, channel);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void Server::join(Client &client, std::vector<std::string> const &args)
{
	if (args.size() != 1)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "JOIN"));
	check_channel_syntax(client, args[0]);
	for (size_t i = 0; i < this->getChannels().size(); i++)
	{
		if (this->getChannels()[i].getChannelName() == args[0])
		{
			join_channel(client, this->_channels[i]);
			return ;
		}
	}
	create_channel(client, args[0]);
}