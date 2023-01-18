/*********************************************************************
 *		
 *  文      件:    MsgCREU01.h   		
 *
 *
 *  概述：
 *        ：MsgCREU01 为单例类
 *        ：接收所有行车PLC发来的行车状态数据
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为HandleMessage  接收的参数为电文内容的byteSeq
 *  版本历史		
 *      2017年04月建立
*********************************************************************/

#pragma once
#ifndef _MsgCREU01_
#define _MsgCREU01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CranePLCStatusBase.h"
#include "CraneMonitor.h"

#include "CranePLCStatusStorm.h"

#include "ACTION_COMMON_FUNCTION.h"

namespace Monitor
{
		class MsgCREU01
		{
			public:
					MsgCREU01();
					~MsgCREU01(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;

			private:
					static MsgCREU01*	m_pMsgCREU01;

			public:
					static  MsgCREU01*  getInstance(void);

			public:

					ByteSeq HandleMessage(string myCraneNO, 
																	string cranePLCStatusTopicName, 
																	const ByteSeq& ParamBuffer, 
																	vector<long>& vecOrderIDAlarmCode, 
																	CranePLCStatusBase& cranePLCStatus_Last);

			//2017.9.18  zhangyuhong add  高低字节转换
			private:
					//param1:data							字节流
					//param2:start4BytesPos		起始转换的位置（4字节一组，从0开始编号）
					//param3:countShift				需要转换的DINT型数量
					ByteSeq HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift);

					//获取plc中craneNO和实际craneNO对照关系
					string GetRealCraneNO(int PlcCraneNO);

		
		};
}

#endif
