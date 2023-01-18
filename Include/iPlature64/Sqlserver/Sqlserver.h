/*********************************************************************
 *		
 *  文      件:    Sqlserver.h   		
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
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include <Sqlserver/datetime.h>

namespace Sqlserver
{
	enum DataTypesEnum
	{
		DT_UNKNOWN,
		DT_NUMBER,
		DT_DATE,
		DT_TEXT,
//		DT_RESULT_SET, unsupported
		DT_CLOB
	};

	typedef const char* Pstr;
	typedef _com_error error;
}

#include <Sqlserver/SqlserverConnection.h>
#include <Sqlserver/SqlserverStatement.h>
#include <Sqlserver/SqlserverResultSet.h>
#include <Sqlserver/SqlserverParameter.h>
#include <Sqlserver/SqlserverColumn.h>