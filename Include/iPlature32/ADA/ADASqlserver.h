/*********************************************************************
 *		
 *  文      件:    ADASqlserver.h   		
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：
 *
 *  版本历史		
 *      1.0    2009-08-13    lumengyi    创建
 *     
*********************************************************************/
#ifndef	_ADASQLSERVER_H_
#define	_ADASQLSERVER_H_
#include <Sqlserver/Sqlserver.h>

namespace ADA
{
	struct ADASqlserver
	{
		typedef Sqlserver::SqlserverConnection Connection;
		typedef Sqlserver::SqlserverResultSet ResultSet;
		typedef Sqlserver::SqlserverStatement Statement;
		typedef Sqlserver::SqlserverParameter Parameter;
		typedef Sqlserver::SqlserverColumn Column;
		typedef Sqlserver::DataTypesEnum DataTypesEnum;
	};
}

#endif