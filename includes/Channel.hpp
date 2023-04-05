#pragma once

#include "irc.hpp"

class Channel
{
	public:

		Channel();
		Channel(std::string const &channel);
		~Channel();

		const std::string &getChannelName(void) const;
		const std::string &getChannelTopic(void) const;
		const std::vector<Client> &getBanList(void) const;
		const std::vector<std::pair<Client, Permission> >  &getChannelMembers(void) const;

		void setChannelTopic(std::string const &topic);

		void addUserToBanlist(Client const &client);
		void addMemberToChannel(Client const &client, int byte);


	private:
		std::string									_topic;
		std::string									_channelname;
		std::vector<Client>							_banlist;
		std::vector<std::pair<Client, Permission> >	_channelmembers;
};

class Permission
{
	public:

		Permission(int byte);
		~Permission();

		bool	_ban;
		bool	_member;
		bool	_creator;
		bool	_operator;
};