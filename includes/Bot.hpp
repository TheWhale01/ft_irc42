#include "irc.hpp"

class Bot: public Client
{
	public:
		Bot(void);
		~Bot(void);

		void weather();
	
	private:
		char _buff[BUFF_SIZE];
		addrinfo_t _hints, *_server_info;
		std::string _domain_name;

		std::string _get_request(std::string endpoint);
};