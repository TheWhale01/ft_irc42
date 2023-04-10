#include "irc.hpp"

// bool kick(Client &client, Server &serv, std::vector<std::string> const &args)
// {
// 	return (1);
// }

// bool mode(Client &client, Server &serv, std::vector<std::string> const &args)
// {
// 	return (1);
// }

// bool invite(Client &client, Server &serv, std::vector<std::string> const &args)
// {
// 	return (1);
// }

bool topic(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "TOPIC"));
	for (size_t i = 0; i < serv.getChannels().size(); i++)
	{
		if (serv.getChannels()[i].getChannelName() == args[0])
		{
			if (search_user_in_channel(client, serv.getChannels()[i]).empty())
				throw (NotOnChannelException(client.getServerName(), client.getNickName(), args[0]));
			if (args.size() == 2)
			{
				serv._channels[i].setChannelTopic(args[1]);
				send_to_members_in_chan(serv.getChannels()[i], format_reply(client, "332", serv.getChannels()[i].getChannelName()) + serv.getChannels()[i].getChannelTopic() + "\r\n", std::string());
			}
			else
			{
				if (serv.getChannels()[i].getChannelTopic().empty())
					send_to_user(client, format_reply(client, "331", serv.getChannels()[i].getChannelName()) + "No topic is set\r\n");
				else
					send_to_user(client, format_reply(client, "332", serv.getChannels()[i].getChannelName()) + serv.getChannels()[i].getChannelTopic() + "\r\n");
			}
			return (1);
		}
	}
	throw (NoSuchChannelException(client.getServerName(), client.getNickName(), args[0]));
}