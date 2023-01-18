#pragma once
#include <map>
#include <sstream>
using namespace std;

namespace iPlature
{
	class HMIUtility
	{
	private:
		static const std::string SPLIT_FLAG;
	public:
		template<typename T>
		static string Map2String(const T& mp)
		{
			typename T::const_iterator iter = mp.begin();
			std::ostringstream o;
			o<<fixed;
			while (iter != mp.end())
			{
				o<<"key="<<iter->first<<"\t"<<"value="<<iter->second;
				if (++iter != mp.end())
				{
					o<<endl;
				}
			}
			return o.str();
		}//Map2String

		static std::string Form2String(const std::string& str1, const std::string& str2)
		{
			return str1 + SPLIT_FLAG + str2;
		}

		static void Split2String(const std::string& str, std::string& str1, std::string& str2);
	};

	
}

