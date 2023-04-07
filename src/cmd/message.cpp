#include "irc.hpp"

void send_to_members_in_chan(Channel const &channel, std::string const &name, std::string const &message)
{
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].first.getNickName() == name)
		{
			for (size_t j = 0; j < channel.getChannelMembers().size(); j++)
				send(channel.getChannelMembers()[j].first.getPoll().fd, message.c_str(), message.length(), 0);
			return ;
		}
	}
	throw (std::exception()); //throw (CannotSendToChanException());
}
//faut t'il mettre le \r\n et comment gèrer le :

Channel const &search_channel(std::string const &name, std::vector<Channel> const &channel)
{
	for (size_t i = 0; i < channel.size(); i++)
		if (channel[i].getChannelName() == name)
			return (channel[i]);
	throw (std::exception()); //throw (CannotSendToChanException());
}

Client const &search_client(std::string const &name, std::vector<Client> const &client)
{
	for (size_t i = 0; i < client.size(); i++)
		if (client[i].getNickName() == name)
			return (client[i]);
	throw (std::exception()); //throw (NoSuchNickException());
}

void send_to_user(Client const &client, std::string const &message)
{
	send(client.getPoll().fd, message.c_str(), message.length(), 0);
}

bool privmsg(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (std::exception()); //throw (NoRecipientException());
	if (args.size() < 2 || args[1].empty())
		throw (std::exception()); //throw (NoTextToSendException());
	if (args[0][1] == '#' || args[0][1] == '&')
	{
		send_to_members_in_chan(search_channel(args[0], serv.getChannels()), client.getNickName(), args[1]);
	}
	else
	{
		std::cout << args[1];
		send_to_user(search_client(args[0], serv.getClients()), args[1]);
	}
	return (1);
}

bool notice(Client &client, Server &serv, std::vector<std::string> const &args)
{
	(void) client;
	(void) serv;
	(void) args;
	return (1);
}