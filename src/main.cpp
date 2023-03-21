#include "irc.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	int client_fd;
	char buff[200];
	struct pollfd fds[SIM_USERS];
	socklen_t addrlen;

	Server serv(atoi(av[1]), av[2]);
	for (int i = 0; i < SIM_USERS; i++)
	{
		fds[i].fd = -1;
		fds[i].events = POLLIN;
		fds[i].revents = 0;
	}
	client_fd = accept(serv.getFd(), (struct sockaddr *)&serv.getAddr(), &addrlen);
	return (0);
}