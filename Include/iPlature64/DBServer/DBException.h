#pragma once
#include <string>


namespace iPlature
{
	class DBException : public std::exception
	{
	public:
		DBException() {}
		DBException(const std::string& msg);
		DBException(const std::string& msg, const std::string& tip);
		~DBException(void) throw(){}
		const char* what();
	protected:
		std::string FormMessage(const std::string& msg, const std::string& tip);
	protected:
		std::string _msg;
	};
}



