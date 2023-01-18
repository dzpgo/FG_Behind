#ifndef __CDATETIME_H_BBB_
#define __CDATETIME_H_BBB_
/*****************************************************************************
* 
* �ַ��������࣬����string�Ĺ���
* 2007-07-04  �쳤ʢ now-->static Now
* 2007-04-09  �쳤ʢ ���ע��
* 2007-04-04  ½��ΰ ��ɴ���ı�д
* 2007-03-26  �쳤ʢ ������ȡ����
* 2010-08-26  ½��ΰ AIX��
* ��Դ��oralib�еĹ���
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
*��������ʱ����
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

		//���ַ�����ʼ��
		CDateTime(const std::string& str,const std::string pattern="yyyyMMddhhmmss");	

		//��������ʼ��
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

		//��ȡ��ǰʱ��
		static CDateTime Now(void);

		//��ʱ��������ת��Ϊ�ַ���
		std::string ToString(void);

		//��ʱ��������ת��Ϊ����
		time_t ToSec(void);

		//������ת��Ϊʱ��������
		CDateTime& FromSec(time_t& fromsec);

		//�����������
		CDateTime& operator + (const long& o);

		//�����������
		CDateTime& operator - (const long& o);

		//��ǰֵ������ֵ�Ƚ�
		int Compare(CDateTime anotherDate);

		//��ǰֵС������ֵ
		bool After(CDateTime when);

		//��ǰֵ��������ֵ
		bool Before(CDateTime when);

		//�õ�ǰֵΪ���ֵ
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

		//�õ�ǰֵΪ��Сֵ
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

		//�жϵ�ǰֵ�Ƿ�Ϊ���ֵ
		bool isMAX(void);

		//�жϵ�ǰֵ�Ƿ�Ϊ��Сֵ
		bool isMIN(void);

	};
};

#endif

