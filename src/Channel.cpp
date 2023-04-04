#include "irc.hpp"

Channel::Channel(std::string channel) : _channelname(channel) {}

Channel::~Channel(void) {}

const std::string &Channel::getChannelName(void) const {return (_channelname);}

void Channel::addMemberToChannel(Client &client) {_channelmembers.push_back(client);}

void Channel::addCreatorToChannel(Client &client) {_channelcreator.push_back(client);}

void Channel::addOperatorToChannel(Client &client) {_channeloperators.push_back(client);}