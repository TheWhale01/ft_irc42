#pragma once

class Client;

class Permission
{
	public:

		Permission(int byte);
		~Permission();

		bool	_member;
		bool	_creator;
		bool	_operator;
};

class Channel
{
	public:

		Channel();
		Channel(std::string const &channel);
		~Channel();

		const std::string &getChannelName(void) const;
		const std::string &getChannelTopic(void) const;
		const std::vector<std::pair<Client, Permission> >  &getChannelMembers(void) const;

		void setChannelTopic(std::string const &topic);

		void addMemberToChannel(Client const &client, int byte);


	private:
		std::string									_topic;
		std::string									_channelname;
		std::vector<std::pair<Client, Permission> >	_channelmembers;
};