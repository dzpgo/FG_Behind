/*********************************************************************
 *		
 *  ��      ��:    MsgCREU01.h   		
 *
 *
 *  ������
 *        ��MsgCREU01 Ϊ������
 *        �����������г�PLC�������г�״̬����
 *		   ���������ݶ���μ� �г�PLC��UACSͨѶ�ӿ�
 *		   ���������ΪHandleMessage  ���յĲ���Ϊ�������ݵ�byteSeq
 *  �汾��ʷ		
 *      2017��04�½���
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

			//2017.9.18  zhangyuhong add  �ߵ��ֽ�ת��
			private:
					//param1:data							�ֽ���
					//param2:start4BytesPos		��ʼת����λ�ã�4�ֽ�һ�飬��0��ʼ��ţ�
					//param3:countShift				��Ҫת����DINT������
					ByteSeq HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift);

					//��ȡplc��craneNO��ʵ��craneNO���չ�ϵ
					string GetRealCraneNO(int PlcCraneNO);

		
		};
}

#endif
