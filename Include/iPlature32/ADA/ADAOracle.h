/*********************************************************************
 *		
 *  ��      ��:    ADAOracle.h   		
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������
 *
 *  �汾��ʷ		
 *      1.0    2009-08-06    lumengyi    //TODO����ӱ�����Ҫ�޸�����
 *     
*********************************************************************/
#ifndef	_ADAORACLE_H_
#define	_ADAORACLE_H_
#include <db/_p.h>
#include <db/oralib.h>

namespace ADA
{
	struct ADAOracle
	{
		typedef oralib::connection Connection;
		typedef oralib::resultset ResultSet;
		typedef oralib::statement Statement;
		typedef oralib::parameter Parameter;
		typedef oralib::column Column;
		typedef oralib::DataTypesEnum DataTypesEnum;
	};
}

#endif