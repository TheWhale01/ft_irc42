#pragma once

class Client;
class Channel;

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

		void run(void);
		void cap(Client &client, std::vector<std::string> const &args);
		void pass(Client &client, std::vector<std::string> const &args);
		void nick(Client &client, std::vector<std::string> const &args);
		void user(Client &client, std::vector<std::string> const &args);
		void quit(Client &client, std::vector<std::string> const &args);

		void join(Client &client, std::vector<std::string> const &args);
		void part(Client &client, std::vector<std::string> const &args);
		void kick(Client &client, std::vector<std::string> const &args);
		void topic(Client &client, std::vector<std::string> const &args);
		void notice(Client &client, std::vector<std::string> const &args);
		void privmsg(Client &client, std::vector<std::string> const &args);

		void create_channel(Client &client, std::string const &name);
		iter_member search_user_in_channel(Client const &client, Channel &channel);
		Client const &search_client(std::string const &name, std::vector<Client> const &clients);
		Channel const &search_channel(std::string const &name, std::vector<Channel> const &channel);

	private:
		int _bytes;
		char _buff[BUFF_SIZE + 1];
		pollfd_t _poll;
		std::string _passwd;
		sockaddr_in_t _addr;
		std::vector<Client> _clients;
		std::vector<Channel> _channels;
		std::vector<pollfd_t> _pollfds;

		void _exec_cmd(Client &client, std::string str);
		void _get_commands(std::vector<std::string> &cmds);
		void _get_commands_ptr(void (Server::*cmds_ptr[])(Client &, std::vector<std::string> const &));
		friend Channel;
};