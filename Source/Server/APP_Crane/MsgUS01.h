/*********************************************************************
 *		
 *  文      件:    MsgUS01.h   		
 *
 *
 *  概述：
 *        ：MsgUS01 为单例类
 *        ：负责将一条完整的行车走行指令下达到行车PLC
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为SendOutMessage  接收的参数为电文内容的一个完整的行车走行指令对象
 *  版本历史		
 *      2017年04月建立
*********************************************************************/

#pragma once
#ifndef _MsgUS01_
#define _MsgUS01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include <iXcomTCP2.h>

#include "DataAccess.h"


namespace Monitor
{
		class MsgUS01
		{
			public:
					MsgUS01();
					~MsgUS01(void);
			private:
					string msgId;

			private:
					static MsgUS01*	m_pMsgUS01;

			public:
					static  MsgUS01*  getInstance(void);

			public:

					bool SendOutMessage(vector <string> vecLineName , string craneNO);


			
		};
}

#endif
