#include <iostream>
#include <stdexcept>
#include <exception>
#include <cstring>
#include <sys/socket.h>

#define SIM_USERS 50
typedef struct sockaddr sockaddr_t;

int main(void)
{
	int sock_fd, client_sock_fd;
	sockaddr_t addr, client_addr;
	socklen_t client_addr_size;

	memset(&addr, 0, sizeof(addr));
	addr.sa_family = AF_INET;
	sock_fd = socket(addr.sa_family, SOCK_STREAM, 0);
	if (sock_fd == -1)
		throw (std::domain_error("socket error."));
	if (bind(sock_fd, (sockaddr *) &addr, sizeof(addr)) == -1)
		throw (std::domain_error("bind error."));
	if (listen(sock_fd, SIM_USERS) == -1)
		throw (std::domain_error("Salut !"));
	client_addr_size = sizeof(client_addr);
	client_sock_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &client_addr_size);
	if (client_sock_fd == -1)
		throw (std::domain_error("Bonsoir !"));
	return (0);
}