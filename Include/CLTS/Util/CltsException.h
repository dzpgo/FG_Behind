#pragma once
#include <iostream>
#include <pace/pace.h>
#include <iDA/iDA.h>
#include <iDA/ConnectionPool.h>
#include <log4cplus/LOG.h>
#include <Slice/CltsException.h>
#include <Msg/MsgSetting.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** 抛出异常信息.
		 *  函数名： throwCltsEx 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    file    : const string&                               异常的文件名
		 *    line    : int                                         异常的行号
		 *    function: string                               		异常的函数名
		 *    type      : string&                             		异常概述
		 *    format : const char*                                  异常格式字符串
		 */
		void throwCltsEx(string file, int line, string function, string type, const char* format, ...);
		
		/** 抛出异常信息.
		 *  函数名： throwCltsEx 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    file    : const string&                               异常的文件名
		 *    line    : int                                         异常的行号
		 *    current : const Ice::Current&                         调用上下游数据
		 *    type      : string&                             		异常概述
		 *    format : const char*                                  异常格式字符串
		 */
		void throwCltsEx(string file, int line, const Ice::Current& current, string type, const char* format, ...);

		/** 捕获异常信息.
		 *  函数名： catchFunc 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    file    : const string&                               捕获异常的文件名
		 *    line    : int                                         捕获异常的行号
		 *    ex      : std::exception&                             异常信息
		 *    bThrowEx : bool                                       捕获后是否再次抛出异常
		 */
		void catchFunc( LOG& log, const string& file, int line, const string& function, std::exception& ex, bool bThrowEx = true);

		/** 捕获异常信息.
		 *  函数名： catchFunc 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    file    : const string&                               捕获异常的文件名
		 *    line    : int                                         捕获异常的行号
		 *    function : const string&                              发生异常的函数
		 *    ex      : std::exception&                             异常信息
		 *    bThrowEx : bool                                       捕获后是否再次抛出异常
		 */
		void catchFunc( LOG& log, const string& file, int line, const string& function, const IceUtil::Time& timeStart, std::exception& ex, bool bThrowEx = true);

		/** 捕获异常信息.
		 *  函数名： catchFunc 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    file    : const string&                               捕获异常的文件名
		 *    line    : int                                         捕获异常的行号
		 *    function : const string&                              发生异常的函数
		 *    timeStart : const IceUtil::Time&                      被调用的起始时间
		 *    current : const Ice::Current&                         调用上下游数据
		 *    ex      : std::exception&                             异常信息
		 *    bThrowEx : bool                                       捕获后是否再次抛出异常
		 */
		void catchFunc( LOG& log, const string& file, int line, const string& function, const IceUtil::Time& timeStart, const Ice::Current& current, std::exception& ex, bool bThrowEx = true);
	}
}
