/*********************************************************************
*		
*  文      件:    DataAccess.h   		//TODO请概述文件功能
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：数据库基类
*        ：完成数据库的连接
*
*  版本历史		
*      1.0    2010-06-03    fzz    根据软件设计书添加文件
*      1.1    2013-03-28    sxd    修改
*      %USER%   
*********************************************************************/
#pragma once
#ifndef _DATAACCESS_H_
#define _DATAACCESS_H_

#include <iDA/iDA.h>
#include <string>
#include <vector>

#include "PreDefine.h"

using namespace std;
//#include "DBDefine.h"
using namespace iPlature;

namespace Monitor
{

		 const char SPLIT_VERTICALLINE[] = "|";
		 const char SPLIT_COMMA[] = ",";

	    static const string DB_STR_NULL = "999999";
	    static const long DB_INT_NULL =999999;
		static const iDA::DateTime  DB_TIME_NULL(1970,01,01,00,00,00);

		static const string DF_STR_NULL = "";
		static const long DF_INT_NULL = -1;

/*********************************************************************
		*  类      名:   	CDataAccess
		*  版权所有:   Shanghai Baosight Software Co., Ltd.
		*  类 职 责：数据库基类
		*              ：完成数据库的连接
		*  版本历史		
		*       1.0    2010-06-03    fzz    根据软件设计书添加类
		*     
		*********************************************************************/
		class CDataAccess
		{
		public:
			/**********************************************************************
			*  概述: 析构函数
			*  函数名： ~CDataAccess 
			*  返回值： 	 	无
			*  参数列表：	参数类型    					取值范围     		    描述
			*
			*  版本历史		
			*       1.0    2010-06-03  fzz    添加函数
			*  
			**********************************************************************/
			~CDataAccess(void);

			/**********************************************************************
			*  概述: 初始化数据库信息，连接数据库
			*  函数名： Initialize 
			*  返回值： void	 	
			*  参数列表：	参数类型    					取值范围     		    描述
			*
			*  版本历史		
			*       1.0    2010-05-29  fzz    添加函数
			*  
			**********************************************************************/
			void Initialize(void);

			/**********************************************************************
			*  概述: 释放初始化信息,关闭数据库连接
			*  函数名： UnInitialize 
			*  返回值： int	 	成功：0  失败：1
			*  参数列表：	参数类型    					取值范围     		    描述
			*
			*  版本历史		
			*       1.0    2010-06-03  fzz    添加函数
			*  
			**********************************************************************/
			void UnInitialize(void);

			static CDataAccess* GetInstance(void);

			/**********************************************************************
			*  概述: 获取数据库连接字符串
			*  函数名： GetConnectionString 
			*  返回值： int	 	成功：0  失败：1
			*  参数列表：	参数类型    					取值范围     		    描述
			*
			*  版本历史		
			*       1.0    2010-06-03  fzz    添加函数
			*  
			**********************************************************************/
			void GetConnectionString(void);

		private:
			CDataAccess(void);

		public:
			iDA::Connection m_DBCon;

		private:
			static CDataAccess*	m_pDBInstance;
			string m_strUsername;					//数据库用户名			
			string m_strPassword;					//数据库密码			
			string m_strDatabase;					//数据库SID
			string m_strDBStatus;					//数据库类型

		public:
			static bool isDBTimeNULL(iPlature::iDA::DateTime theValue);
		};

}
#endif