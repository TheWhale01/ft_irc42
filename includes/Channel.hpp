#pragma once

class Client;

// class Permission
// {
// 	public:

// 		Permission(int byte);
// 		~Permission(void);

// 		bool	_member;
// 		bool	_creator;
// 		bool	_operator;
// };

class Channel
{
	public:

		Channel();
		Channel(std::string const &channel);
		~Channel();

		const int &getChannelPermission(void) const;
		const std::string &getChannelName(void) const;
		const std::string &getChannelTopic(void) const;
		const std::vector<std::pair<Client, bool> > &getChannelMembers(void) const;

		void setChannelTopic(std::string const &topic);
		void deleteChannelMember(std::string const &name);
		void addMemberToChannel(Client const &client, bool byte);


	private:
		int										_permission;
		std::string								_topic;
		std::string								_channelname;
		std::vector<std::pair<Client, bool> >	_channelmembers;
};