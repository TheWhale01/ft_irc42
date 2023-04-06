#include "irc.hpp"

std::string &format_reply(Client const &client, std::string const &code, std::string const &name)
{
	std::string answer = ":" + client.getServerName() + " " + code + " " + client.getNickName() + " " + name + " :";
	return (answer);
}

std::string &print_user(Client const &client, Channel const &channel)
{
	std::string answer = ":" + client.getServerName() + " 353 " + client.getNickName() + " = " + channel.getChannelName() + " :";
	for (size_t i = 0; i < channel.getChannelMembers().size(); i++)
	{
		if (channel.getChannelMembers()[i].second._operator == 1)
			answer += "@" + channel.getChannelMembers()[i].first.getNickName();
		else
			answer += channel.getChannelMembers()[i].first.getNickName();
	}
	answer += "\r\n" + format_reply(client, "366", channel.getChannelName()) + "End of NAMES list\r\n";
	return (answer);
}

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
		answer = format_reply(client, "331", channel.getChannelName()) + "No topic is set.\r\n";
	else
		answer = format_reply(client, "332", channel.getChannelName()) + channel.getChannelTopic() + "\r\n";
	if (!check_already_in_chan(client.getNickName(), channel))
	{
		channel.addMemberToChannel(client, 0);
	}
	answer += print_user(client, channel);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void create_channel(Client &client, Server &serv, std::string const &name)
{
	Channel	new_channel(name);
	new_channel.addMemberToChannel(client, 2);
	serv._channels.push_back(new_channel);
	std::string answer = format_reply(client, "331", name) + "No topic is set.\r\n";
	answer += print_user(client, new_channel);
	send(client.getPoll().fd, answer.c_str(), answer.length(), 0);
}

void check_same_name_as_user(Server &serv, std::string name)
{
	std::string cpy = name;
	cpy.erase(name.begin());
	for (size_t i = 0; i < serv.getClients().size(); i++)
	{
		if (serv.getClients()[i].getNickName() == cpy)
			throw (NeedMoreParamsException(name)); //throw (NoSuchChannelException(name));
	}
}

void check_channel_syntax(std::string const &channel)
{
	std::string charset = " ," + 7;
	if (channel.size() > 200)
		throw (NeedMoreParamsException(channel)); //throw (NoSuchChannelException(name));
	if (channel[0] != '&' && channel[0] != '#')
		throw (NeedMoreParamsException(channel)); //throw (NoSuchChannelException(name));
	for (size_t i = 0; i < channel.length(); i++)
		if (charset.find(channel[i]) == std::string::npos)
			throw (NeedMoreParamsException(channel)); //throw (NoSuchChannelException(name));
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
