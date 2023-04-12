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
			send_to_user(client, format_reply(client, RPL_CHANNELMODEIS, args[0]) + channel->getChannelMode() + "\r\n"); //modif
			return ;
		}
		charset = "tio";
		for (size_t i = 0; i < args[1].size(); i++)
		{
			if (args[1][i] == '+')
				sign = 1;
			else if (args[1][i] == '-')
				sign = -1;
			else if (sign != 0 && (charset.find(args[1][i]) != std::string::npos))
			{
					if (args[1][i] == 'o')
					{
						if (args.size() < 3)
							throw(NeedMoreParamsException(client.getServerName(), client.getNickName(), "MODE"));
						iter_member member = channel->search_user_in_channel(args[2]);
						if (member == channel->getChannelMembers().end())
							throw(UserNotInChannelException(client.getServerName(), client.getNickName(), args[0], args[1]));
						if (sign == 1)
							member->second = 1;
						else
							member->second = 0;
					}
					if (sign == 1)
						channel->setChannelMode(args[1][i]);
					else
						channel->unsetChannelMode(args[1][i]);
			}
			else
				std::cout << "PAS TROUVÉ FLAGS" << std::endl;
				//throw(UnknownModeException(client.getServerName(), client.getNickName(), args[i]));
		}
	}
	else
	{
		std::cout << "cmd mode for user" << std::endl;
		iter_client cli = search_client(args[0]);
		if (cli == _clients.end())
			throw(NoSuchNickException(client.getServerName(), client.getNickName(), args[0]));
		if (args[0] != client.getNickName())
			throw(UserDontMatchException(client.getServerName(), client.getNickName()));
		if (args.size() == 1)
		{
			send_to_user(client, format_reply(client, RPL_UMODEIS, std::string()) + client.getClientMode() + "\r\n"); //modif
			return ;
		}
		charset = "i";
		for (size_t i = 0; i < args[1].size(); i++)
		{
			if (args[1][i] == '+')
				sign = 1;
			else if (args[1][i] == '-')
				sign = -1;
			else if (sign != 0 && (charset.find(args[1][i]) != std::string::npos))
			{
				if (sign == 1)
					cli->setClientMode(args[1][i]);
				else
					cli->unsetClientMode(args[1][i]);
			}
			else
				std::cout << "PAS TROUVÉ FLAGS" << std::endl;
				//throw(UModeUnknowFlagsException(client.getServerName(), client.getNickName()));
		}
	}
}
