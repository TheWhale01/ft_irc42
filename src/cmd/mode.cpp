#include "irc.hpp"

void Server::mode(Client &client, std::vector<std::string> const &args)
{
	int sign = 0;
	std::string charset;
	if (args.size() < 1)
		throw(NeedMoreParamsException(client.getServerName(), client.getNickName(), "MODE"));
	if (args[0][0] == '&' || args[0][0] == '#')
	{
		std::cout << "cmd mode for channel" << std::endl;
		iter_channel channel = search_channel(args[0]);
		if (channel == _channels.end())
			throw(NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
		if (args.size() == 1)
		{
			send_to_user(client, format_reply(client, RPL_CHANNELMODEIS, args[0]) + "i\r\n"); //modif
			return ;
		}
		charset = "toi";
		for (size_t i = 0; i < args[1].size(); i++)
		{
			if (args[1][i] == '+')
				sign = 1;
			else if (args[1][i] == '-')
				sign = -1;
			else if (sign != 0)
			{
				
				if (charset.find(args[1][i]) == std::string::npos)
					
			}
			else
				throw(UnknownModeException(client.getServerName(), client.getNickName(), args[i]));
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
