/*********************************************************************
 *		
 *  文      件:    MsgHMICRANE02.h   		
 *
 *
 *  概述：
 *        ：MsgHMICRANE02 为单例类
 *        ：接收由画面发出的行车走行指令
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为HandleMessage  接收的参数为电文内容的String
 *  版本历史		
 *      2017年04月建立
 *      内部电文   电文号HMICRANE02
 *      电文内容   与行车指令电文相同
*********************************************************************/

#pragma once
#ifndef _MsgHMICRANE02_
#define _MsgHMICRANE02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CranePLCOrderBase.h"

#include "CraneMonitor.h"



namespace Monitor
{
		class MsgHMICRANE02
		{
			public:
					MsgHMICRANE02();
					~MsgHMICRANE02(void);
		

			private:
					static MsgHMICRANE02*	m_pMsgHMICRANE02;

			public:
					static  MsgHMICRANE02*  getInstance(void);

			public:

					bool HandleMessage(string myCraneNO,string messageData);




		
		};
}

#endif
