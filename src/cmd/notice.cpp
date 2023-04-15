#include "irc.hpp"

void Server::notice(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 2 || args[1].empty())
		return ;
	if (args[0][0] == '#' || args[0][0] == '&')
	{
		Channel::iter_channel channel = search_channel(args[0]);
		if (channel == _channels.end())
			return ;
		Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
		if (channel->getChannelModes() & MODE_N)
		{
			if (member == channel->getChannelMembers().end())
				return ;
		}
		if (channel->getChannelModes() & MODE_M) {
			if ((member == channel->getChannelMembers().end()) || (member->second == 0))
				return ;
		}
		send_to_members_in_chan(*channel, format_msg(client) + "NOTICE " + args[0] + " :" + args[1] + "\r\n", client.getNickName());
	}
	else
	{
		Client::iterator cli = search_client(args[0]);
		if (cli == _clients.end())
			return ;
		send_to_user(*(*cli), format_msg(client) + "NOTICE " + args[0] + " :" + args[1] + "\r\n");
	}
}