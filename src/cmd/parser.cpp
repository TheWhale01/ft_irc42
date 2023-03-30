#include "irc.hpp"

std::vector<std::string> split(std::string &str)
{
	char to_find = ' ';
	std::vector<std::string> args;
	std::string::iterator it;
	
	while (find(str))
	return (args);
}

void exec(std::string const &str)
{
	std::string cmds[] = {
		"PASS",
		"NICK",
		"USER",
	};

	cmd = split();

	for (cmd in cmds)
		if (cmd == str[0].toupper())
			func[i](cmd);
}