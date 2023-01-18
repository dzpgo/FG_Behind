/*********************************************************************
 *		
 *  文      件:    DateTime.h   		日期时间类
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：日期时间方法
 *
 *  版本历史		
 *      1.0    2011-05-19    Haykin-2010    create
 *      %USER%   
*********************************************************************/
#ifndef __IPLATURE_DATETIME_H__
#define __IPLATURE_DATETIME_H__
#include <Ice/Config.h>
#include <iostream>
#include <string>
namespace IceUtil
{
  class Time;
}
namespace iPlature
{
typedef Ice::Long Long;
class DateTime
{
public:
   DateTime();
   DateTime(Long t);
   DateTime(const IceUtil::Time& t);
   DateTime(const int year,const int mon,const int day,const int hour=0,const int min=0,const int sec=0);
   DateTime(const char* time_string,const char *time_format);
   static DateTime now();
   static DateTime tomorrow();
   static DateTime yesterday();
   static DateTime days(const int t);
   static DateTime hours(const int t);
   static DateTime minutes(const int t);
   static DateTime seconds(const int t);
   static DateTime milliSeconds(const Long t);
   static DateTime microSeconds(const Long t) ;
   operator Long() const;
   DateTime& operator=(Long rhs);
   Long toDays() const;
   Long toHours() const;
   Long toMinutes() const;
   Long toSeconds() const;
   Long toMilliSeconds() const;
   Long toMicroSeconds() const;
   std::string toDuration() const;

   //FORMAT %Y-%m-%d %H:%M:%S.%FF3
   std::string toString(std::string format="") const;

   //YYYY-MM-DD HH24:MI:SS
   std::string toDateTimeStr() const;
   //YYYYMMDDHH24MISS
   std::string toShortDateTimeStr() const;
   //YYYY-MM-DD HH24:MI:SS:MilsSec
   std::string toLongDateTimeStr() const;

   //HH24:MI:SS
   std::string toTimeStr() const;
   //HH24:MI:SS:MilsSec
   std::string toLongTimeStr() const;

   int year() const;
   int month() const;
   int week() const;
   int day() const;
   int hour() const;
#ifndef _WIN32
   int min() const;
#endif
   int minute() const;
   int second() const;
   int millisec() const;
   bool isToday() const;
   DateTime operator-() const;
   DateTime operator-(const DateTime& rhs) const;
   DateTime& operator-=(const DateTime& rhs);
   DateTime operator+(const DateTime& rhs) const;
   DateTime& operator+=(const DateTime& rhs);
   operator IceUtil::Time() const;
   bool operator<(const DateTime& rhs) const;
   bool operator>(const DateTime& rhs) const;
   bool operator<=(const DateTime& rhs) const;
   bool operator>=(const DateTime& rhs) const;
   bool operator==(const DateTime& rhs) const;
   bool operator!=(const DateTime& rhs) const;
   double operator/(const DateTime& rhs) const;
   template<typename T> 
   double operator*(T rhs) const
   {
      return _t * rhs;
   }
   template<typename T> 
   DateTime& operator/=(T rhs) const
   {
       _t /= rhs;
       return *this;
   }
   template<typename T> 
   DateTime& operator*=(T rhs) const
   {
      _t *= rhs;
      return *this;
   }
private:
   Long  _t;
};
std::ostream& operator<<(std::ostream& out, const DateTime& dt);
}//end namespace pace.
#endif
