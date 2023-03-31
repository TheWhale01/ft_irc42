#pragma once

// C includes
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>

// C++ includes
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define SIM_USERS 50
#define BUFF_SIZE 512

// Errors
#define ERR_NEEDMOREPARAMS		461
#define ERR_ALREADYREGISTRED	462
#define ERR_PASSWDMISMATCH		464
#define ERR_NONICKNAMEGIVEN		431
#define ERR_ERRONEUSNICKNAME	432
#define ERR_NICKNAMEINUSE		433

// Typedefs
typedef struct pollfd pollfd_t;
typedef struct sockaddr_in sockaddr_in_t;

#include "Client.hpp"
#include "Server.hpp"
#include "exception.hpp"

// Prototypes
bool pass(Client &client, Server const &serv, std::vector<std::string> const &args);
bool nick(Client &client, Server const &serv, std::vector<std::string> const &args);

void str_toupper(std::string &str);

std::vector<std::string> split(std::string &str);