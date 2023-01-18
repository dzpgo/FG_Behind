#pragma once

#if defined(_WIN32)
#	include <windows.h>
#   include <direct.h> // For _getcwd
#   include <pdhmsg.h> // For PDH_MORE_DATA
#else
#   include <sys/utsname.h>
#endif

#include <iostream>


using namespace std;

namespace iPlature
{
	class SystemInfo
	{
	public:
		SystemInfo(void);
		~SystemInfo(void);
		string getHostName(void);
	private:
		std::string _hostname;
	};
}

