/*********************************************************************
 *		
 *  文      件:    MsgEUCR02.h   		
 *
 *
 *  概述：
 *        ：MsgEUCR02 为单例类
 *        ：负责将一条完整的行车短命令下达到行车PLC，行车短命令包括 模式切换、停车、紧停、复位等
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为SendOutMessage  接收的参数为电文内容的一个行车短命令对象
 *  版本历史		
 *      2017年04月建立
*********************************************************************/

#pragma once
#ifndef _MsgEUCR02_
#define _MsgEUCR02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include <iXcomTCP2.h>

#include "DataAccess.h"

#include "CranePLCShortCmdBase.h"

namespace Monitor
{
		class MsgEUCR02
		{
			public:
					MsgEUCR02();
					~MsgEUCR02(void);
			private:
					string msgId;

			private:
					static MsgEUCR02*	m_pMsgEUCR02;

			public:
					static  MsgEUCR02*  getInstance(void);

			public:

					bool SendOutMessage(CranePLCShortCmdBase cranePLCShortCmdBase);


			
		};
}

#endif
