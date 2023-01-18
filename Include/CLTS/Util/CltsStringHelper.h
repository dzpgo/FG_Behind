#pragma once
#include <string>
#include <Ice/Ice.h>
#include <pace/pace.h>

using namespace std;

namespace CLTS
{
	// 最大长度
	const int MAX_BUFFER_LENGTH = 4096;

	namespace Util
	{
		// 字符串操作函数
		std::string str2chstr(std::string & str);	// ansi --> utf-8
		std::string chstr2str(std::string & str);	// utf-8 --> ansi
	}
}
