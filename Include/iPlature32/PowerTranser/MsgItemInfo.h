/*********************************************************************
*		
*  文      件:    MsgItemInfo.h   		//TODO请概述文件功能
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：//TODO请添加本文件包含功能详细描述
*        ：//TODO
*        ：//TODO
*
*  版本历史		
*      1.0    2012-02-13    Haykin-2010    //TODO请添加本次主要修改内容
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
		//MsgItemDataType _DataType;		//类型
		iPlature::MsgItemDataType _DataType;				//haykin 2012-9-24
		int	_Length;				//长度
		int _binaryLen;
		std::string _Format;			//格式
		std::string _MsgTableField;	//数据表字段名
		double _Scale;			//系数
		std::string _DefVal;			//默认值
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

