#include "irc.hpp"

void send_to_members_in_chan(Client const &client, Channel const &channel, std::string const &name, std::string const &message)
{
	std::cout << "message envoyé au client pour prvmsg dans channel= " << message << std::endl;
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].first.getNickName() == name)
		{
			for (size_t j = 0; j < channel.getChannelMembers().size(); j++)
			{
				if (channel.getChannelMembers()[j].first.getNickName() != name)
				{
					std::cout << "fd envoie pour la personne dans channel: "<< channel.getChannelMembers()[j].first.getPoll().fd << std::endl;
					send(channel.getChannelMembers()[j].first.getPoll().fd, message.c_str(), message.length(), 0);
				}
			}
			return ;
		}
	}
	throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
}

Channel const &search_channel(Client const &client, std::string const &name, std::vector<Channel> const &channel)
{
	for (size_t i = 0; i < channel.size(); i++)
		if (channel[i].getChannelName() == name)
			return (channel[i]);
	throw (CannotSendToChanException(client.getServerName(), client.getNickName()));
}

Client const &search_client(Client const &client, std::string const &name, std::vector<Client> const &clients)
{
	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].getNickName() == name)
		{
			std::cout << clients[i].getPoll().fd << std::endl;
			return (clients[i]);
		}
	throw (NoSuchNickException(client.getServerName(), client.getNickName(), name));
}

std::string format_msg(Client const &client)
{
	return (":" + client.getNickName() + "!" + client.getUserName() + "@" + client.getServerName() + " ");
}

void send_to_user(Client const &client, std::string const &message)
{
	std::cout << "message envoyer en prvmsg au client= " << message << std::endl;
	send(client.getPoll().fd, message.c_str(), message.length(), 0);
}

bool privmsg(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() == 0)
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args.size() < 2 || args[1].empty())
		throw (NoRecipientException(client.getServerName(), client.getNickName()));
	if (args[0][0] == '#' || args[0][0] == '&')
	{
		send_to_members_in_chan(client, search_channel(client, args[0], serv.getChannels()), client.getNickName(), format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n");
	}
	else
	{
		std::cout << "fd a qui envoyé le message privé= " <<client.getPoll().fd << std::endl;
		send_to_user(search_client(client, args[0], serv.getClients()), format_msg(client) + "PRIVMSG " + args[0] + " :" + args[1] + "\r\n");
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