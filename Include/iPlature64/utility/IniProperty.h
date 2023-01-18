#ifndef IniProperty_H
#define IniProperty_H
#include <utility/StringHelper.h>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;
/*****************************************************************************
* ini格式的配置文件
* 2007-09-25  徐长盛 发现没有注释的被写了注释
* 2007-04-09  徐长盛 增加namespace和注释
* 2007-04-05  王文峰 完成代码的编写
* 2007-03-26  徐长盛 创建接口
******************************************************************************/
namespace baosight
{
	struct Record//用于记录每条记录的信息
	{
		std::string key;  //key
		std::string value;//值
		std::string comment;//注释
	};

	struct SectionArea//记录段的信息
	{
		std::string section;//段名
		std::vector<std::string>keylist;//段的记录的键值
		std::string comment;//注释
	};

	class CIniProperty{
	private:
		std::string filename;//ini文件的路径
		std::map<std::string,Record> datas;
		std::vector<SectionArea>sectlist;//记录下所有的段

		Record split(std::string& line);

		bool write;//用于判断是否被写
	private:
		int flush();//输出到文件中去
	protected:
		void  Init();
	public:
		CIniProperty(const std::string& file);

	public:
		std::string ReadProperty(const std::string& section,const std::string& key);
		int WriteProperty(const std::string& section,const std::string& key="",const std::string& value="",const std::string& comment="");//第四个参数为注释

		virtual ~CIniProperty();

	};
};
#endif

