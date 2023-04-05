#pragma once

#include <errno.h>
#include <cstring>
#include <stdexcept>

class AIrcStandardException: public std::exception
{
	public:
		virtual const char *what(void) const throw() = 0;
		virtual ~AIrcStandardException(void) throw();

	protected:
		std::string _cmd;
		std::string _nickname;
		std::string _servername;
		std::string *_error_msg;
};

class AlreadyRegistredException: public AIrcStandardException
{
	public:
		explicit AlreadyRegistredException(std::string const &servername, std::string const &nickname);
		~AlreadyRegistredException(void) throw();

		const char *what(void) const throw();
};

class NickNameInUseException: public AIrcStandardException
{
	public:
		explicit NickNameInUseException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NickNameInUseException(void) throw();

		const char *what(void) const throw();
};

class ErroneusNickNameException: public AIrcStandardException
{
	public:
		explicit ErroneusNickNameException(std::string const &servername, std::string const &nickname);
		~ErroneusNickNameException(void) throw();

		const char *what(void) const throw();
};

class UnknownCommandException: public AIrcStandardException
{
	public:
		explicit UnknownCommandException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~UnknownCommandException(void) throw();

		const char *what(void) const throw();
};

class NeedMoreParamsException: public AIrcStandardException
{
	public:
		explicit NeedMoreParamsException(std::string const &servername, std::string const &nickname, std::string const &cmd);
		~NeedMoreParamsException(void) throw();

		const char *what(void) const throw();
};

class NoNickNameGivenException: public AIrcStandardException
{
	public:
		explicit NoNickNameGivenException(std::string const &servername, std::string const &nickname);
		~NoNickNameGivenException(void) throw();

		const char *what(void) const throw();
};

class ClientCouldNotConnectException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class ServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class KillServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};