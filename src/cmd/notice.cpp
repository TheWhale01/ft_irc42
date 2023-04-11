#include "irc.hpp"

void Server::notice(Client &client, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		return ;
	if (args.size() < 2 || args[1].empty())
		return ;
	if (args[0][0] == '#' || args[0][0] == '&')
	{
		iter_channel channel = search_channel(args[0]);
		if (channel == _channels.end())
			return ;
		iter_member member = (*channel).search_user_in_channel(client.getNickName());
		if (member == (*channel).getChannelMembers().end())
			return ;
		send_to_members_in_chan((*channel), format_msg(client) + "NOTICE " + args[0] + " :" + args[1] + "\r\n", (*member).first.getNickName());
	}
	else
	{
		iter_client cli = search_client(args[0]);
		if (cli == _clients.end())
			return ;
		send_to_user((*cli), format_msg(client) + "NOTICE " + args[0] + " :" + args[1] + "\r\n");
	}
}