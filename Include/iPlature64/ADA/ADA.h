/*********************************************************************
*		
*  文      件:    ADA.h   		
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：
*
*  版本历史		
*      1.0    2009-08-10    lumengyi    创建
*     
*********************************************************************/
#include <ADA/IConnection.hpp>
#include <ADA/IStatement.hpp>
#include <ADA/IResultSet.hpp>

//迄今为止所支持的数据库适配器
#include <ADA/ADAOracle.h>
#include <ADA/ADASqlserver.h>

//当前所使用数据库类型
#define ORACLE_DB

//当前所使用数据库库文件
#ifdef WIN32
	#ifdef ORACLE_DB
		#ifdef _DEBUG
			#pragma comment(lib,"oralib.lib")
		#else
			#pragma comment(lib,"oralibR.lib")
		#endif
	#endif
	#ifdef SQLSERVER_DB
		#pragma comment(lib,"sqlserver.lib")
	#endif
#endif