#ifndef __CDATETIME_H_BBB_
#define __CDATETIME_H_BBB_
/*****************************************************************************
* 
* 字符串辅助类，扩充string的功能
* 2007-07-04  徐长盛 now-->static Now
* 2007-04-09  徐长盛 添加注释
* 2007-04-04  陆建伟 完成代码的编写
* 2007-03-26  徐长盛 单独提取出来
* 2010-08-26  陆建伟 AIX中
* 来源于oralib中的功能
******************************************************************************/
#include <string>
#include <iostream>

#ifdef _WIN32
#   include <sys/timeb.h>
#   include <time.h>
#pragma warning (disable : 4996)
#else
#   include <sys/time.h>
#endif

using namespace std;
/**
*宝信日期时间类
*
*/

const time_t TIMEMAX = 2147426047;

const int MAX_YEAR = 2038;
const int MAX_MONTH = 1;
const int MAX_DAY = 18;
const int MAX_HOUR = 19;
const int MAX_MINUTE = 14;
const int MAX_SECOND = 7;

const int MIN_YEAR = 1970;
const int MIN_MONTH = 1;
const int MIN_DAY = 1;
const int MIN_HOUR = 0;
const int MIN_MINUTE = 0;
const int MIN_SECOND = 0;

namespace baosight{
	enum MonthsEnum
	{
		jan = 1,
		feb,
		mar,
		apr,
		may,
		jun,
		jul,
		aug,
		sep,
		oct,
		nov,
		dec
	};

	class CDateTime{
	private:
		int				year;
		MonthsEnum		month;
		int				day;
		int				hour;
		int				minute;
		int				second;

	public:
		CDateTime (void);
		~CDateTime (void);

		CDateTime (
			int yyyy,
			MonthsEnum mm,
			int dd,			
			int hh,
			int mi,
			int ss);		

		//用字符串初始化
		CDateTime(const std::string& str,const std::string pattern="yyyyMMddhhmmss");	

		//用秒数初始化
		CDateTime(time_t& nse);

		int GetYear(void);		
		MonthsEnum GetMonth(void);		
		int GetDay();
		int GetHour();
		int GetMinute();
		int GetSecond();

		void SetYear(int y);
		void SetMonth(MonthsEnum mm);
		void SetDay(int d);
		void SetHour(int h);
		void SetMinute(int mi);
		void SetSecond(int s);

		//获取当前时间
		static CDateTime Now(void);

		//将时间日期类转化为字符串
		std::string ToString(void);

		//将时间日期类转化为秒数
		time_t ToSec(void);

		//把秒数转化为时间日期类
		CDateTime& FromSec(time_t& fromsec);

		//重载运算符＋
		CDateTime& operator + (const long& o);

		//重载运算符－
		CDateTime& operator - (const long& o);

		//当前值与输入值比较
		int Compare(CDateTime anotherDate);

		//当前值小于输入值
		bool After(CDateTime when);

		//当前值大于输入值
		bool Before(CDateTime when);

		//置当前值为最大值
		static CDateTime MAX(void)
		{	
			CDateTime temp;
			temp.SetYear(MAX_YEAR);
			temp.SetMonth((MonthsEnum)MAX_MONTH);
			temp.SetDay(MAX_DAY);
			temp.SetHour(MAX_HOUR);
			temp.SetMinute(MAX_MINUTE);
			temp.SetSecond(MAX_SECOND);

			return temp;
		}

		//置当前值为最小值
		static CDateTime MIN(void)
		{
			CDateTime temp;
			temp.SetYear(MIN_YEAR);
			temp.SetMonth((MonthsEnum)MIN_MONTH);
			temp.SetDay(MIN_DAY);
			temp.SetHour(MIN_HOUR);
			temp.SetMinute(MIN_MINUTE);
			temp.SetSecond(MIN_SECOND);

			return temp;
		}

		//判断当前值是否为最大值
		bool isMAX(void);

		//判断当前值是否为最小值
		bool isMIN(void);

	};
};

#endif

