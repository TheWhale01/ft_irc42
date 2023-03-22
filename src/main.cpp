#include "irc.hpp"
#include "Server.hpp"
#include <vector>

#define BUFF_LEN 1024

int main(int ac, char **av)
{
	if (ac != 3)
		return (1);

	Server serv(atoi(av[1]), av[2]);
	std::vector<struct pollfd> fds;
	struct sockaddr_in client_addr;
	socklen_t addrlen;
	struct pollfd server_poll = {serv.getFd(), POLLIN, 0};
	fds.push_back(server_poll);
	while (true)
	{
		int poll_ret = poll(fds.data(), fds.size(), -1);
		std::cout << "(Debug) >> poll_ret: " << poll_ret << std::endl;
		if (poll_ret < 0)
		{
			std::cerr << "(Error) >> Could not poll" << std::endl;
			return (1);
		}
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == serv.getFd())
				{
					struct pollfd new_client;
					new_client.fd = accept(serv.getFd(), (struct sockaddr *)&client_addr, &addrlen);
					if (new_client.fd == -1)
						std::cerr << "(Error) >> Client could not connect." << std::endl;
					new_client.events = POLLIN;
					new_client.revents = 0;
					fds.push_back(new_client);
					std::cout << "(Info) >> Client connected." << std::endl;					
				}
				else
				{
					char buff[BUFF_LEN + 1];
					int bytes = recv(fds[i].fd, buff, BUFF_LEN, 0);
					if (bytes <= 0)
					{

						close(fds[i].fd);
						fds.erase(fds.begin() + i);
						i--;
						std::cout << "(Info) >> Client " << fds[i].fd << " disconnected." << std::endl;
					}
					else
					{
						buff[bytes] = '\0';
						std::cout << "(Client: " << fds[i].fd << ") >> " << buff << std::endl;;
						for (size_t j = 1; j != fds.size(); j++)
							if (j != i)
								send(fds[j].fd, buff, bytes, 0);
					}
				}
			}
		}
	}
	for (size_t i = 0; i < fds.size(); i++) {
        close(fds[i].fd);
    }
	return (0);
}