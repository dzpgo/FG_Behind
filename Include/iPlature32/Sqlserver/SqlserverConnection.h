/*********************************************************************
 *		
 *  文      件:    SqlserverConnection.h   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：
 *
 *  版本历史		
 *      1.0    2009-08-12    linchangbo    创建
 *     
*********************************************************************/
#pragma once
#include <Sqlserver/Sqlserver.h>
//#include <Sqlserver/SqlserverResultSet.h>
//#include <Sqlserver/SqlserverStatement.h>
#include <string>
#include <vector>

namespace Sqlserver
{
	class SqlserverResultSet;
	class SqlserverStatement;
	class SqlserverConnection
	{
	private:
		std::string _longin;
		std::string _password;
		std::string _servicename;
		_ConnectionPtr m_pConnection;
		std::vector<SqlserverResultSet*> resultsets;
		std::vector<SqlserverStatement*> statements;
	public:
		SqlserverConnection();
		SqlserverConnection(const std::string& login,const std::string& password,const std::string& service_name);
		~SqlserverConnection(void);
		/**********************************************************************
		*  概述: 打开数据库连接
		*  函数名： open
		*  返回值： SqlserverParameter&		参数对象
		*  参数列表：	参数类型    					取值范围     	描述
		*  login  :  [IN] const std::string&	     				    登陆名
		*  password:  [IN] const std::string&	     				    密码
		*  service_name:  [IN] const std::string&	     				服务器名\\数据库实例名/数据库名（例如WINSERVER1\\SQLEXPRESS/iPlature）
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		void open (const std::string& login,const std::string& password,const std::string& service_name);
		/**********************************************************************
		*  概述: 关闭数据库连接
		*  函数名： close
		*  返回值： void
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		void close();
		/**********************************************************************
		*  概述: 重新打开数据库连接
		*  函数名： reopen
		*  返回值： void
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		void reopen();
		/**********************************************************************
		*  概述: 执行SQL语句
		*  函数名： execute
		*  返回值： int		执行SQL语句后产生影响的记录数
		*  参数列表：	参数类型    					取值范围     	描述
		*  sql_block  :  [IN] const std::string&	     				SQL语句
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		int execute(const std::string& sql_block);
		/**********************************************************************
		*  概述: 准备SQL语句
		*  函数名： prepare
		*  返回值： SqlserverStatement*		准备SQL语句并获得SqlserverStatement对象
		*  参数列表：	参数类型    					取值范围     	描述
		*  sql_block  :  [IN] const std::string&	     				SQL语句
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		SqlserverStatement* prepare(const std::string& sql_block);
		/**********************************************************************
		*  概述: 准备SQL语句
		*  函数名： select
		*  返回值： SqlserverResultSet*		准备SQL语句并获得SqlserverResultSet对象
		*  参数列表：	参数类型    					取值范围     	描述
		*  sql_block  :  [IN] const std::string&	     				SQL语句
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		SqlserverResultSet* select(const std::string& sql_block);
		/**********************************************************************
		*  概述: 开始事务
		*  函数名： beginTrans
		*  返回值： void
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		void beginTrans();
		/**********************************************************************
		*  概述: 提交事务
		*  函数名： commit
		*  返回值： void
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		void commit();
		/**********************************************************************
		*  概述: 回滚事务
		*  函数名： rollback
		*  返回值： void
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		void rollback();
		/**********************************************************************
		*  概述: 释放资源
		*  函数名： release
		*  返回值： void
		*  参数列表：	参数类型    					取值范围     	描述
		*
		*  版本历史		
		*       1.0    2009-09-07  lumengyi    添加注释
		*  
		**********************************************************************/
		void release();
	};
}