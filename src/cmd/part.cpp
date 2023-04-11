#include "irc.hpp"

void Server::part(Client &client, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "PART"));
	iter_channel channel = search_channel(args[0]);
	if (channel == _channels.end())
		throw (NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
	iter_member member = (*channel).search_user_in_channel(client.getNickName());
	if (member == (*channel).getChannelMembers().end())
		throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
	if (args.size() >= 2)
		send_to_members_in_chan(*channel, format_msg(client) + "PART " + args[0] + " :" + args[1] + "\r\n", std::string());
	else
		send_to_members_in_chan(*channel, format_msg(client) + "PART " + args[0] + " :" + client.getNickName() + "\r\n", std::string());
	(*channel).deleteChannelMember(member);
	if ((*channel).getChannelMembers().size() == 0)
		_channels.erase(channel);
}