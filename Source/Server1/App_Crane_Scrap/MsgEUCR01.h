/*********************************************************************
 *		
 *  文      件:    MsgEUCR01.h   		
 *
 *
 *  概述：
 *        ：MsgEUCR01 为单例类
 *        ：负责将一条完整的行车走行指令下达到行车PLC
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为SendOutMessage  接收的参数为电文内容的一个完整的行车走行指令对象
 *  版本历史		
 *      2017年04月建立
*********************************************************************/

#pragma once
#ifndef _MsgEUCR01_
#define _MsgEUCR01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include <iXcomTCP2.h>

#include "DataAccess.h"

#include "CranePLCOrderBase.h"
#include "Adapter_UACS_CRANE_MOVEORDER_MSG.h"

#include "ACTION_COMMON_FUNCTION.h"

#include "MultiLine_MDProxy_TimerWatchInterfaceI.h"
#include "imultilink/MLAPI.h"

#pragma comment(lib, "pace.lib")
#pragma comment(lib, "iMLLib.lib")

namespace Monitor
{
		class MsgEUCR01
		{
			public:
					MsgEUCR01();
					~MsgEUCR01(void);
			private:
					string msgId;

			private:
					static MsgEUCR01*	m_pMsgEUCR01;

			public:
					static  MsgEUCR01*  getInstance(void);

			public:

					bool SendOutMessage(CranePLCOrderBase cranePLCOrderBase);
					bool SendOutMessage_III(CranePLCOrderBase cranePLCOrderBase);//废钢1号配料间

			private:
					
					int getLineNO(string craneNO); 

			
		};
}

#endif
