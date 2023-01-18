/*********************************************************************
*		
*  ��      ��:    DataTime.h
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������ͨ�����ݿ�ӿ�DateTime�࣬�������ݿ��е�����
*
*  �汾��ʷ		
*      1.0    2009-12-08    lumengyi    ����
*	    1.0   2010-06-09	haykin		����<< ���Ľ�ToString��ʽ  YYYY-MM-DD HH:MI:SS 
*      1.0    2010-10-11    haykin   operator time_t() const;  /    operator long() const;��linux��ͻ
*********************************************************************/
#pragma once
#include <sys/timeb.h>
#include <string>
namespace iPlature
{
	namespace iDA
	{
		class DateTimeImpl;

		class DateTime
		{
			friend class Parameter;
		public:
			DateTime();
			~DateTime();
			DateTime(const DateTime& other);
			DateTime& operator=(const DateTime& other);

			DateTime(const tm& tmValue);
			DateTime(const struct timeb& tmbValue);
			//DateTime(const struct timeval& tmvValue);
			DateTime(double dt);									//��Ϊ��λ
			DateTime(const time_t& tm);						//��Ϊ��λ			haykin 2010-9-20
			
			DateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);
			DateTime(const std::string& strDayTime); //  yyyymmddhh24miss
			DateTime(const std::string& time_string,const std::string& time_format);

			int GetYear() const;		// year, f.ex., 1999, 2000
			int GetMonth() const;		// 1..12
			int GetDay() const;			// 1..31
			int GetHour() const;		// 0..23
			int GetMinute() const;		// 0..59
			int GetSecond() const;		// 0..59
			operator double() const;
			std::string ToString() const;  // yyyy-mm-dd hh24:mi:ss

			std::string ToShortTimeString() const; //yyyymmddhh24mi::ss

			DateTime operator+(long interval) const;
			DateTime operator-(long interval) const;
			DateTime& operator+=(long interval);
			DateTime& operator-=(long interval);
			long operator-(const DateTime& dt) const;

			DateTime& operator = (const std::string & str);

			operator time_t() const;					//ת��Ϊ��
#ifdef _WIN32
			operator long() const;
#endif

			//friend std::ostream& operator << (std::ostream& o, const DateTime& tm);
			
			void SetYear(int nYear);
			void SetMonth(int nMonth);
			void SetDay(int nDay);
			void SetHour(int nHour);
			void SetMinute(int nMinute);
			void SetSecond(int nSecond);

			static DateTime Now();
		private:
			DateTimeImpl* _impl;
		};

		std::ostream& operator << (std::ostream& o, const DateTime& tm);
	}//namespace iDA
}//namespace iPlature
