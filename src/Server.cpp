#include "irc.hpp"

Server::Server(int port, std::string passwd): _passwd(passwd)
{
	int temp = 1;
	bzero(&addrlen, sizeof(addrlen));
	_addr.sin_family = AF_INET;
	_poll.fd = socket(_addr.sin_family, SOCK_STREAM, 0);
	if (_poll.fd == -1)
		throw (ServerException());
	if (setsockopt(_poll.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &temp, sizeof(temp)) < 0)
		throw (ServerException());
	_poll.events = POLLIN;
	_poll.revents = 0;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);
	if (bind(_poll.fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw (ServerException());
	if (listen(_poll.fd, SIM_USERS) == -1)
		throw (ServerException());
	_pollfds.push_back(_poll);
	std::cout << "Server started on port: " << ntohs(_addr.sin_port) << std::endl;
	return ;
}

Server::~Server(void)
{
	for (size_t i = 0; i < _pollfds.size(); i++)
		close(_pollfds[i].fd);
	return ;
}

const pollfd_t &Server::getPoll(void) const {return (_poll);}
const sockaddr_in_t &Server::getAddr(void) const {return (_addr);}
const std::string &Server::getPasswd(void) const {return (_passwd);}
const std::vector<Client> &Server::getClients(void) const {return (_clients);}
const std::vector<Channel> &Server::getChannels(void) const {return (_channels);}

void Server::run(void)
{
	signal(SIGINT, sigHandler);
	while (true)
	{
		if (poll(_pollfds.data(), _pollfds.size(), TIMEOUT) < 0)
			throw (ServerException());
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents & POLLIN)
			{
				if (_pollfds[i].fd == _poll.fd)
				{
					try
					{
						Client new_client(*this);
						_pollfds.push_back(new_client.getPoll());
						_clients.push_back(new_client);
					}
					catch (const std::exception& e) {std::cerr << e.what();}
				}
				else
				{
					_bytes = recv(_pollfds[i].fd, _buff, BUFF_SIZE, 0);
					if (_bytes <= 0)
					{
						std::cout << "(info) >> Client " << _pollfds[i].fd << " disconnected." << std::endl;
						close(_pollfds[i].fd);
						_pollfds.erase(_pollfds.begin() + i);
						_clients.erase(_clients.begin() + (i - 1));
						i--;
					}
					else
					{
						_buff[_bytes] = '\0';
						std::cout << "message recu= " << _buff << std::endl;
						std::string user_input(_buff);
						std::vector<std::string> user_inputs = split(user_input, "\r\n");
						std::vector<std::string>::iterator it;
						for (it = user_inputs.begin(); it != user_inputs.end(); it++)
						{
							try {_exec_cmd(_clients[i  - 1], *it);}
							catch (std::exception const &e)
							{
								std::string error_msg(e.what());
								std::cerr << error_msg;
								send(_clients[i - 1].getPoll().fd, error_msg.c_str(), error_msg.length(), 0);
							}
						}
					}
				}
			}
		}
	}
}

// PRIVATE FUNCTION MEMBERS
void Server::_exec_cmd(Client &client, std::string str)
{
	std::string cmd;
	std::string cmd_not_found;
	std::vector<std::string> args = split(str);
	if (!args.size())
		return ;
	std::vector<std::string> cmds;
	_get_commands(cmds);
	bool (*cmds_ptr[cmds.size()])(Client &, Server &, std::vector<std::string> const &);
	_get_commands_ptr(cmds_ptr);

	for (size_t i = 0; i < cmds.size(); i++)
	{
		str_toupper(args[0]);
		cmd = args[0];
		if (args[0] == cmds[i])
		{
			args.erase(args.begin());
			cmds_ptr[i](client, *this, args);
			return ;
		}
	}
	// Unknown Command;
	cmd_not_found = ":" + (client.getServerName().empty() ? "localhost" : client.getServerName()) + " "
		+ ERR_UNKNOWNCOMMAND + " " + (client.getNickName().empty() ? "*" : client.getNickName()) + " " + cmd
		+ " :Unknown command\r\n";
	std::cerr << cmd_not_found;
	send(client.getPoll().fd, cmd_not_found.c_str(), cmd_not_found.length(), 0);
}

void Server::_get_commands(std::vector<std::string> &cmds)
{
	cmds.push_back("PASS");
	cmds.push_back("NICK");
	cmds.push_back("CAP");
	cmds.push_back("USER");
	cmds.push_back("QUIT");
	cmds.push_back("JOIN");
	cmds.push_back("PRIVMSG");
	cmds.push_back("NOTICE");
	cmds.push_back("PART");
	cmds.push_back("TOPIC");
}

void Server::_get_commands_ptr(bool (*cmds_ptr[])(Client &, Server &, std::vector<std::string> const &))
{
	cmds_ptr[0] = &pass;
	cmds_ptr[1] = &nick;
	cmds_ptr[2] = &cap;
	cmds_ptr[3] = &user;
	cmds_ptr[4] = &quit;
	cmds_ptr[5] = &join;
	cmds_ptr[6] = &privmsg;
	cmds_ptr[7] = &notice;
	cmds_ptr[8] = &part;
	cmds_ptr[9] = &topic;
}