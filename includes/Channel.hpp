#pragma once

#include "irc.hpp"

class Channel
{
	public:

		Channel();
		Channel(std::string channel);
		~Channel();

		const std::string &getChannelName(void) const;
		const std::string &getChannelTopic(void) const;
		const std::vector<std::pair<Client, Permission> >  &getChannelMembers(void) const;

		void addMemberToChannel(Client &client, int byte);
		void setChannelTopic(std::string const &topic);

		std::vector<std::pair<Client, Permission> >	_channelmembers;

	private:
		std::string									_topic;
		std::string									_channelname;
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