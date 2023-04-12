#include "irc.hpp"

static void check_nickname_syntax(Client const &client, std::string const &nickname)
{
	std::string charset;

	if (nickname.length() > 9)
		throw (ErroneusNickNameException(client.getServerName(), nickname));
	for (char c = 'A'; c <= 'Z'; c++)
	{
		charset.push_back(c);
		charset.push_back(c + 32);
	}
	for (char c = '1'; c <= '9'; c++)
		charset.push_back(c);
	charset.insert(charset.length(), "[]`^_{}|");	
	if ((nickname[0] < 'A' || nickname[0] > 'Z') && (nickname[0] < 'a' || nickname[0] > 'z'))
		throw (ErroneusNickNameException(client.getServerName(), nickname));
	for (size_t i = 0; i < nickname.length(); i++)
		if (charset.find(nickname[i]) == std::string::npos)
			throw (ErroneusNickNameException(client.getServerName(), nickname));
}

void Server::nick(Client &client, std::vector<std::string> const &args)
{
	// Need more errors !
	std::string msg;
	if (!args.size())
		throw (NoNickNameGivenException(client.getServerName(), client.getNickName()));
	for (size_t i = 0; i < this->getClients().size(); i++)
		if (this->getClients()[i].getNickName() == args[0])
			throw (NickNameInUseException(client.getServerName(), client.getNickName(), args[0]));
	check_nickname_syntax(client, args[0]);
	msg = format_msg(client) + "NICK " + args[0] + "\r\n";
	if (!client.getUserName().empty() && !client.getRegist())
	{
		msg = format_reply(client, RPL_WELCOME, "") + "Welcome to the fucked up IRC server!\r\n";
		client.setRegist(true);
		send(client.getPoll().fd, msg.c_str(), msg.length(), 0);
	}
	else
		sendToChannels(client, msg);
	client.setNickName(args[0]);
}