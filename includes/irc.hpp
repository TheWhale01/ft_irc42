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

#include "Client.hpp"
#include "Server.hpp"
#include "exception.hpp"

// Prototypes
void exec(std::string str);
bool pass(Server const &serv, std::string const &pass);

// Operator overloads
template<class T>
std::ostream &operator<<(std::ostream &stream, std::vector<T> const &v)
{
	typename std::vector<T>::const_iterator it;

	stream << "[";
	for (it = v.begin(); it != v.end(); it++)
		stream << *it << (it + 1 != v.end() ? ", " : "");
	stream << "]";
	return (stream);
}