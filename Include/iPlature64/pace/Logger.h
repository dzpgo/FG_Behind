/*********************************************************************
 *		
 *  文      件:    Logger.h   		//TODO请概述文件功能
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2011-02-12    Haykin-2010    //TODO请添加本次主要修改内容
 *      %USER%   
*********************************************************************/
#ifndef _PACE_LOGGER_H_
#define _PACE_LOGGER_H_
#include <string>
#include <sstream>
#include <Ice/Identity.h>
//#include <log4cplus/LOG.h>

namespace log4cplus
{
	class LOG;
}

namespace iPlature
{ 
	/**
	* pace::Logger类
	* 根据不同的级别,方法,输出方式,布局等进行日志输出
	* 日志级别: debug < info < notice <  warn < error < alert < fatal
	* 推荐使用最常用日志级别：debug < warn < error
	*/
	class Log
	{ 
	public:
		/**
		* Logger流的操作符函数类型
		*/
		typedef Log& (*Manipulator)(Log&);

		/**
		* Logger类构建器
		* 创建Logger对象,生成指定的Log目录,并在当前LOG目录记录log.start信息
		*
		* @param category 日志目录,多个层次日志目录用点分隔,
		* 如:app.function或者namespace.class.method等.
		*/
		Log(std::string category);
		/**
		* Log类析构器
		* 清除Log对象缓存,记录Log.end信息
		*/
		~Log();
		/**
		* 改变Log对象的Log记录级别为debug
		* @return 当前Log对象
		*/
		Log& debug();	
		/**
		* 按照printf格式输出debug级别日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		void debug(const char* _format, ...) throw();
		/**
		* 输出debug级别日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/
		void debug(const std::string& message) throw();
		/**
		* 改变Log对象的Log记录级别为debug
		* @return 当前Log对象
		*/
		Log& info();
		/**
		* 按照printf格式输出debug级别日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		void info(const char* _format, ...) throw();
		/**
		* 输出info级别日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/
		void info(const std::string& message) throw();
		/**
		* 改变Log对象的Log记录级别为notice
		* @return 当前Log对象
		*/
		//Log& notice();
		/**
		* 按照printf格式输出notice级别日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		//void notice(const char* _format, ...) throw();
		/**
		* 输出notice级别日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/      
		//void notice(const std::string& message) throw();
		/**
		* 改变Log对象的Log记录级别为warn
		* @return 当前Log对象
		*/
		Log& warn();
		/**
		* 按照printf格式输出warn级别日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		void warn(const char* _format, ...) throw();
		/**
		* 输出warn级别日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/
		void warn(const std::string& message) throw();
		/**
		* 改变Log对象的Log记录级别为error
		* @return 当前Log对象
		*/
		Log& error();
		/**
		* 按照printf格式输出error级别日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		void error(const char* _format, ...) throw();
		/**
		* 输出error级别日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/
		void error(const std::string& message) throw();
		/**
		* 改变Log对象的Log记录级别为alert
		* @return 当前Log对象
		*/
		//Log& alert();
		/**
		* 按照printf格式输出alert级别日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		//void alert(const char* _format, ...) throw();
		/**
		* 输出alert级别日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/
		//void alert(const std::string& message) throw();
		/**
		* 改变Log对象的Log记录级别为fatal
		* @return 当前Log对象
		*/
		Log& fatal();
		/**
		* 按照printf格式输出fatal级别日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		void fatal(const char* _format, ...) throw();
		/**
		* 输出fatal级别日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/
		void fatal(const std::string& message) throw();
		/**
		* 按照printf格式输出当前Log对象所具有级别的日志信息
		* @param _format 日志格式化信息串
		* @param ...   对应_format格式串的值列表
		*/
		//void log(const char* _format, ...) throw();     
		/**
		* 当前Log对象所具有级别的日志信息,格式为std::string类型
		* @param message 日志信息字符串
		*/
		//void log(const std::string& message) throw();
		/**
		* 同步流式日志消息
		* @return 当前Log对象
		* @see operator<<
		*/      
		Log& flush();
		/**
		* Log流的操作符
		* @param pf Manipulator类型的Log流操作符函数指针
		* @return 当前Log对象
		* @see std::endl
		* @see Manipulator
		* @see template<typename T> Log& operator <<(const T& t)
		*/
		Log& operator<<(Manipulator  pf)
		{
			return (*pf)(*this);
		};
		/**
		* Log输入流方法
		* @param t 模板类型,输入到Log流的值对象
		* @return 当前Log对象
		*/
		template<typename T> Log& operator <<(const T& t)
		{
			//if (!_buffer) 
			//{
			//	if (!(_buffer = new std::ostringstream)) 
			//	{
			//		// memory malloc error,just return
			//		return *this;
			//	}
			//}
			//(*_buffer) << t;
			(*_impl)<<t;
			return *this;
		}
		/**
		* 根据配置文件来设置Log环境.
		* 静态成员函数,影响当前进程所有Log对象.
		* @param configFile 配置文件全路径字符串
		*/
		static void configure(const std::string& configFile);
		/**
		* 关闭日志环境,静态成员函数,关闭后所有Log对象都将失效.
		*/
		/*static void shutdown();*/

		int DebugHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

	private:
		Log();
		/*void* _category;
		std::ostringstream* _buffer;
		int _priority;*/

		log4cplus::LOG* _impl;
	};

}//namespace pace

namespace std
{
	/**
	* 格式化一个Log对象,效果相当于调用Log对象的flush方法.
	* @param log 待格式化的Log对象
	* @return 被endl操作符格式化后的Log对象
	*/
	iPlature::Log& endl(iPlature::Log& log);
}
iPlature::Log& operator<<(iPlature::Log&,const Ice::Identity& id);

#endif
