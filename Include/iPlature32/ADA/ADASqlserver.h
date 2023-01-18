/*********************************************************************
 *		
 *  ��      ��:    ADASqlserver.h   		
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������
 *
 *  �汾��ʷ		
 *      1.0    2009-08-13    lumengyi    ����
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