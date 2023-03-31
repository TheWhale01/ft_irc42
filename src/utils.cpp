#include "irc.hpp"

std::vector<std::string> split(std::string &str)
{
	std::vector<std::string> words;
	std::string current_word;
	bool stop_at_colon = false;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '\r' && str[i + 1] == '\n')
			break;
		if (str[i] == ' ' && !stop_at_colon)
		{
			if (current_word.length() > 0)
			{
				words.push_back(current_word);
				current_word.clear();
			}
		}
		else if (str[i] == ':' && !stop_at_colon)
			stop_at_colon = true;
		else
			current_word += str[i];
	}
	if (current_word.length() > 0)
		words.push_back(current_word);
	return (words);
}

void str_toupper(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = static_cast<char>(std::toupper(str[i]));
}

std::string format_msg(char const *msg)
{
	std::string new_msg(msg);

	new_msg.append("\r\n");
	return (new_msg);
}

void format_msg(std::string &str)
{
	str.append("\r\n");
}