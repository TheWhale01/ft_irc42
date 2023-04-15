#include "irc.hpp"

void Server::names(Client &client, std::vector<std::string> const &args)
{
	bool in = 0;
	if (args.size() == 1)
	{
		Channel::iter_channel channel = search_channel(args[1]);
		if (channel == _channels.end()) {
			send_to_user(client, format_reply(client, RPL_ENDOFNAMES, args[1]) + "End of /NAMES list\r\n");
			return ;
		}
		Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
		if (member != channel->getChannelMembers().end())
			in = 1;
		if (channel->getChannelModes() & MODE_S) {
			if (!in) {
				send_to_user(client, format_reply(client, RPL_ENDOFNAMES, channel->getChannelName()) + "End of /NAMES list\r\n");
				return ;
			}
		}
		send_to_user(client, print_all_user(client, *channel, in));
	}
}
