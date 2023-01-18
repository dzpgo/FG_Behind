/*********************************************************************
 *		
 *  文      件:    MsgUS04.h   		
 *
 *
 *  概述：
 *        ：MsgUS04 为单例类
 *        ：行车走行路径上的安全门通知电文
 *		   ：电文数据定义参见 行车PLC与UACS通讯接口
 *		   ：程序入口为SendOutMessage  接收的参数为电文内容的一个完整的行车走行指令对象
 *  版本历史		
 *      2017年04月建立
*********************************************************************/

#pragma once
#ifndef _MsgUS04_
#define _MsgUS04_

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
		class MsgUS04
		{
			public:
					MsgUS04();
					~MsgUS04(void);
			private:
					string msgId;

			private:
					static MsgUS04*	m_pMsgUS04;

			public:
					static  MsgUS04*  getInstance(void);

			public:

					bool SendOutMessage(vector <long> vecSafeDoorID );


			
		};
}

#endif
