#include "irc.hpp"

void Server::kick(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 2)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "KICK"));
	Channel::iter_channel channel = search_channel(args[0]);
	if (channel == _channels.end())
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
	Channel::iter_member member = (*channel).search_user_in_channel(client.getNickName());
	if (member == (*channel).getChannelMembers().end())
		throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
	if ((*member).second == false)
		throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), args[0]));
	Channel::iter_member member2 = (*channel).search_user_in_channel(args[2]);
	if (member2 == (*channel).getChannelMembers().end())
		throw(UserNotInChannelException(client.getServerName(), client.getNickName(), args[0], args[1]));
	if (args.size() >= 3)
		send_to_members_in_chan(*channel, format_msg(client) + "KICK " + args[0] + " " + args[1] + " :" + args[2] + "\r\n", std::string());
	else
		send_to_members_in_chan(*channel, format_msg(client) + "KICK " + args[0] + " " + args[1] + " :" + args[1] + "\r\n", std::string());
	(*channel).deleteChannelMember(member2);
	if ((*channel).getChannelMembers().size() == 0)
		_channels.erase(channel);
}