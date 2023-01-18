/**
*this class is used for parse command line,can use cmd -h20 -m30 or cmd /h20 /m30
*
*/

#pragma once
#ifndef  _CMDLINE_H
#define  _CMDLINE_H
#include <map>
#include <iostream>
#include <string>
using namespace std;
/**
*@2007-4-9 添加命名空间和注释
*@author Xu Changsheng
*@since 2005-10-18
*@version 1.0
*
*/

namespace baosight
{
	class CCmdline
	{
	private:
		CCmdline(const CCmdline& );
		
	public:
		CCmdline(int argc , char **argv);
		bool parse();
		virtual ~CCmdline(void);
		std::string getValue(const char& option,const std::string& defvalue="");
	public:
		bool hasOption(std::string c)
		{
			std::map<std::string,std::string>::iterator it;
			it = options.find(c);
			return (it!=options.end());
		}
	private:
		std::map<std::string,std::string>options; 
		int argc;
		char** argv;
	};
};
#endif

