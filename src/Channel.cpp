#include "irc.hpp"

Channel::Channel(void) {}
Channel::Channel(std::string const &channel) : _mode(0), _channelname(channel) {}
Channel::~Channel(void) {}

const int &Channel::getChannelModes(void) const {return (_mode);}
const std::string &Channel::getChannelTopic(void) const {return (_topic);}
const std::string &Channel::getChannelName(void) const {return (_channelname);}
const std::vector<std::pair<Client, int> > &Channel::getChannelMembers(void) const {return (_channelmembers);}

void Channel::addMemberToChannel(Client const &client, int oper) {_channelmembers.push_back(std::make_pair(client, oper));}
void Channel::setChannelTopic(std::string const &topic) {_topic = topic;}

std::string const Channel::getChannelMode(void) const
{
	std::string modes;
	if (_mode & MODE_T)
		modes += "t ";
	if (_mode & MODE_I)
		modes += "i ";
	return (modes);
}

void Channel::setChannelMode(char const &mode)
{
	if (mode == 't')
		_mode |= MODE_T;
	if (mode == 'i')
		_mode |= MODE_I;
}

void Channel::unsetChannelMode(char const &mode)
{
	if (mode == 't')
		_mode &= -(MODE_T) - 1;
	if (mode == 'i')
		_mode &= -(MODE_I) - 1;
}

void Channel::deleteChannelMember(Channel::iter_member it) {_channelmembers.erase(it);}