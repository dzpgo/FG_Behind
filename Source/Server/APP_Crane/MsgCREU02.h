/*********************************************************************
 *		
 *  ��      ��:    MsgCREU02.h   		
 *
 *
 *  ������
 *        ��MsgCREU02 Ϊ������
 *        �����������г�PLC�������г����ϱ�������
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪHandleMessage  ���յĲ���Ϊ�������ݵ�byteSeq
 *  �汾��ʷ		
 *      2017��04�½���
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

					//param1:data							�ֽ���
					//param2:start4BytesPos		��ʼת����λ�ã�4�ֽ�һ�飬��0��ʼ��ţ�
					//param3:countShift				��Ҫת����DINT������
					ByteSeq HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift);




		
		};
}

#endif
