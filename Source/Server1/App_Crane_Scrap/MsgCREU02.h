/*********************************************************************
 *		
 *  文      件:    MsgCREU02.h   		
 *
 *
 *  概述：
 *        ：MsgCREU02 为单例类
 *        ：接收所有行车PLC发来的行车故障报警数据
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为HandleMessage  接收的参数为电文内容的byteSeq
 *  版本历史		
 *      2017年04月建立
*********************************************************************/

#pragma once
#ifndef _MsgCREU02_
#define _MsgCREU02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CranePLCAlarmBase.h"

#include "CraneMonitor.h"



namespace Monitor
{
		class MsgCREU02
		{
			public:
					MsgCREU02();
					~MsgCREU02(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
			private:
					SmartData sd;

			private:
					static MsgCREU02*	m_pMsgCREU02;

			public:
					static  MsgCREU02*  getInstance(void);

			public:

					ByteSeq HandleMessage(string myCraneNO,const ByteSeq& ParamBuffer);

					//param1:data							字节流
					//param2:start4BytesPos		起始转换的位置（4字节一组，从0开始编号）
					//param3:countShift				需要转换的DINT型数量
					ByteSeq HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift);




		
		};
}

#endif
