/*********************************************************************
 *		
 *  文      件:    Connection.h
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：通用数据库接口Connection类，代表数据库连接
 *
 *  版本历史		
 *      1.0    2009-12-08    lumengyi    创建
 *      1.0		2010-05-24	 haykin		reload operator Connect
 *		1.0		2010-07-12	 hyakin		add operator ReConnect
*********************************************************************/
#pragma once
#include <iDA/iDADef.h>
namespace iPlature
{
	namespace iDA
	{
		class ConnectionImpl;

		class Connection
		{
			friend class Command;
		public:
			Connection();
			~Connection();

			void Connect(const std::string& sDBString,
						const std::string& sUserName,
						const std::string& sPassword,
						iDA_Client_t eClient = iDA_Client_NotSpecified);

			/**********************************************************************
			 *  概述: 连接数据库
			 *  函数名： Connect 
			 *  返回值： void	 	
			 *  参数列表：	参数类型    					取值范围     		    描述
			 *    sDBString  :    [IN/OUT] const std::string &	     数据库名
			 *    sUserName  :    [IN/OUT] const std::string &	     用户名
			 *    sPassword  :    [IN/OUT] const std::string &	     密码
			 *    sClient  :    [IN/OUT] const std::string &	     字符串型数据库类型 oracle/db2/sqlserver/sqlite
			 *
			 *  版本历史		
			 *       1.0    2010-05-24  Haykin-2010    create
			 *  
			 **********************************************************************/
			void Connect(const std::string& sDBString,
						const std::string& sUserName,
						const std::string& sPassword,
						const std::string& sClient );

			/**********************************************************************
			 *  概述: 连接数据库
			 *  函数名： Connect 
			 *  返回值： void	 	
			 *  参数列表：	参数类型    					取值范围     		    描述
			 *    sConnectString  :    [IN/OUT] const std::string &	     数据库连接描述符 user/password@dbname
			 *    sClient  :    [IN/OUT] const std::string &			 字符串型数据库类型 oracle/db2/sqlserver/sqlite
			 *
			 *  版本历史		
			 *       1.0    2010-05-24  Haykin-2010    create
			 *  
			 **********************************************************************/
			void Connect(const std::string& sConnectString
					   , const std::string& sClient = "");

			bool IsConnected() const;
			bool IsAlive() const;
			void Disconnect();
			void Rollback();
			void Commit();
			void SetAutoCommit(iDA_AutoCommit_t eAutoCommit);
			iDA_AutoCommit_t AutoCommit() const;

			/**********************************************************************
			 *  概述: 重新连接数据库
			 *  函数名： ReConnect 
			 *  返回值： void	 	
			 *  参数列表：	参数类型    					取值范围     		    描述
			 *
			 *  版本历史		
			 *       1.0    2010-07-12  Haykin-2010    create
			 *  
			 **********************************************************************/
			void ReConnect();

			/**********************************************************************
			 *  概述: //TODO:请添加函数描述
			 *  函数名： Client 
			 *  返回值： iPlature::iDA::iDA_Client_t	 	数据库类型枚举对象
			 *  参数列表：	参数类型    					取值范围     		    描述
			 *    strClient  :    [IN/OUT] const std::string &				字符串型数据库类型 oracle/db2/sqlserver/sqlite
			 *
			 *  版本历史		
			 *       1.0    2010-05-24  Haykin-2010    //TODO请添加本次主要修改内容
			 *  
			 **********************************************************************/
			static iDA_Client_t Client(const std::string& strClient);

			//Gets the current DBMS client assigned for the connection.
			iDA_Client_t Client() const;
		private:
			ConnectionImpl* _impl;
		};
	}//namespace iDA
}//namespace iPlature
