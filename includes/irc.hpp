#pragma once

// C includes
# include <poll.h>
# include <errno.h>
# include <unistd.h>
# include <netinet/in.h>

// C++ includes
# include <vector>
# include <map>
# include <csignal>
# include <cstring>
# include <utility>
# include <cstdlib>
# include <sstream>
# include <iostream>
# include <algorithm>

# define TIMEOUT 10
# define SIM_USERS 50
# define BUFF_SIZE 512

// Mods

# define MODE_I 1 << 0
# define MODE_T 1 << 1

// Errors
# define ERR_NOSUCHNICK			"401"
# define ERR_NOSUCHCHANNEL		"403"
# define ERR_CANNOTSENDTOCHAN	"404"
# define ERR_NORECIPIENT		"411"
# define ERR_NOTEXTTOSEND		"412"
# define ERR_UNKNOWNCOMMAND		"421"
# define ERR_NONICKNAMEGIVEN	"431"
# define ERR_ERRONEUSNICKNAME	"432"
# define ERR_NICKNAMEINUSE		"433"
# define ERR_USERNOTINCHANNEL	"441"
# define ERR_NOTONCHANNEL		"442"
# define ERR_NEEDMOREPARAMS		"461"
# define ERR_ALREADYREGISTRED	"462"
# define ERR_PASSWDMISMATCH		"464"
# define ERR_CHANOPRIVSNEEDED	"482"

// Reply
# define RPL_WELCOME			"001"
# define RPL_NOTOPIC			"331"
# define RPL_TOPIC				"332"
# define RPL_NAMREPLY			"353"
# define RPL_ENDOFNAMES			"366"

typedef struct pollfd pollfd_t;
typedef struct sockaddr_in sockaddr_in_t;
# include "Client.hpp"
typedef std::vector<std::pair<Client, int> >::iterator iter_member;
typedef std::vector<Client>::iterator iter_client;
# include "Channel.hpp"
typedef std::vector<Channel>::iterator iter_channel;
# include "Server.hpp"
# include "exception.hpp"

void sigHandler(int sig_id);
void format_msg(std::string &str);
void str_toupper(std::string &str);
void send_to_user(Client const &client, std::string const &message);
void send_to_members_in_chan(Channel const &channel, std::string const &message, std::string const &sender);

std::string format_msg(char const *msg);
std::string format_msg(Client const &client); //:<nickname>!<username>@<hostname> "
std::string print_all_user(Client const &client, Channel const &channel); 
std::string format_reply(Client const &client, std::string const &code, std::string const &name);

std::vector<std::string> split(std::string &str);
std::vector<std::string> split(const std::string& str, const std::string& delimiter);