#include "irc.hpp"

std::vector<std::string> split(std::string &str)
{
	std::vector<std::string> words;
	std::string current_word;
	bool stop_at_colon = false;

	for (size_t i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == ' ' && !stop_at_colon)
		{
			if (current_word.length() > 0)
			{
				words.push_back(current_word);
				current_word.clear();
			}
		}
		else if (str[i] == ':' && !stop_at_colon)
		{
			stop_at_colon = true;
		}
		else
		{
			current_word += str[i];
		}
	}
	if (current_word.length() > 0)
	{
		words.push_back(current_word);
	}
	return words;
}

void exec(std::string str)
{
	// std::string cmds[] = {
	// 	"PASS",
	// 	"NICK",
	// 	"USER",
	// };

	// cmd = split();

	// for (cmd in cmds)
	// 	if (cmd == str[0].toupper())
	// 		func[i](cmd);
	std::cout << split(str) << std::endl;
}