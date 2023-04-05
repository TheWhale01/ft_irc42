#include "irc.hpp"

bool join(Client &client, Server &serv, std::vector<std::string> const &args)
{
	if (args.size() != 1)
		throw (NeedMoreParamsException(args[0]));
	check_channel_syntax(args[0]);
	check_same_name_as_user(serv, args[0]);
	for (size_t i = 0; i < serv._channels.size(); i++)
	{
		if (serv._channels[i].getChannelName() == args[0])
		{
			join_channel(client, serv._channels[i]);
			return (1);
		}
	}
	create_channel(client, serv, args[0]);
	return (1);
}

void join_channel(Client &client, Channel &channel)
{
	std::string answer;
	if (channel.getChannelTopic().empty())
		answer = ":" + client.getServerName() + " 331 " + client.getNickName() + " " + channel.getChannelName() + " :No topic is set.\r\n";
	else
		answer = ":" + client.getServerName() + " 332 " + client.getNickName() + " " + channel.getChannelName() + " :" + channel.getChannelTopic() + "\r\n";
	if (!check_already_in_chan(client.getNickName(), channel))
	{
		//check_is_ban(client.getNickName(), channel);
		channel.addMemberToChannel(client, 0);
	}
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void create_channel(Client &client, Server &serv, std::string const &name)
{
	Channel	new_channel(name);
	new_channel.addMemberToChannel(client, 2);
	serv._channels.push_back(new_channel);
}

// void check_is_ban(std::string const &nickname, Channel const &channel)
// {

// }

void check_same_name_as_user(Server &serv, std::string name)
{
	name.erase(name.begin());
	for (size_t i = 0; i < serv.getClients().size(); i++)
	{
		if (serv.getClients()[i].getNickName() == name)
			throw (NoSuchChannelException());
	}
}

void check_channel_syntax(std::string const &channel)
{
	if (channel.size() > 200)
		throw (NoSuchChannelException());
	if (channel[0] != '&' && channel[0] != '#')
		throw (NoSuchChannelException());
	for (size_t i = 1; i < channel.size(); i++)
		if (!isalpha(channel[i]) && channel[i] != '_' && channel[i] != '-' && channel[i] != '.')
			throw (NoSuchChannelException());
}

bool check_already_in_chan(std::string const &nickname, Channel const &channel)
{
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
		if (channel.getChannelMembers()[i].first.getNickName() == nickname)
			return (1);
	return (0); 
}





// size_t	search_index_channel(Server &serv, std::string const &name)
// {
// 	for (size_t i = 0; i < serv.getChannels().size(); i++)
// 	{
// 		if (serv.getChannels()[i].getChannelName() == name)
// 			return (i);
// 	}
// 	throw (NoSuchChannelException());
// }

// size_t search_index_members_in_channel(size_t i, )
// {
// 	for (size_t j = 0; j < serv.getChannels()[i].getChannelMembers().size(); j++)
// 	{
// 		if (serv.getChannels()[i].getChannelMembers()[j].getNickName() == nickname)
// 		{
// 			serv.getChannels()[i].getChannelMembers().erase(serv.getChannels()[i].getChannelMembers().begin() + j);
// 			if ()
// 			return (1);
// 		}
// 	}
// 	throw (NoSuchChannelException());
// }

// // void	search_client_in_channel(Server &serv, Client &client, std::string &name)
// // {
// // 	size_t i = search_channel(serv, name);

// // 	for (size_t j = 0; j < serv.getChannels()[i].getChannelMembers().size(); j++)
// // 	{
// // 		if (serv.getChannels()[i].getChannelMembers()[j].getNickName() == name)
// // 			return (j);
// // 	}
// // 	throw (NoSuchChannelException());
// // }

// bool part(Client &client, Server &serv, std::vector<std::string> const &args)
// {
// 	size_t i = search_index_channel(serv, args[0]);
	


// 	throw (NoSuchChannelException());
// }
