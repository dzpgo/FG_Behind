/*********************************************************************
*		
*  ��      ��:    MsgItemInfo.h   		//TODO������ļ�����
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������//TODO����ӱ��ļ�����������ϸ����
*        ��//TODO
*        ��//TODO
*
*  �汾��ʷ		
*      1.0    2012-02-13    Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
*      %USER%   
*********************************************************************/
#ifndef __MSG_ITEM_IFNO_H__
#define __MSG_ITEM_IFNO_H__
#include <string>
#include <vector>
#include <IceUtil/Shared.h>
#include <IceUtil/Handle.h>
#include <PowerTranser/MsgItemDataType.h>
namespace iPlature
{
	//////////////////////////////////////////////////////////////////////////

	/*typedef enum _MsgItemDataType
	{
		ITEM_DT_INT
		, ITEM_DT_DOUBLE
		, ITEM_DT_STRING
		, ITEM_DT_ACK
		, ITEM_DT_BCD4
		, ITEM_DT_BCD8
		, ITEM_DT_BYTE
		, ITEM_DT_HEX
		, ITEM_DT_INT2
		, ITEM_DT_RINT2
		, ITEM_DT_RINT4
		, ITEM_DT_TIME
		, ITEM_DT_RFLOAT
		, ITEM_DT_GROUP
	}MsgItemDataType;*/

	typedef struct _MsgItemInfo
	{
		typedef std::vector<_MsgItemInfo> VecMsgItemInfo;

		std::string _name;
		//MsgItemDataType _DataType;		//����
		iPlature::MsgItemDataType _DataType;				//haykin 2012-9-24
		int	_Length;				//����
		int _binaryLen;
		std::string _Format;			//��ʽ
		std::string _MsgTableField;	//���ݱ��ֶ���
		double _Scale;			//ϵ��
		std::string _DefVal;			//Ĭ��ֵ
		int _count;
		VecMsgItemInfo _subItem;

		_MsgItemInfo(const std::string& name
							, const std::string& dtType
							, int nLen
							, const std::string& fmt
							, const std::string& tbField
							, double scale
							, const std::string& defVal
							, int count);
	}MsgItemInfo;
}

#endif

