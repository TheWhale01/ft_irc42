#include "irc.hpp"

int main(void)
{
	while (1)
	{
		int serv_fd;
	int opt = 1;
	int client_fd;
	int recv_bytes;
	char msg[1024];
	struct sockaddr_in myaddr;
	socklen_t addrlen = sizeof(myaddr);

	myaddr.sin_family = AF_INET;
	serv_fd = socket(myaddr.sin_family, SOCK_STREAM, 0);
	if (serv_fd == -1)
		return (1);
	// Prevent address and port already in use
	if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		return (1);
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(PORT);
	if (bind(serv_fd, (struct sockaddr *) &myaddr, sizeof(myaddr)) == -1)
		return (1);
	if (listen(serv_fd, SIM_USERS))
		return (1);
	std::cout << "Server started on port: " << PORT << std::endl;
	if ((client_fd = accept(serv_fd, (struct sockaddr *)&myaddr, &addrlen)) == -1)
		return (1);
	recv_bytes = read(client_fd, msg, 1024);
	std::cout << msg << std::endl;
	}
	return (0);
}