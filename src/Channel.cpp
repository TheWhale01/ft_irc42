#include "irc.hpp"

Channel::Channel() {}
Channel::Channel(std::string const &channel) : _channelname(channel) {}
Channel::~Channel(void) {}

const std::string &Channel::getChannelTopic(void) const {return (_topic);}
const std::string &Channel::getChannelName(void) const {return (_channelname);}
const std::vector<Client> &Channel::getBanList(void) const {return (_banlist);}
const std::vector<std::pair<Client, Permission> > &Channel::getChannelMembers(void) const {return (_channelmembers);}

void Channel::addUserToBanlist(Client const &client) {_banlist.push_back(client);}
void Channel::addMemberToChannel(Client const &client, int byte) {_channelmembers.push_back(std::make_pair(client, Permission(byte)));}

void Channel::setChannelTopic(std::string const &topic) {_topic = topic;}







Permission::Permission(int byte) : _member(1), _creator(0), _operator(0), _ban(0)
{
	if (byte >= 1)
		_operator = 1;
	if (byte == 2)
		_creator = 1;
}

Permission::~Permission(void) {}