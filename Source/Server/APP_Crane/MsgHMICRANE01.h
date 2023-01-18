/*********************************************************************
 *		
 *  文      件:    MsgHMICRANE01.h   		
 *
 *
 *  概述：
 *        ：MsgHMICRANE01 为单例类
 *        ：接收由画面发出的短指令
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为HandleMessage  接收的参数为电文内容的String
 *  版本历史		
 *      2017年04月建立
 *      内部电文   电文号HMICRANE01
 *      电文内容   行车号，操作码
*********************************************************************/

#pragma once
#ifndef _MsgHMICRANE01_
#define _MsgHMICRANE01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CranePLCShortCmdBase.h"

#include "CraneMonitor.h"


namespace Monitor
{
		class MsgHMICRANE01
		{
			public:
					MsgHMICRANE01();
					~MsgHMICRANE01(void);
		

			private:
					static MsgHMICRANE01*	m_pMsgHMICRANE01;

			public:
					static  MsgHMICRANE01*  getInstance(void);

			public:

					bool HandleMessage(string myCraneNO,string messageData);




		
		};
}

#endif
