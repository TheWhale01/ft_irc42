#pragma once

#include "irc.hpp"

class Client;

class Server
{
	public:
		socklen_t addrlen;
		sockaddr_in_t client_addr;

		Server(int port, std::string passwd);
		~Server(void);

		const pollfd_t &getPoll(void) const;
		const sockaddr_in_t &getAddr(void) const;
		const std::string &getPasswd(void) const;
		const std::vector<Client> &getClients(void) const;
		const std::vector<Channel> &getChannels(void) const;

		std::vector<Channel> _channels;
		void run(void);
	
	private:
		int _bytes;
		char _buff[BUFF_SIZE + 1];
		pollfd_t _poll;
		std::string _passwd;
		sockaddr_in_t _addr;
		std::vector<Client> _clients;
		std::vector<pollfd_t> _pollfds;

		void _exec_cmd(Client &client, std::string str);
		void _get_commands(std::vector<std::string> &cmds);
		void _get_commands_ptr(bool (*cmds_ptr[])(Client &, Server &, std::vector<std::string> const &));
};