#ifndef __STRINGHELPER_H_BAOSIGHT
#define __STRINGHELPER_H_BAOSIGHT
/*****************************************************************************
* 
* 字符串辅助类，扩充string的功能
*2008-11-27 add DoubleToStr功能
*2008-07-25 add Split功能
* 2008-07-23 徐长盛  注释 ToVector的TrimChar功能
* 2007-11-25 徐长盛  fix bug:ToHex参数，const char*p --> const unsigned char *p
* 2007-09-25  李海刚 fix bug ：stringstream在vs2005 sp1前memory leak 问题
* 2007-05-17  徐长盛 增加ToVector功能和去除字符串两边的括号等功能
* 2007-04-10  徐长盛 增加 int->string,可选择前导0
* 2007-04-06  徐长盛 增加namespace,16进制的功能
* 2007-04-05  王文峰 完成代码的编写
* 2007-03-26  徐长盛 单独提取出来
* 2006-12-25  徐长盛 在Berkely Client中初建

@version 1.4 since 2006-12-25
******************************************************************************/
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
#include <sstream>
#include <map>
#include <limits>
using namespace std;

namespace baosight
{
	//全部是静态方法
	class StringHelper{
	private:
		static char change(int c);

		static bool oneofchar(char c,char split[] ,int len){
			for( int i= 0 ; i < len ; i++){
				if( c == split[i]) return true;
			}
			return false;
		}

	public:
		//*******************************************************************
		// 功能:	  小数按照精度转化为字符串
		// 传入参数:  value欲转化的小数,decplaces精度
		// 返回值:	  转化后的字符串结果
		//*******************************************************************
		static std::string DoubleToStr(const long double value,const int decplaces);
		/**
		* 去除左空格   
		*/
		static void LeftTrim(std::string& str);

		/**
		* 去除右空格
		*/
		static void RightTrim(std::string& str);

		/**
		* 去除左右空格
		*/
		static void Trim(std::string& str);


		/**
		* 转化为大写
		*/
		static void ToUpper(std::string& str);

		/**
		* 转化为小写
		*/
		static void ToLower(std::string& str);


		/*到 string，可能会增加前导0；
		*len是转换后的长度
		*/
		template <class T> static std::string ToString(const T& str ,const int len )
		{

			std::string s = ToString(str);
			int a = len-(int)s.length();
			if(a>0) //需要补充前导0
			{
				std::string t(a,'0');
				return t+s;
			}
			else
				return s;

		}

		/**
		* 转换函数,将输入的T型的值转化为string
		*/
		template <class T> static std::string ToString(const T& str)
		{
			std::ostringstream ostream;		
			ostream<<str;
			std::istringstream istream(ostream.str());
			std::string value;
			istream>>value;
			return value; 
		}

		/**
		* 转换函数,将输入的string的值转化为T型
		*/
		template <typename T> static  T ToNumber(const std::string& str);


		/**
		*输出16进制，2007-04-12
		const void *p  数据
		const string&  16进制数据之间的输出分割符号
		*/
		static std::string ToHex(const void *p,const int len,const std::string& split="",bool needorigin=false);
		static std::string ToHex(const unsigned char *p,const int len,const std::string& split="",bool needorigin=false);
		static std::string ToHex(const std::string& str,const std::string& split="",bool needorigin=false);

		//将num转换为len长的16进制字符串
		static std::string ToHex(const unsigned char num,int len = 2);

	   /***
		*
		*使用多个分割字傅进行字符串分割
		* 
		*/
		template<class K> static std::vector<K> ToVector(const std::string& field,char split[],int len = 1)
		{
			std::vector<K> vec;

			//2010-1-6 lumengyi 增加输入string空值的判断
			string localvalue = field;
			Trim(localvalue);
			if(localvalue.empty()) return vec;
			if (len == 1 )
				return  ToVector<K>(field,split[0]);

			std::string ss = field+split[0]; //添加一个以方便分割.

			size_t  strlen= ss.length();
			unsigned int i = 0;
			bool found = false;
			std::string::size_type pos0 = 0;
			
			while( i < strlen )
			{
				if( oneofchar(ss[i],split,len)){
					std::string s = ss.substr(pos0,i-pos0);
					
					K a = ToNumber<K>(s);
					vec.push_back(a);
					pos0 = i + 1; //要把 分隔符跳过
				}
				i++;
			}
			return vec;
		}

		/***
		* 输入值是 格式是(1,2,3,4)的形式
		* 转换为vector类型的值
		* 
		*/
		template<class K> static std::vector<K>  ToVector(const std::string& field,const char split='#')
		{
			std::vector<K> vec;

			//2010-1-6 lumengyi 增加输入string空值的判断
			string localvalue = field;
			Trim(localvalue);
			if(localvalue.empty()) return vec;

			//2008-07-23取消该行代码，在外由使用者手动调用
		    //std::string str = StringHelper::TrimChar(field); //去除可能的括号
			std::string str = field;
			std::string::size_type pos0 = str.find_last_of(split);
    		if(pos0 == std::string::npos || pos0 != str.length()-1)   //如果没有,或者最后一个没有,
	    		str = str+split; //附加一个方便分析
	    	
	    	pos0 = 0;
		    std::string::size_type pos1 = 0;
        	
			 while(true)
			 {
				pos1=str.find(split,pos0);//从pos0开始查找#
				if(pos1 == pos0) 
					break;//只有#数据
				std::string field = str.substr(pos0,pos1-pos0);

				K a = ToNumber<K>(field);
				vec.push_back(a);
	
				pos0 = pos1+1;
				if(pos0>=str.length())
					break;//结束循环
			}
			return vec; 			    
		}

		/**
		* 分割字符串,类似key1=value1,将分割得到pair类型
		* @return 返回值:pair  ,pair.first = key1,pair.second=value
		*
		*/
		template <class K,class V> static std::pair<K,V>  ToPair(const std::string& str,const char split='=')
		{
			std::pair<K,V> p1;
			
			//2010-1-6 lumengyi 增加输入string空值的判断
			string localvalue = str;
			Trim(localvalue);
			if(localvalue.empty()) return p1;

			std::string::size_type pos = str.find(split);
			std::string key = str.substr(0,pos);
			std::string value = str.substr(pos+1);
			Trim(key);
			Trim(value);
			
			p1.first =StringHelper::ToNumber<K>(key);
			p1.second = StringHelper::ToNumber<V>(value);
			return p1;
		}

		/**
		* 分割字符串,类似key1=value1#key2=value2#key3=value3，得到一个map
		*
		*/
		template<class K,class V>static std::map<K,V>  ToMap(const std::string& str,const char split='=',const char Split='#')
		{
			std::map<K,V> datas;

			//2010-1-6 lumengyi 增加输入string空值的判断
			string localvalue = str;
			Trim(localvalue);
			if(localvalue.empty()) return datas;

			std::string s1,s2=str;
			s2=s2+Split;//末尾补上一个分割符
			std::string::size_type pos=s2.find(Split);
			s1=s2.substr(0,pos);
			s2=s2.substr(pos+1);
			Trim(s1);
			std::pair<K,V>p=ToPair<K,V>(s1,split);//通过产生pair插入到图中
			datas.insert(p);
			while(s2.length()>1)
			{
				std::string::size_type pos=s2.find(Split);
				s1=s2.substr(0,pos);
				Trim(s1);
				s2=s2.substr(pos+1);
				p=ToPair<K,V>(s1,split);//产生pair
				datas.insert(p);
			}
			return datas;
		}



		/**
		* 本函数用来去除字符串首尾两边的特定字符，如将(f1=abc)--〉f1=abc
		* 
		*/	
		static std::string TrimChar(const std::string& str,char c= '(');

		static bool ParseMessage(std::vector<std::string> &obj, const std::string& field, const char seperator=',');
		
		static bool ParseMessage(std::vector<std::string> &obj, const std::string& field, const std::vector<int> & membersize);

		static std::string ToOctal(unsigned int n);

		static std::wstring string2wstring(const std::string& s);

		static std::string wstring2string(const std::wstring& ws);

		static std::string doubleTostring(const long double value,const int decplaces);

		//将str分割成std::string数组，分隔符由delimiter指定。比如abcd###efg###ddd--〉变成三个字符串
		static std::vector<std::string> Split(const std::string str,char delimiter);
	};  //class

	template <typename T> inline T StringHelper::ToNumber(const std::string& str)
	{
		T value;
		std::istringstream istream(str);
		istream>>value;
		return value;
	}

	template <> inline std::string StringHelper::ToNumber<std::string>(const std::string& str)
	{
		return str;
	}

};//namespace



#endif

