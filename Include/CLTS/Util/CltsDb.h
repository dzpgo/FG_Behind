#pragma once
#include <iostream>
#include <pace/pace.h>
#include <iDA/iDA.h>
#include <iDA/ConnectionPool.h>
#include <log4cplus/LOG.h>
#include <Slice/CltsException.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** 数据库链接.
		 *  函数名： dbConn 
		 *  返回值： int					iDA操作返回值
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    con     : iDA::Connection&                            iDA数据库链接
		 *    strCfgfile : string                            		链接字符串配置文件
		 */		
		int dbConn(iDA::Connection & con, string strCfgfile);

		/** SQL操作.
		 *  函数名： dbExecute 
		 *  返回值： int					iDA操作返回值
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    command    : iDA::Command&                            iDA数据库命令
		 *    file : string                            				链接字符串配置文件
		 *    line : int                            				链接字符串配置文件
		 */				
		int dbExecute(LOG& log, iDA::Command& command, string file, int line);

		/** 立即提交.
		 *  函数名： dbCommit 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    pCon    : iDA::Connection*                            数据库连接指针
		 */
		void dbCommit(LOG& log, iDA::Connection* pCon);

		/** 立即回滚.
		 *  函数名： dbCommit 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    pCon    : iDA::Connection*                            数据库连接指针
		 */
		void dbRollback(LOG& log, iDA::Connection* pCon);

		/** 创建事务开始(根据上下游信息).
		 *  函数名： transactionBegin 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log : LOG                                             日志对象
		 *    current : const Ice::Current&                         调用上下游数据
		 *    strFunc : const string&								被调函数名
		 */
		void transactionBegin(LOG& log, Ice::Current& current, const string& strFunc);

		/** 事务提交(根据上下游信息提交).
		 *  函数名： transactionCommit 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    timeStart :  IceUtil::Time                            调用开始时间
		 *    pCon    : iDA::Connection*                            数据库连接指针
		 *    caller  : const Ice::Current&		                    调用上下游信息
		 *    function : const string&                              当前调用函数
		 */
		void transactionCommit(LOG& log, IceUtil::Time timeStart, iDA::Connection* pCon, const Ice::Current& caller, const string& function);

		/** 事务回滚(根据上下游信息回滚).
		 *  函数名： transactionRollback 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    log     : LOG&                                        日志实例
		 *    timeStart :  IceUtil::Time                            调用开始时间
		 *    pCon    : iDA::Connection*                            数据库连接指针
		 *    caller  : const Ice::Current&		                    调用上下游信息
		 *    function : const string&                              当前调用函数
		 */
		void transactionRollback(LOG& log, iDA::Connection* pCon, const Ice::Current& caller, const string& function);
	}
}
