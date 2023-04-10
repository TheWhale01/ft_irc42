#include "irc.hpp"

// bool mode(Client &client, Server &serv, std::vector<std::string> const &args)
// {
// 	return (1);
// }

// bool invite(Client &client, Server &serv, std::vector<std::string> const &args)
// {
// 	return (1);
// }

bool kick(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() < 2)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "KICK"));
	size_t j = 0;
	Channel channel;
	for (; j < serv.getChannels().size(); j++)
	{
		if (serv.getChannels()[j].getChannelName() == args[0])
		{
			channel = serv.getChannels()[j];
			break;
		}
	}
	if (channel.getChannelName().empty())
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
	std::pair<Client, bool>	const &member = search_user_in_channel(client, channel);
	if (member.first.getNickName().empty())
		throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
	if (member.second == false)
		throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), args[0]));
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].first.getNickName() == args[1])
		{
			if (args.size() >= 3)
				send_to_members_in_chan(channel, format_msg(client) + "KICK " + args[0] + " " + args[1] + " :" + args[2] + "\r\n", std::string());
			else
				send_to_members_in_chan(channel, format_msg(client) + "KICK " + args[0] + " " + args[1] + " :" + args[1] + "\r\n", std::string());
			serv._channels[j].deleteChannelMember(args[1]);
			if (serv._channels[j].getChannelMembers().size() == 0)
				serv._channels.erase(serv._channels.begin() + j);
			return (1);
		}
	}
	throw(UserNotInChannelException(client.getServerName(), client.getNickName(), args[0], args[1]));
}

bool topic(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "TOPIC"));
	for (size_t i = 0; i < serv.getChannels().size(); i++)
	{
		if (serv.getChannels()[i].getChannelName() == args[0])
		{
			std::pair<Client, bool>	const &member = search_user_in_channel(client, serv.getChannels()[i]);
			if (member.first.getNickName().empty())
				throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
			if (args.size() == 2)
			{
				if ((serv.getChannels()[i].getChannelPermission() & MODE_T) != 0)
				{
					if (member.second == false)
						throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), args[0]));
				}
				serv._channels[i].setChannelTopic(args[1]);
				send_to_members_in_chan(serv.getChannels()[i], format_reply(client, RPL_TOPIC, serv.getChannels()[i].getChannelName()) + serv.getChannels()[i].getChannelTopic() + "\r\n", std::string());
			}
			else
			{
				if (serv.getChannels()[i].getChannelTopic().empty())
					send_to_user(client, format_reply(client, RPL_NOTOPIC, serv.getChannels()[i].getChannelName()) + "No topic is set\r\n");
				else
					send_to_user(client, format_reply(client, RPL_TOPIC, serv.getChannels()[i].getChannelName()) + serv.getChannels()[i].getChannelTopic() + "\r\n");
			}
			return (1);
		}
	}
	throw (NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
}