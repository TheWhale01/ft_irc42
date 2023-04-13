#include "irc.hpp"

void Server::privmsg(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 2 || args[1].empty())
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args[0][0] == '#' || args[0][0] == '&')
	{
		Channel::iter_channel channel = search_channel(args[0]);
		if (channel == _channels.end())
			throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
		Channel::iter_member member = channel->search_user_in_channel(client.getNickName());
		if (member == channel->getChannelMembers().end())
			throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
		if (channel->getChannelModes() & MODE_M) {
			if (member->second == 0)
				throw (ChanoPrivsNeededException(client.getServerName(), client.getNickName(), args[0]));
		}
		send_to_members_in_chan(*channel, format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n", member->first->getNickName());
	}
	else
	{
		Client::iterator cli = search_client(args[0]);
		if (cli == _clients.end())
			throw (NoSuchNickException(client.getServerName(), client.getNickName(), args[0]));
		send_to_user(*cli, format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n");
	}
}
