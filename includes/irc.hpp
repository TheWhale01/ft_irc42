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

#define SIM_USERS 50
#define BUFF_SIZE 512

// Errors
#define ERR_NEEDMOREPARAMS		461
#define ERR_ALREADYREGISTRED	462

// Typedefs
typedef struct pollfd pollfd_t;
typedef struct sockaddr_in sockaddr_in_t;

#include "Server.hpp"
#include "exception.hpp"

// Prototypes
bool pass(Server const &serv, std::string const &pass);