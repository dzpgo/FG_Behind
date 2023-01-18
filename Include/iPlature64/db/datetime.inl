
/**
2007 -08 -09  �ֿ���datetime.h��cpp
*2007 -08 -07 �޸�
UNIX��Linux��ʱ��ϵͳ����Epoch��ʼ�����𣬵�λΪ�룬
Epoch����ָ��Ϊ1970��һ��һ���賿���������룬��������ʱ�䡣

       char *asctime(const struct tm *timeptr);
       char *ctime(const time_t *timep);
       struct tm *gmtime(const time_t *timep);
       struct tm *localtime(const time_t *timep);
	   time_t mktime(struct tm *timeptr);

       The ctime(), gmtime() and localtime() functions  all  take
       an  argument of data type time_t which represents calendar
       time.  When interpreted as an absolute time value, it rep-
       resents  the  number  of seconds elapsed since 00:00:00 on
       January 1, 1970, Coordinated Universal Time (UTC).

       The asctime() and mktime() functions both take an argument
       representing  broken-down time which is a binary represen-
       tation separated into year, month, day, etc.   Broken-down
       time  is  stored  in  the structure tm which is defined in
       <time.h> as follows:

              struct tm
              {
                      int     tm_sec;         
                      int     tm_min;         
                      int     tm_hour;        
                      int     tm_mday;        
                      int     tm_mon;         
                      int     tm_year;        
                      int     tm_wday;        
                      int     tm_yday;       
                      int     tm_isdst;       
              };

��time.hͷ�ļ��У����ǻ����Կ���һЩ���������Ƕ�����time_tΪ�������ͻ򷵻�ֵ���͵ĺ�����

double difftime(time_t time1, time_t time0);
time_t mktime(struct tm * timeptr);
time_t time(time_t * timer);
char * asctime(const struct tm * timeptr);
char * ctime(const time_t *timer);

���⣬time.h���ṩ�����ֲ�ͬ�ĺ���������ʱ�䣨һ����time_t��ʾ��������ת��Ϊ����ƽʱ�����İ�������ʱ����ֿ���ʾ��ʱ���ʽtm��

struct tm * gmtime(const time_t *timer);
struct tm * localtime(const time_t * timer);
����gmtime()�����ǽ�����ʱ��ת��Ϊ�����׼ʱ�䣨����������ʱ�䣩��������һ��tm�ṹ�����������ʱ�䣬��localtime()�����ǽ�����ʱ��ת��Ϊ����ʱ�䡣����������gmtime()������õ������׼ʱ����2005��7��30��7��18��20�룬��ô����localtime()�������й�������õı���ʱ���������׼ʱ����8��Сʱ����2005��7��30��15��18��20��
*
*/


#ifndef	_DATETIME_INL
#define	_DATETIME_INL

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>


// switch off alignment
#ifdef __DECCXX
#pragma member_alignment save
#pragma nomember_alignment
#elif defined(_MSC_VER)
#pragma pack(push)
#pragma pack(4)
#elif defined(_LINUX)
#pragma pack(4)
#else // hpux 11
#pragma pack 4
#endif

/*
struct OCIDate
{
  sb2 OCIDateYYYY;          gregorian year; range is -4712 <= year <= 9999 /
  ub1 OCIDateMM;                           month; range is 1 <= month < 12 
  ub1 OCIDateDD;                              day; range is 1 <= day <= 31 
  OCITime OCIDateTime;                                                time 
};
*/
using namespace std;

const int YEAR = 1900;
namespace oralib {

//2008-06-26 ��ͳ�ƺ�����
enum STATEnum{
  ST_MAX,
  ST_MIN,
  ST_COUNT,
  ST_AVG,
  ST_SUM
};

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


// helper date/time class with no input validation at all
class datetime
{
private:
	sb2		y;
	MonthsEnum	m;
	ub1		d;
	ub1		h;
	ub1		i;
	ub1		s;

public:
	inline datetime (void) {
		struct tm local;
		time_t  nse = TIMEMAX;
		local = *localtime(&nse);
		y = (sb2) (local.tm_year + YEAR);
		m = (MonthsEnum) (local.tm_mon + 1);
		d = (ub1)local.tm_mday;
		h = (ub1)local.tm_hour;
		i = (ub1)local.tm_min;
		s = (ub1)local.tm_sec;
	};

/*
*2038��һ��ʮ��������һ����ʮ��ʮ�ķ�����
*/
	inline datetime (
		IN ub1 dd,
		IN MonthsEnum mm,
		IN ub2 yyyy,
		IN OPTIONAL ub1 hh = 0,
		IN OPTIONAL ub1 mi = 0,
		IN OPTIONAL ub1 ss = 0) : y (yyyy), m (mm), d (dd), h (hh), i (mi), s (ss)
		{ };

	/**
	*2007-10-18 add
	*/
	void setYear(sb2 year){
		if(year > 2038 || year < 1970)
			y = 1970;
		else
			y = year;
	}

	void setMonth(ub1 month){
		if(month >12 || month < 1)
			m = (MonthsEnum)1;
		else
			m = (MonthsEnum)month;
	}

	void setDay(ub1 day){
		d = day;
	}

	void setHour(ub1 hour){
		h = hour;
	}

	void setMinute(ub1 minute){
		i = minute;
	}

   void setSecond(ub1 second){
		s = second;
	}

	inline datetime (
		IN const OCIDate& o)
		{ operator = (o); };

	/**
	*ʹ��string�������ڣ�Oracle yyyymmddhh24miss��ʽ

	*/
	inline datetime (const string & str) 
	{
		int iLen;
		int flag = 0;
		int icmp = 0;
		const char * strTemp = str.c_str();
		char strYear[5];
		char strtp[3];

		strYear[4] = '\0';//�������ϣ�����c�������������
		strtp[2] = '\0';

		iLen = (int)strlen(strTemp);
		if (iLen != 14)
		{
			flag = 1;
		}
		else
		{
			memcpy(strYear,strTemp,4);
			y = (sb2)atoi(strYear);
			strTemp += 4;

			memcpy(strtp,strTemp,2);
			m = (MonthsEnum)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			d = (ub1)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			h = (ub1)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			i = (ub1)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			s = (ub1)atoi(strtp);

			struct tm tmTosec;

			/*
			struct tm  
			{  
				int tm_sec;  
				int tm_min;  
				int tm_hour;  
				int tm_mday;  
				int tm_mon;  
				int tm_year;  
				int tm_wday;  
				int tm_yday;  
				int tm_isdst;  
			};  

			tm_sec���롹������[0,61]֮�䣬������������������������������õġ�  
			tm_min���֡�������[0,59]֮�䡣  
			tm_hour��ʱ��������[0,23]֮�䡣  
			tm_mday�����µڼ��ա�����[1,31]֮�䡣  
			tm_mon������ڼ��¡�����[0,11]֮�䡣  
			tm_year  ............Ҫ��1900��ʾ��һ�ꡣ  
			tm_wday�����ڼ��ա�����[0,6]֮�䡣  
			tm_yday������ڼ��ա�����[0,365]֮�䣬������366�ա�  
			tm_isdst���Ƿ�Ϊ���չ��Լʱ�䡹��
			*/
			tmTosec.tm_year = (int)y - YEAR;
			tmTosec.tm_mon = (int)m - 1;
			tmTosec.tm_mday = (int)d;
			tmTosec.tm_hour = (int)h;
			tmTosec.tm_min = (int)i;
			tmTosec.tm_sec = (int)s;
			tmTosec.tm_isdst = -1;


			time_t tosec;
			//time_t mktime(struct tm *tp);  
			//ת��tm��Ϊtime_t��ʽ��ʹ�ñ���ʱ�䡣  
			//��ʱ��ṹ����ת���ɾ���������,
			tosec = mktime(&tmTosec);   
			
			if (tosec > TIMEMAX || tosec < 0)
			{
				flag = 1;
			}
			else
			{
				struct tm local;		
				local = *localtime(&tosec);
				//localtime_s(&local,&tosec);

				icmp += ((local.tm_year + YEAR) - (int)y) + ((local.tm_mon + 1) - (int)m) + (local.tm_mday - (int)d);
				icmp += (local.tm_hour - (int)h) + (local.tm_min - (int)i) + (local.tm_sec - (int)s);
				if (icmp != 0)
				{
					flag = 1;
				}
			}			
		}

		if (flag == 1)
		{					
			y = (sb2) (2038);
			m = (MonthsEnum) (1);
			d =  18;
			h = 19;
			i = 14;
			s = 7;
		}
	};

	//2007 - 8 -9 add
	static  datetime parse(const string & str) {
	   datetime dt(str);
	   return dt;
	}

		//2007 - 8 -9 add
	static  datetime parse(const char*  p) {
	   string str(p);
		datetime dt(str);
	   return dt;
	}
	
	inline datetime (time_t& nse) 
	{
		if (nse > TIMEMAX || nse < 0)
		{
			nse = TIMEMAX;
		}
		struct tm local;	
		local = *localtime(&nse);
		//localtime_s(&local,&nse);

		y = (sb2) (local.tm_year + YEAR);
		m = (MonthsEnum) (local.tm_mon + 1);
		d = (ub1)local.tm_mday;
		h = (ub1)local.tm_hour;
		i = (ub1)local.tm_min;
		s = (ub1)local.tm_sec;
	};

public:
	inline ub1 day (void) const { return (d); };
	inline void day (
		IN ub1 dd)
		{ d = dd; };

	inline MonthsEnum mon (void) const
		{ return (m); };
	inline void mon (
		IN MonthsEnum mm)
		{ m = mm; };

	inline sb2 year (void) const
		{ return (y); };
	inline void year (
		IN sb2 yy)
		{ y = yy; };

	inline ub1 hour (void) const
		{ return (h); };
	inline void hour (
		IN ub1 hh)
		{ h = hh; };

	inline ub1 minute (void) const
		{ return (i); };
	inline void minute (
		IN ub1 mi)
		{ i = mi; };

	inline ub1 sec (void) const
		{ return (s); };
	inline void sec (
		IN ub1 ss)
		{ s = ss; };

	/* 2007 - 08-07 ����
	*/
	inline datetime& operator = (const string & str){
         datetime dt(str);
		 *this = dt;
		 return *this;

	}

	inline datetime& operator = (const datetime & dt){
        this->y = dt.y;
		this->m = dt.m;
		this->d = dt.d;
		this->h = dt.h;
		this->i = dt.i;
		this->s = dt.s;


		 return *this;

	}


	inline datetime& operator = (
		IN const OCIDate& o)
	{
		y = o.OCIDateYYYY;
		m = (MonthsEnum) (o.OCIDateMM);
		d = o.OCIDateDD;
		h = o.OCIDateTime.OCITimeHH;
		i = o.OCIDateTime.OCITimeMI;
		s = o.OCIDateTime.OCITimeSS;
		return (*this);
	};


	inline void set (
		OUT OCIDate& o) const
	{
		o.OCIDateYYYY = y;
		o.OCIDateMM = static_cast <ub1> (m);
		o.OCIDateDD = d;
		o.OCIDateTime.OCITimeHH = h;
		o.OCIDateTime.OCITimeMI = i;
		o.OCIDateTime.OCITimeSS = s;
	};

    inline time_t toSec(void) 
	{
		struct tm tmTosec;
		tmTosec.tm_year = (int)y - YEAR;
		tmTosec.tm_mon = (int)m - 1;
		tmTosec.tm_mday = (int)d;
		tmTosec.tm_hour = (int)h;
		tmTosec.tm_min = (int)i;
		tmTosec.tm_sec = (int)s;

		time_t tosec;
		tosec = mktime(&tmTosec);

		if (tosec > TIMEMAX || tosec < 0)
		{
			tosec = TIMEMAX;
		}

		return tosec;
	};

	inline datetime& fromSec(time_t& fromsec)
	{
		if (fromsec > TIMEMAX || fromsec < 0)
		{
			fromsec = TIMEMAX;
		}
		struct tm local;	
		local = *localtime(&fromsec);
		//localtime_s(&local,&fromsec);

		y = (sb2) (local.tm_year + YEAR);
		m = (MonthsEnum) (local.tm_mon + 1);
		d = (ub1)local.tm_mday;
		h = (ub1)local.tm_hour;
		i = (ub1)local.tm_min;
		s = (ub1)local.tm_sec;

		return *this;
	};

		inline datetime& operator + (
		IN const long& o)
	{
		struct tm tmTosec;
		tmTosec.tm_year = (int)y - YEAR;
		tmTosec.tm_mon = (int)m - 1;
		tmTosec.tm_mday = (int)d;
		tmTosec.tm_hour = (int)h;
		tmTosec.tm_min = (int)i;
		tmTosec.tm_sec = (int)s;

		time_t tosec;
		tosec = mktime(&tmTosec);

		tosec += (time_t)o;

		struct tm local;		
		local = *localtime(&tosec);
		//localtime_s(&local,&tosec);

		y = (sb2) (local.tm_year + YEAR);
		m = (MonthsEnum) (local.tm_mon + 1);
		d = (ub1)local.tm_mday;
		h = (ub1)local.tm_hour;
		i = (ub1)local.tm_min;
		s = (ub1)local.tm_sec;

		return (*this);
	};

		//2007-10-19 add
	inline long operator - (IN  datetime other)
	{
		time_t t1 = toSec();
		time_t t2 = other.toSec();
		double a = difftime(t1,t2);
		return (long)a;
	};


	inline datetime& operator - (IN const long& o)
	{
		struct tm tmTosec;
		tmTosec.tm_year = (int)y - YEAR;
		tmTosec.tm_mon = (int)m - 1;
		tmTosec.tm_mday = (int)d;
		tmTosec.tm_hour = (int)h;
		tmTosec.tm_min = (int)i;
		tmTosec.tm_sec = (int)s;

		time_t tosec;
		tosec = mktime(&tmTosec);

		tosec -= (time_t)o;

		struct tm local;		
		local = *localtime(&tosec);
		//localtime_s(&local,&tosec);

		y = (sb2) (local.tm_year + YEAR);
		m = (MonthsEnum) (local.tm_mon + 1);
		d = (ub1)local.tm_mday;
		h = (ub1)local.tm_hour;
		i = (ub1)local.tm_min;
		s = (ub1)local.tm_sec;

		return (*this);
	};

	inline string toString(string pattern="yyyymmddhhmiss") 
	{
		char stringTemp[16];
		memset(stringTemp,0,sizeof(stringTemp));
		char * strTemp = (char *)stringTemp;

		//int j;
		sprintf(strTemp,"%d",(int)y);	
		strTemp += 4;
		//j  = sprintf_s( stringTemp, 16,"%d",(int)y);
		
		if ((int)m > 9)
		{
			sprintf(strTemp,"%d",(int)m);			
			strTemp += 2;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)m );
		}
		else
		{
			sprintf(strTemp,"%d",0);			
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", 0 );
			sprintf(strTemp,"%d",(int)m);			
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)m );
		}

		if ((int)d > 9)
		{
			sprintf(strTemp,"%d",(int)d);
			strTemp += 2;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)d );
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", 0);
			sprintf(strTemp,"%d",(int)d);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)d );
		}

		if ((int)h > 9)
		{
			sprintf(strTemp,"%d",(int)h);
			strTemp += 2;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)h );
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", 0 );
			sprintf(strTemp,"%d",(int)h);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)h );
		}

		if ((int)i > 9)
		{
			sprintf(strTemp,"%d",(int)i);
			strTemp += 2;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)i );
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", 0 );
			sprintf(strTemp,"%d",(int)i);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)i );
		}

		if ((int)s > 9)
		{
			sprintf(strTemp,"%d",(int)s);
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)s );
			
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", 0 );
			sprintf(strTemp,"%d",(int)s);
			//j += sprintf_s( stringTemp + j, 16 - j,"%d", (int)s );
		}			

		//string str = string(stringTemp);
		string str(stringTemp);		

		return str;

	};

	static datetime Now(void)
	{
		datetime ddd;
		time_t aclock;
		aclock = time(NULL);
		struct tm local;	
		local = *localtime(&aclock);
		//localtime_s(&local,&aclock);

		ddd.y = (sb2) (local.tm_year + YEAR);
		ddd.m = (MonthsEnum) (local.tm_mon + 1);
		ddd.d = (ub1)local.tm_mday;
		ddd.h = (ub1)local.tm_hour;
		ddd.i = (ub1)local.tm_min;
		ddd.s = (ub1)local.tm_sec;

		return ddd;
	};

	
	inline string toDateString(void) 
	{
		char stringTemp[20];
		char * strTemp = (char *)stringTemp;
		//int j;

		sprintf(strTemp,"%d-",(int)y);
		strTemp += 4 + 1;
		//j  = sprintf_s( stringTemp, 20,"%d-",(int)y);			

		if ((int)m > 9)
		{
			sprintf(strTemp,"%d-",(int)m);
			strTemp += 2 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d-", (int)m );
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d", 0 );
			sprintf(strTemp,"%d-",(int)m);
			strTemp += 1 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d-", (int)m );
		}

		if ((int)d > 9)
		{
			sprintf(strTemp,"%d ",(int)d);
			strTemp += 2 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d ", (int)d );
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d", 0 );
			sprintf(strTemp,"%d ",(int)d);
			strTemp += 1 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d ", (int)d  );
		}

		if ((int)h > 9)
		{
			sprintf(strTemp,"%d:",(int)h);
			strTemp += 2 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d:", (int)h );			
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d", 0 );			
			sprintf(strTemp,"%d:",(int)h);
			strTemp += 1 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d:", (int)h );			
		}

		if ((int)i > 9)
		{
			sprintf(strTemp,"%d:",(int)i);
			strTemp += 2 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d:", (int)i );			
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d", 0 );			
			sprintf(strTemp,"%d:",(int)i);
			strTemp += 1 + 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d:", (int)i );			
		}

		if ((int)s > 9)
		{
			sprintf(strTemp,"%d",(int)s);
			//j += sprintf_s( stringTemp + j, 20 - j,"%d", (int)s );			
		}
		else
		{
			sprintf(strTemp,"%d",0);
			strTemp += 1;
			//j += sprintf_s( stringTemp + j, 20 - j,"%d", 0 );			
			sprintf(strTemp,"%d",(int)s);	
			//j += sprintf_s( stringTemp + j, 20 - j,"%d", (int)s );			
		}			

		//string str = string(stringTemp);
		string str(stringTemp);

		return str;

	};

	static datetime MAX(void)
	{
		datetime temp;
		temp.year((sb2)2038);
		temp.mon((MonthsEnum)1);
		temp.day(18);
		temp.hour(19);
		temp.minute(14);
		temp.sec(7);

		return temp;
	}

	static datetime MIN(void)
	{
		datetime temp;
		temp.year((sb2)1970);
		temp.mon((MonthsEnum)1);
		temp.day(1);
		temp.hour(0);
		temp.minute(0);
		temp.sec(0);

		return temp;
	}

	inline bool isMAX(void)
	{
		int icmp = 0;
		bool bRet;
		icmp += ((int)y - 2038) + ((int)m - 1) + ((int)d - 18) + ((int)h - 19) + ((int)i - 14) + ((int)s - 7);		
		if (icmp == 0)
		{
			bRet = 1;
		}
		else
		{
			bRet = 0;
		}
		return bRet;
	};

	inline bool isMIN(void)
	{
		int icmp = 0;
		bool bRet;
		icmp += ((int)y - 1970) + ((int)m - 1) + ((int)d - 1) + ((int)h - 0) + ((int)i - 0) + ((int)s - 0);		
		if (icmp == 0)
		{
			bRet = 1;
		}
		else
		{
			bRet = 0;
		}
		return bRet;
	};

/*
* 
*/
	inline datetime& fromString(const string & str)
	{
		int iLen;
		int temp = 0;
		int icmp = 0;
		const char * strTemp = str.c_str();
		
		char strYear[5];
		strYear[4]='\0';
		char strtp[3];
		strtp[2] = '\0';
		
		iLen = (int)strlen(strTemp);
		if (iLen != 14)
		{
			temp = 1;
		}
		else
		{
			memcpy(strYear,strTemp,4);
			y = (sb2)atoi(strYear);
			strTemp += 4;

			memcpy(strtp,strTemp,2);
			m = (MonthsEnum)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			d = (ub1)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			h = (ub1)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			i = (ub1)atoi(strtp);
			strTemp += 2;

			memcpy(strtp,strTemp,2);
			s = (ub1)atoi(strtp);

			struct tm tmTosec;
			tmTosec.tm_year = (int)y - YEAR;
			tmTosec.tm_mon = (int)m - 1;
			tmTosec.tm_mday = (int)d;
			tmTosec.tm_hour = (int)h;
			tmTosec.tm_min = (int)i;
			tmTosec.tm_sec = (int)s;

			time_t tosec;
			tosec = mktime(&tmTosec);

			if (tosec > TIMEMAX || tosec < 0)
			{
				temp = 1;
			}
			else
			{
				struct tm local;		
				local = *localtime(&tosec);
				//localtime_s(&local,&tosec);

				icmp += ((local.tm_year + YEAR) - (int)y) + ((local.tm_mon + 1) - (int)m) + (local.tm_mday - (int)d);
				icmp += (local.tm_hour - (int)h) + (local.tm_min - (int)i) + (local.tm_sec - (int)s);
				if (icmp != 0)
				{
					temp = 1;
				}
			}			
		}

		if (temp == 1)
		{					
			y = (sb2) (2038);
			m = (MonthsEnum) (1);
			d =  18;
			h = 19;
			i = 14;
			s = 7;
		}
		return *this;
	}

}; // datetime class
static ostream& operator << ( ostream& out, datetime& dt)
{
	return out << dt.toDateString();
}

}; // oralib namespace

// switch on alignment
#ifdef __DECCXX
#pragma member_alignment restore
#elif defined(_MSC_VER)
#pragma pack(pop)
#elif defined(_LINUX)
#pragma pack()
#else // hpux 11
#pragma pack(pop)
#endif

#endif // _DATETIME_INL


