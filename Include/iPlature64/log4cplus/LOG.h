/*********************************************************************
 *		
 *  文      件:    LOG.h   		interface for the LOG class.
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//TODO请添加本文件包含功能详细描述
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2006-10-12    lihaigang       创建
 *      1.0    2007-03-25    xuchangsheng    修改
 *      1.0    2007-11-26    xuchangsheng    改变16进制的参数，char * --> void *
 *      1.0    2008-03-21    xuchangsheng    添加flag，避免doConfigure多次
 *      1.1    2009-05-22    lujianwei       添加支持多线程多日志文件输出
 *      1.1    2009-06-23    lujianwei       App4Log.cfg中添加%f配置项，用于把文件名在log中输出
 *      1.1    2009-07-06    lujianwei       修改多线程调用时没有执行doThreadConfigure时内存泄露的bug
 *      1.1    2009-07-07    lujianwei       修改同一条线程避免多次doThreadConfigure
 *      1.1    2009-07-14    lujianwei       添加eraseThreadInstance方法，用于去除线程的配置
 *      1.1    2009-11-24    lujianwei       整合doConfigure，支持主进程、分支、多线程日志
 *      %USER%   
*********************************************************************/

#if _WIN32_WINNT < 0x0400
#undef  _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#ifndef AFX_LOG_H__345E073D_7445_4768_962C_E572847596D5__INCLUDED_
#define AFX_LOG_H__345E073D_7445_4768_962C_E572847596D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdarg.h>				// va_start on linux
#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/fileappender.h>
//处理16进制
#include <utility/StringHelper.h>
//
//using namespace std;
using namespace baosight;
using namespace log4cplus;
//using namespace log4cplus::helpers;

namespace log4cplus 
{
	typedef enum
	{
		ROOT_CONFIG			= 1		//主进程log初始化调用
		,THREAD_CONFIG		= 2		//多线程log初始化调用
		,BRANCH_CONFIG		= 3		//分支log初始化调用
	}en_config_type;

	typedef enum
	{
		AUTO_CATCH_PID		= 1		//用于线程构造，自动获取线程ID
	}en_thread;

	typedef enum
	{
		LOG_SUCCESS				= 0		//读配置成功
		,LOG_CONFIG_UNEXIST		= 1		//App4Log.cfg配置文件不存在
		,LOG_PATH_UNEXIST		= 2		//log输出目录不存在
		,LOG_ONLY_ONCE_FAILD	= 3		//相同的doConfigure不能执行多遍
		,LOG_OTHER				= 4		//其他错误
	}en_doconfigure_error_code;

	class LOG4CPLUS_EXPORT LOG  
	{
	public:
		/**********************************************************************
		 *  概述: 带参构造，供主进程log用
		 *  函数名： LOG 
		 *  返回值： 	 	//TODO:返回值描述
		 *  参数列表：	参数类型    				取值范围     		    描述
		 *    category:	[IN] const std::string &	//TODO:参数取值范围		log输出标识
		 *
		 *  版本历史		
		 *       1.0    2007-03-25  xuchangsheng    实现功能
		 *       1.1    2009-11-24  jacklu			添加多类型设置
		 *  
		 **********************************************************************/
		LOG(const std::string& category);

		/**********************************************************************
		 *  概述: 带参构造，供分支log用
		 *  函数名： LOG 
		 *  返回值： 	 	//TODO:返回值描述
		 *  参数列表：			参数类型    				取值范围     		    描述
		 *    category  :		[IN] const std::string &	//TODO:参数取值范围		log输出标识
		 *    strLogFileName  : [IN] const std::string &	//TODO:参数取值范围		日志名称
		 *
		 *  版本历史		
		 *       1.1    2009-11-24  jacklu    实现功能
		 *  
		 **********************************************************************/
		LOG(const std::string& category, const std::string& strLogFileName);

		/**********************************************************************
		 *  概述: 带参构造，供多线程log用
		 *  函数名： LOG 
		 *  返回值： 	 	//TODO:返回值描述
		 *  参数列表：		参数类型    				取值范围     		    描述
		 *    category  :   [IN] const std::string &	//TODO:参数取值范围		log输出标识
		 *    nThreadID  :  [IN] int					//TODO:参数取值范围		线程号
		 *
		 *  版本历史		
		 *       1.1    2009-11-24  jacklu    实现功能
		 *  
		 **********************************************************************/
		LOG(const std::string& category, int nThreadID);
	public:
		virtual ~LOG();

	public:
		typedef LOG& (*Manipulator)(LOG&);
		LOG& operator<<(Manipulator  pf);

		LOG& Debug();
		LOG& Info();
		LOG& Warn();
		LOG& Error();
		LOG& Fatal();
		LOG& flush();

		template<typename T> LOG& operator <<(const T& t)
		{
			if (!buffer) 
			{
				if (!(buffer = new log4cplus::tostringstream)) 
				{
					// memory malloc error,just return
					return *this;
				}
			}
			(*buffer) << t;
			return *this;
		}

	private:
		/**********************************************************************
		 *  概述: 开始处理日志
		 *  函数名： DealLog4cplus 
		 *  返回值： int	 	//TODO:返回值描述
		 *  参数列表：		参数类型    				取值范围     		    描述
		 *    strBuffer  :  [IN] const std::string &	//TODO:参数取值范围		日志缓存
		 *    nCurlevel  :  [IN] LogLevel				//TODO:参数取值范围		日志级别
		 *
		 *  版本历史		
		 *       1.0    2009-11-24  jacklu    实现功能
		 *  
		 **********************************************************************/
		int DealLog4cplus(const std::string& strBuffer, LogLevel nCurlevel);

	public:
		/**********************************************************************
		 *  概述: 日志配置
		 *  函数名： doConfigure 
		 *  返回值： int	 	0：成功，1：App4Log.cfg配置文件不存在，2：log输出目录不存在
		 *						3：相同的doConfigure不能执行多遍，4：其他错误
		 *  参数列表：		参数类型    				取值范围     		    描述
		 *    strLogName:	[IN] const std::string &	//TODO:参数取值范围		log文件名称
		 *    nType  :		[IN] int					//TODO:参数取值范围		日志类型，默认为主进程日志
		 *
		 *  版本历史		
		 *       1.0    2007-03-25  xuchangsheng    实现功能
		 *       1.1    2009-11-24  jacklu			修改读配置，把主进程、分支、线程日志配置合并
		 *       1.1    2009-11-30  jacklu			添加错误返回值以及对配置文件和日志生成路径的检查
		 *  
		 **********************************************************************/
		static int doConfigure(const std::string& strLogName, int nType = ROOT_CONFIG);

		/**********************************************************************
		 *  概述: 日志配置
		 *  函数名： doConfigure 
		 *  返回值： int	 	0：成功，1：App4Log.cfg配置文件不存在，2：log输出目录不存在
		 *						3：相同的doConfigure不能执行多遍，4：其他错误
		 *  参数列表：		参数类型    				取值范围     		    描述
		 *    strLogName  : [IN] const std::string &	//TODO:参数取值范围		log文件名称
		 *    strLogConfig:	[IN] const std::string &	//TODO:参数取值范围		log配置文件
		 *    strLogDir  :  [IN] const std::string &	//TODO:参数取值范围		log输出路径
		 *    nType  :		[IN] int					//TODO:参数取值范围		日志类型，默认为主进程日志
		 *
		 *  版本历史		
		 *       1.1    2009-11-24  jacklu		实现功能
		 *       1.1    2009-11-30  jacklu		添加错误返回值以及对配置文件和日志生成路径的检查
		 *  
		 **********************************************************************/
		static int doConfigure(const std::string& strLogName, const std::string& strLogConfig, 
								const std::string& strLogDir, int nType = ROOT_CONFIG);

		/**********************************************************************
		*  概述: 去除已有配置
		*  函数名： remove 
		*  返回值： void	 	//TODO:返回值描述
		*  参数列表：		参数类型    				取值范围     		    描述
		*  strLogName  :    [IN] const std::string &	//TODO:参数取值范围		日志名称，默认为去除线程配置
		*
		*  版本历史		
		*       1.0    2009-07-14  jacklu    //实现功能
		*  
		**********************************************************************/
		static void remove(const std::string& strLogName = log4cplus::thread::getCurrentThreadName());

		/**********************************************************************
		*  概述: 设置线程log级别
		*  函数名： setThreadLogLevel 
		*  返回值： void	 	//TODO:返回值描述
		*  参数列表：	参数类型    	取值范围     		    描述
		*    ll  :    [IN] LogLevel		//TODO:参数取值范围		log级别
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			根据调用方式实现等级设置
		*  
		**********************************************************************/
		void setLogLevel(LogLevel ll);

		/**********************************************************************
		*  概述: Debug，用于流输出
		*  函数名： Debug 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    					取值范围     		    描述
		*    strMsg  :    [IN] const std::string&	     //TODO:参数取值范围	log输出信息
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Debug(const std::string& strMsg);	

		/**********************************************************************
		*  概述: Debug，用于十六进制输出
		*  函数名： DebugHex 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    			取值范围     			描述
		*    data  :    [IN] void *				//TODO:参数取值范围		首地址
		*    len  :		[IN] const int			//TODO:参数取值范围		数据长度（字节
		*    split  :   [IN] const string &		//TODO:参数取值范围		分隔的字符
		*    needorigin:[IN] bool				//TODO:参数取值范围		是否需要输出原始数据
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int DebugHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  概述: Debug，用于printf格式输出
		*  函数名： Debug 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    				取值范围     		    描述
		*    strformat  :    [IN] const char *	    //TODO:参数取值范围		  log输出信息
		*      :    [IN] ...						//TODO:参数取值范围		  <//TODO:参数描述>
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Debug(const char* strFormat,...);

		/**********************************************************************
		*  概述: Info，用于流输出
		*  函数名： Info 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    					取值范围     		    描述
		*    strMsg  :    [IN] const std::string&	    //TODO:参数取值范围		log输出信息
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Info(const std::string& strMsg);

		/**********************************************************************
		*  概述: Info，用于十六进制输出
		*  函数名： InfoHex 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    			取值范围     			描述
		*    data  :    [IN] void *				//TODO:参数取值范围		首地址
		*    len  :		[IN] const int			//TODO:参数取值范围		数据长度（字节
		*    split  :   [IN] const string &		//TODO:参数取值范围		分隔的字符
		*    needorigin:[IN] bool				//TODO:参数取值范围		是否需要输出原始数据
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int InfoHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  概述: 线程Info，用于printf格式输出
		*  函数名： ThreadInfo 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    			取值范围     		    描述
		*    strformat  :[IN] const char *	    //TODO:参数取值范围		log输出信息
		*      :    [IN] ...					//TODO:参数取值范围		<//TODO:参数描述>
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Info(const char* strFormat,...);

		/**********************************************************************
		*  概述: Warn，用于流输出
		*  函数名： Warn 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    				取值范围     		    描述
		*    strMsg  :  [IN] const std::string&	    //TODO:参数取值范围		log输出信息
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Warn(const std::string& strMsg);

		/**********************************************************************
		*  概述: Warn，用于十六进制输出
		*  函数名： WarnHex 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    			取值范围     			描述
		*    data  :    [IN] void *				//TODO:参数取值范围		首地址
		*    len  :		[IN] const int			//TODO:参数取值范围		数据长度（字节
		*    split  :   [IN] const string &		//TODO:参数取值范围		分隔的字符
		*    needorigin:[IN] bool				//TODO:参数取值范围		是否需要输出原始数据
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int WarnHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  概述: Warn，用于printf格式输出
		*  函数名： Warn 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    			取值范围     		    描述
		*    strformat  :[IN] const char *	    //TODO:参数取值范围		log输出信息
		*      :    [IN] ...					//TODO:参数取值范围		<//TODO:参数描述>
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Warn(const char* strFormat,...);

		/**********************************************************************
		*  概述: Error，用于流输出
		*  函数名： Error 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    					取值范围     		    描述
		*    strMsg  :    [IN] const std::string&	     //TODO:参数取值范围	log输出信息
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Error(const std::string& strMsg);

		/**********************************************************************
		*  概述: 线程Error，用于十六进制输出
		*  函数名： ThreadErrorHex 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    			取值范围     			描述
		*    data  :    [IN] void *				//TODO:参数取值范围		首地址
		*    len  :		[IN] const int			//TODO:参数取值范围		数据长度（字节
		*    split  :   [IN] const string &		//TODO:参数取值范围		分隔的字符
		*    needorigin:[IN] bool				//TODO:参数取值范围		是否需要输出原始数据
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int ErrorHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  概述: Error，用于printf格式输出
		*  函数名： Error 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：		参数类型    			取值范围     		    描述
		*    strformat  :   [IN] const char *	    //TODO:参数取值范围		log输出信息
		*      :    [IN] ...						//TODO:参数取值范围		<//TODO:参数描述>
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Error(const char* strFormat,...);
		
		/**********************************************************************
		*  概述: Fatal，用于流输出
		*  函数名： Fatal 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    					取值范围     		    描述
		*    strMsg  :    [IN] const std::string&	     //TODO:参数取值范围		log输出信息
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Fatal(const std::string& strMsg);

		/**********************************************************************
		*  概述: 线程Fatal，用于十六进制输出
		*  函数名： FatalHex 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    			取值范围     			描述
		*    data  :    [IN] void *				//TODO:参数取值范围		首地址
		*    len  :		[IN] const int			//TODO:参数取值范围		数据长度（字节
		*    split  :   [IN] const string &		//TODO:参数取值范围		分隔的字符
		*    needorigin:[IN] bool				//TODO:参数取值范围		是否需要输出原始数据
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int FatalHex(void* data,const int len,const std::string& split=" ",bool needorigin=true);

		/**********************************************************************
		*  概述: Fatal，用于printf格式输出
		*  函数名： Fatal 
		*  返回值： int	 	0：成功。1：失败
		*  参数列表：	参数类型    					取值范围     		    描述
		*    strformat  :    [IN] const char *	    //TODO:参数取值范围		  log输出信息
		*      :    [IN] ...						//TODO:参数取值范围		  <//TODO:参数描述>
		*
		*  版本历史		
		*       1.0    2007-03-25  xuchangsheng		实现功能
		*       1.1    2009-11-24  jacklu			提取处理日志功能
		*  
		**********************************************************************/
		int Fatal(const char* strFormat,...);
		void print(){std::cout<<"hi ,in LOG"<<std::endl;}

	private:
		log4cplus::tostringstream *buffer;
		std::string prefix;
		LogLevel curlevel;//current log level
		
	private:
		std::string m_strLogFileName;
		int			m_nType;
		static int flag ; //2008-03-21防止多次初始化
	};
}

namespace std
{
	LOG4CPLUS_EXPORT log4cplus::LOG& endl(log4cplus::LOG& log);
}
#endif // !defined(AFX_LOG_H__345E073D_7445_4768_962C_E572847596D5__INCLUDED_)

//#define _WIN32

