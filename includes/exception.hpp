#include <errno.h>
#include <cstring>
#include <stdexcept>

class UnknownCommandException: public std::exception
{
	public:
		explicit UnknownCommandException(std::string const &str);
		~UnknownCommandException(void) throw();

		const char *what(void) const throw();
	
	private:
		std::string *_error_msg;
};

class NeedMoreParamsException: public std::exception
{
	public:
		explicit NeedMoreParamsException(std::string const &str);
		~NeedMoreParamsException(void) throw();

		const char *what(void) const throw();
	
	private:
		std::string *_error_msg;
};

class NickNameInUseException: public std::exception
{
	public:
		explicit NickNameInUseException(std::string const &str);
		~NickNameInUseException(void) throw();

		const char *what(void) const throw();
	
	private:
		std::string *_error_msg;
};

class ErroneusNickNameException: public std::exception
{
	public:
		explicit ErroneusNickNameException(std::string const &str);
		~ErroneusNickNameException(void) throw();

		const char *what(void) const throw();
	
	private:
		std::string *_error_msg;
};

class ServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class ClientCouldNotConnectException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class AlreadyRegisteredExcpetion: public std::exception
{
	public:
		const char *what(void) const throw();
};

class NoNickNameGivenException: public std::exception
{
	public:
		const char *what(void) const throw();
};

class KillServerException: public std::exception
{
	public:
		const char *what(void) const throw();
};