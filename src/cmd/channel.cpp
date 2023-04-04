#include "irc.hpp"

bool join(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() != 1)
		throw (NeedMoreParamsException(args[0]));
	check_channel_syntax(args[0]);
	check_same_name_as_user(serv, args[0]);
	for (size_t i = 0; i < serv.getChannels().size(); i++)
	{
		if (serv.getChannels()[i].getChannelName() == args[0])
		{
			join_channel(client, serv.getChannels()[i]);
			return (1);
		}
	}
	create_channel(client, serv, args[0]);
	return (1);
}

void check_same_name_as_user(Server &serv, std::string name)
{
	name.erase(name.begin());
	for (size_t i = 0; i < serv.getClients().size(); i++)
	{
		if (serv.getClients()[i].getNickName() == name)
			throw (NoSuckChannelException());
	}

}

static void check_channel_syntax(std::string const &channel)
{
	if (channel.size() > 200)
		throw (NoSuckChannelException());
	if (channel[0] != '&' && channel[0] != '#')
		throw (NoSuckChannelException());
	for (size_t i = 1; i < channel.size(); i++)
		if (!isalpha(channel[i]) && channel[i] != '_' && channel[i] != '-' && channel[i] != '.')
			throw (NoSuckChannelException());
}

void create_channel(Client &client, Server &serv, std::string const &name)
{
	Channel	new_channel(name);
	new_channel.addCreatorToChannel(client);
	new_channel.addOperatorToChannel(client);
	new_channel.addMemberToChannel(client);
	serv.getChannels().push_back(new_channel);
}

void join_channel(Client &client, Channel &chan)
{
	chan.addMemberToChannel(client);
}