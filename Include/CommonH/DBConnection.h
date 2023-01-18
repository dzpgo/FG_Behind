/*********************************************************************
*  类      名:CDBConnection
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*  类 职 责：//TODO读配置文件初始化数据库连接池
*              ：//TODO
*              ：//TODO
*  版本历史		
*       1.0    2011-03-07    杨海荣    //TODO创建
*     
*********************************************************************/
#pragma once
#ifndef _CDBConnection_H_
#define _CDBConnection_H_

#include <iDA/iDA.h>
#include <iDA/ConnectionPool.h>
#include "PreDefine.h"
#include <log4cplus/LOG.h>

using namespace iPlature;

const char SPLIT_VERTICALLINE[] = "|";
const char SPLIT_COMMA[] = ",";
const string STRING_NULL = "999999";
const long INT_NULL = 999999;

class CDBConnection
{
private:
	string m_DB_TYPE;//数据库类型
	string m_DB_UserName;//用户名
	string m_DB_PassWord;//密码
	string m_DB_DBName;//数据库实例名
	static CDBConnection * m_DBConnection;

public:
	iDA::Connection m_DBCon;

public:
	CDBConnection(void);
	~CDBConnection(void);
	static CDBConnection * GetInstance();

	//初始化
	void Initialize();

	//读配置文件
	void GetBofConfig();

	//初始化数据库连接池，连接数据库
	void IniConnectionPool(const string& strUserName, const string& strPassWord, const string& strDBName);
};
#endif