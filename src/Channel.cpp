#include "irc.hpp"

Channel::Channel(void) {}
Channel::Channel(std::string const &channel) : _mode(0), _channelname(channel) {}
Channel::~Channel(void) {}

const int &Channel::getChannelMode(void) const {return (_mode);}
const std::string &Channel::getChannelTopic(void) const {return (_topic);}
const std::string &Channel::getChannelName(void) const {return (_channelname);}
const std::vector<std::pair<Client, int> > &Channel::getChannelMembers(void) const {return (_channelmembers);}

void Channel::addMemberToChannel(Client const &client, int oper) {_channelmembers.push_back(std::make_pair(client, oper));}
void Channel::setChannelTopic(std::string const &topic) {_topic = topic;}
void Channel::setChannelmode(std::string mode)
{
	if (mode == "+t")
	{
		std::cout << "mode t activé" << std::endl;
		_mode |= MODE_T;
	}
	else
	{
		std::cout << "mode t désactivé" << std::endl;
		_mode &= -(MODE_T) - 1;
	}
}

void Channel::deleteChannelMember(Channel::iter_member it) {_channelmembers.erase(it);}