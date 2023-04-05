#include "irc.hpp"

bool pass(Client &client, Server const &serv, std::vector<std::string> const &args)
{
	if (args.size() != 1)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "PASS"));
	if (client.getRegist())
		throw (AlreadyRegistredException(client.getServerName(), client.getNickName()));
	if (serv.getPasswd() != *args.begin())
	{
		std::cerr << "(error) >> Password incorrect\n";
		return (0);
	}
	return (1);
}

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

bool nick(Client &client, Server const &serv, std::vector<std::string> const &args)
{
	// Need more errors !
	if (!args.size())
		throw (NoNickNameGivenException(client.getServerName(), client.getNickName()));
	for (size_t i = 0; i < serv.getClients().size(); i++)
		if (serv.getClients()[i].getNickName() == args[0])
			throw (NickNameInUseException(client.getServerName(), client.getNickName(), args[0]));
	check_nickname_syntax(client, args[0]);
	client.setNickName(args[0]);
	if (!client.getUserName().empty() && !client.getRegist())
	{
		std::string welcome;

		welcome = "001 " + client.getNickName() + " :Welcome to the fucked up IRC server!\r\n";
		client.setRegist(true);
		send(client.getPoll().fd, welcome.c_str(), welcome.length(), 0);
	}
	return (1);
}

bool user(Client &client, Server const &serv, std::vector<std::string> const &args)
{
	// RFC 1459
	(void)serv;
	if (args.size() < 4)
		throw (NeedMoreParamsException(client.getServerName(), client.getNickName(), "USER"));
	if (client.getRegist())
		throw (AlreadyRegistredException(client.getServerName(), client.getNickName()));
	client.setUserName(args[0]);
	client.setHostName(args[1]);
	client.setServerName(args[2]);
	client.setRealName(args[3]);
	if (!client.getNickName().empty() && !client.getRegist())
	{
		std::string welcome;

		welcome = "001 " + client.getNickName() + " :Welcome to the fucked up IRC server!\r\n";
		client.setRegist(true);
		send(client.getPoll().fd, welcome.c_str(), welcome.length(), 0);
	}
	return (1);
}