/********************************************************************
	created:	2008/03/21
	created:	21:3:2008   16:23
	filename: 	d:\iPlature\include\db\orahelper.h
	file path:	d:\iPlature\include\db
	file base:	orahelper
	file ext:	h
	author:		zhaoyan
	
	purpose:	
	// 如果connection对象使用局部变量，不是常连接的情况下
	// 那么orahelper对象在connection关闭之前必须调用release方法
	// 否则由于cn对象关闭，helper对象在析构回收statement和resultset对象时会发生内存访问错误
	// 此时，已经发生内存泄露
	


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

