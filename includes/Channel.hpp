#pragma once

class Client;

class Channel
{
	public:

		Channel();
		Channel(std::string const &channel);
		~Channel();

		const int &getChannelModes(void) const;
		const std::string &getChannelName(void) const;
		const std::string &getChannelTopic(void) const;
		const std::string getChannelMode(void) const;
		const std::vector<std::pair<Client, int> > &getChannelMembers(void) const;

		void setChannelTopic(std::string const &topic);
		void setChannelMode(char const &mode);
		void unsetChannelMode(char const &mode);
		void deleteChannelMember(iter_member it);
		void addMemberToChannel(Client const &client, int modes);

		iter_member search_user_in_channel(std::string const &nickname);


	private:
		int										_mode;
		std::string								_topic;
		std::string								_channelname;
		std::vector<std::pair<Client, int> >	_channelmembers;
};