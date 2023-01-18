/********************************************************************
	created:	2008/03/21
	created:	21:3:2008   16:23
	filename: 	d:\iPlature\include\db\orahelper.h
	file path:	d:\iPlature\include\db
	file base:	orahelper
	file ext:	h
	author:		zhaoyan
	
	purpose:	
	// ���connection����ʹ�þֲ����������ǳ����ӵ������
	// ��ôorahelper������connection�ر�֮ǰ�������release����
	// ��������cn����رգ�helper��������������statement��resultset����ʱ�ᷢ���ڴ���ʴ���
	// ��ʱ���Ѿ������ڴ�й¶
	


*********************************************************************/
#ifndef	_ORAHELPER_H
#define	_ORAHELPER_H

#pragma once

#include <db/_p.h>
#include <db/oralib.h>

using namespace oralib;
using namespace std;

class orahelper
{
	typedef vector<statement*> Statements;
	typedef map<string, statement*> StatementsMap;

	typedef vector<resultset*> Resultsets;
	typedef map<string, resultset*> ResultsetsMap;

	connection*		m_pConnection;
	Statements		m_vtrStatement;
	StatementsMap	m_mapStatement;
	Resultsets		m_vtrResultset;
	ResultsetsMap	m_mapResultset;

public:
	orahelper(connection& con);
public:
	~orahelper(void);

	statement&  prepare(const string& strSQL);
	resultset&  select(statement& st);
	resultset&	select(const string& strSQL);
	void		release();
};

#endif

