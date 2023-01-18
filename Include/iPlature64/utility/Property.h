#ifndef __CPROPERTY_H
#define __CPROPERTY_H

#include <string>
#include <utility/StringHelper.h>
using namespace std;
/*****************************************************************************
* 
* 字符串辅助类，扩充string的功能
* 2007-04-09  徐长盛 增加namespace和注释
* 2007-04-05  王文峰 完成代码的编写
* 2007-03-26  徐长盛 创建接口
******************************************************************************/

namespace baosight{
	class  CProperty {
protected:
		//属性文件名
		std::string filename;
		virtual void  Init();//初始化数据
	public:
		CProperty(std::string& file):filename(file){}
		//读属性值
		virtual std::string ReadProperty(const std::string& section,const std::string& key) const = 0;

		//写属性值
		virtual int WriteProperty(const std::string& section,const std::string& key,const string& value) = 0;


		virtual ~CProperty(){}
	};
};
#endif

