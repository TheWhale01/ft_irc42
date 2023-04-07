#pragma once

// C includes
# include <poll.h>
# include <errno.h>
# include <unistd.h>
# include <netinet/in.h>

// C++ includes
# include <vector>
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
# define ERR_NEEDMOREPARAMS		"461"
# define ERR_ALREADYREGISTRED	"462"
# define ERR_PASSWDMISMATCH		"464"

// Answers
# define RPL_NOTOPIC "331"
# define RPL_TOPIC	"332"

// Typedefs
typedef struct pollfd pollfd_t;
typedef struct sockaddr_in sockaddr_in_t;

# include "Client.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "exception.hpp"
class channel;
/*Prototypes*/

// Authentication
bool cap(Client &client, Server &serv, std::vector<std::string> const &args);
bool pass(Client &client, Server &serv, std::vector<std::string> const &args);
bool nick(Client &client, Server &serv, std::vector<std::string> const &args);
bool user(Client &client, Server &serv, std::vector<std::string> const &args);
bool quit(Client &client, Server &serv, std::vector<std::string> const &args);

//channels
bool join(Client &client, Server &serv, std::vector<std::string> const &args);
bool privmsg(Client &client, Server &serv, std::vector<std::string> const &args);
bool notice(Client &client, Server &serv, std::vector<std::string> const &args);

void sigHandler(int sig_id);
void format_msg(std::string &str);
void str_toupper(std::string &str);

std::string format_msg(char const *msg);
std::string format_msg(std::string const &nickname, std::string const &username, std::string const &hostname, std::string const &message);

std::vector<std::string> split(std::string &str);
std::vector<std::string> split(const std::string& str, const std::string& delimiter);