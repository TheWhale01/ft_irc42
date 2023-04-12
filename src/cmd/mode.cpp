#include "irc.hpp"

void Server::mode(Client &client, std::vector<std::string> const &args)
{
	if (args.size() < 1)
		throw(NeedMoreParamsException(client.getServerName(), client.getNickName(), "MODE"));
	if (args[0][0] == '&' || args[0][0] == '#')
	{
		std::cout << "cmd mode for channel" << std::endl;
		Channel::iter_channel channel = search_channel(args[0]);
		if (channel == _channels.end())
			throw(NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
		if (args.size() == 1)
		{
			send_to_user(client, format_reply(client, RPL_CHANNELMODEIS, args[0]) + "i\r\n"); //modif
			return ;
		}
	}
	else
	{
		std::cout << "cmd mode for user" << std::endl;
		if (args[0] != client.getNickName())
			throw(UserDontMatchException(client.getServerName(), client.getNickName()));
		if (args.size() == 1)
		{
			send_to_user(client, format_reply(client, RPL_UMODEIS, std::string()) + "\r\n"); //modif
			return ;
		}
		throw(UModeUnknowFlagsException(client.getServerName(), client.getNickName()));
	}
}
