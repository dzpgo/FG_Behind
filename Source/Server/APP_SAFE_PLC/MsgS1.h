/*********************************************************************
 *		
 *  ��      ��:    MsgS1.h   		
 *
 *
 *  ������
 *  �汾��ʷ		
 *      2017��04�½���
*********************************************************************/

#pragma once
#ifndef _MsgS1_
#define _MsgS1_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"
#include "SafePLC4EAFYardBase.h"



namespace Monitor
{
		class MsgS1
		{
			public:
					MsgS1();
					~MsgS1(void);
			private:
					string msgId;
			private:
					SmartData sd;

			private:
					static MsgS1*	m_pMsgS1;

			public:
					static  MsgS1*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, SafePLC4EAFYardBase& safePLC4EAFYard_Last);

					//param1:data							�ֽ���
					//param2:start4BytesPos		��ʼת����λ�ã�4�ֽ�һ�飬��0��ʼ��ţ�
					//param3:countShift				��Ҫת����DINT������
					ByteSeq HighLowByteShift(ByteSeq data, int start4BytesPos , int countShift);

		private:
					
					void UpdSafePLC4EAFYard(SafePLC4EAFYardBase safePLC4EAFYard_Last, SafePLC4EAFYardBase safePLC4EAFYard_Current);

					void UpdSafeValue(string safeID, string lastValue, string currentValue);




		
		};
}

#endif
