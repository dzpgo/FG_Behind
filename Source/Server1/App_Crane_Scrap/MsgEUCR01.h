/*********************************************************************
 *		
 *  ��      ��:    MsgEUCR01.h   		
 *
 *
 *  ������
 *        ��MsgEUCR01 Ϊ������
 *        ������һ���������г�����ָ���´ﵽ�г�PLC
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪSendOutMessage  ���յĲ���Ϊ�������ݵ�һ���������г�����ָ�����
 *  �汾��ʷ		
 *      2017��04�½���
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
					bool SendOutMessage_III(CranePLCOrderBase cranePLCOrderBase);//�ϸ�1�����ϼ�

			private:
					
					int getLineNO(string craneNO); 

			
		};
}

#endif
