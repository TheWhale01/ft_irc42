#include "irc.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	Server serv(atoi(av[1]), av[2]);
	serv.run();
	return (0);
}