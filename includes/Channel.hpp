#pragma once

#include "irc.hpp"

class Channel
{
	public:
		Channel(std::string channel);
		~Channel();

		const std::string &getChannelName(void) const;

		void addMemberToChannel(Client &client);
		void addCreatorToChannel(Client &client);
		void addOperatorToChannel(Client &client);

	private:
		std::string					_channelname;
		std::vector<Client>			_channelcreator;
		std::vector<Client>			_channelmembers;
		std::vector<Client>			_channeloperators;
};