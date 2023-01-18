#ifndef _D2Property_H
#define _D2Property_H
/**
*本类用于读取二维的配置文件，如
Line   TelId  eventId     A  B
1        abc    1000          -     -
2        ccc    2000          -     -
3        ddd    3000          -     -
 根据关键列来读目标列数据，如根据(1,2)读 第3列数据
*/
#include <stdarg.h>		
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace baosight
{
	class CD2Property{
	public:
		CD2Property(const std::string& file,int ommitfirstline = 1);
		CD2Property();
		
		~CD2Property();
		//打开配置文件
		int OpenFile(std::string file,int ommitfirstline = 1);
		//根据从第几列到第几列去读取指定目标列的数据
		int ReadProperty(const std::string columnname,std::string& value,std::vector<std::string>keys);

		//使用不定参数方式去读取指定列的数据
		//int ReadProperty(const std::string columnname,std::string& value,int keyscount,...);
		int ReadProperty(int index,std::string& value,std::vector<std::string>keys);
		
		//使用不定参数方式去读取指定列的数据
		//int ReadProperty(int index,std::string& value,int keyscount,...);
	protected:
		void Init();
	private:
		std::string filename;
		std::vector<std::string> columns;
		std::vector<std::vector<std::string> > alldata;
		int omitfirstline;//第一行是否关于列的描述？
		int openflag;
		bool write;//配置文件是否被更改过
	};
};
#endif

