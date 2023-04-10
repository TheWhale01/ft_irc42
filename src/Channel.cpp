#include "irc.hpp"

Channel::Channel(void) {_channelname = std::string();}
Channel::Channel(std::string const &channel) : _permission(0), _channelname(channel) {}
Channel::~Channel(void) {}

const int &Channel::getChannelPermission(void) const {return (_permission);}
const std::string &Channel::getChannelTopic(void) const {return (_topic);}
const std::string &Channel::getChannelName(void) const {return (_channelname);}
const std::vector<std::pair<Client, bool> > &Channel::getChannelMembers(void) const {return (_channelmembers);}

void Channel::addMemberToChannel(Client const &client, bool oper) {_channelmembers.push_back(std::make_pair(client, oper));}
void Channel::setChannelTopic(std::string const &topic) {_topic = topic;}

void Channel::deleteChannelMember(std::string const &name)
{
	for (size_t i = 0; i < _channelmembers.size(); i++)
	{
		if (_channelmembers[i].first.getNickName() == name)
		{
			_channelmembers.erase(_channelmembers.begin() + i);
			return ;
		}
	}
}
