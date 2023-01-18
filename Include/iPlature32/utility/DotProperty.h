#ifndef __DotProperty_H
#define __DotProperty_H
#include <string>
#include <map>
#include <fstream>
#include <utility/StringHelper.h>
using namespace std;

/*****************************************************************************
* 
*  .方式的配置文件，例如 obj.a=1
* 字符串辅助类，扩充string的功能
* 2007-04-09  徐长盛 增加namespace和注释
* 2007-04-05  王文峰 完成代码的编写
* 2007-03-26  徐长盛 创建接口
******************************************************************************/
namespace baosight
{
	struct DRecord
	{
		std::string	key;
		std::string value;
		std::string comment;
	};
	class  CDotProperty
	{
	private:
		std::map<std::string,DRecord> datas;
		std::string filename;
		bool write;//用于判断是否写了文件
	public:
		CDotProperty(){}

		CDotProperty(const std::string& file);
		
		int Load(const std::string& file);

		virtual ~CDotProperty();
		DRecord split(std::string& line);//分割记录
		std::string ReadProperty(const std::string &section,const std::string &key);
		std::string ReadProperty(const std::string& key);

		int WriteProperty( const std::string& key,const std::string& value,const std::string& comment="");
	};   
};

#endif

