#pragma once
#include <string>
namespace iPlature
{
	class HMIServerException : public std::exception
	{
	public:
		HMIServerException(const std::string& reason):_what(reason){}
		const char*  what() const  throw();
		virtual ~HMIServerException() throw(){}
	private:
		std::string _what;
	};

	inline const char*  HMIServerException::what() const throw()
	{
		return _what.c_str();
	}
}

