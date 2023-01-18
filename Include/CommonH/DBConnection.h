/*********************************************************************
*  ��      ��:CDBConnection
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*  �� ְ ��//TODO�������ļ���ʼ�����ݿ����ӳ�
*              ��//TODO
*              ��//TODO
*  �汾��ʷ		
*       1.0    2011-03-07    ���    //TODO����
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
	string m_DB_TYPE;//���ݿ�����
	string m_DB_UserName;//�û���
	string m_DB_PassWord;//����
	string m_DB_DBName;//���ݿ�ʵ����
	static CDBConnection * m_DBConnection;

public:
	iDA::Connection m_DBCon;

public:
	CDBConnection(void);
	~CDBConnection(void);
	static CDBConnection * GetInstance();

	//��ʼ��
	void Initialize();

	//�������ļ�
	void GetBofConfig();

	//��ʼ�����ݿ����ӳأ��������ݿ�
	void IniConnectionPool(const string& strUserName, const string& strPassWord, const string& strDBName);
};
#endif