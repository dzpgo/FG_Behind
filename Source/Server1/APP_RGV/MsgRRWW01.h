/*********************************************************************
 *		
 *  ��      ��:    MsgRRWW01.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgRRWW01_
#define _MsgRRWW01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include <json/json.h>
#include "DataAccess.h"

namespace Monitor
{
		class MsgRRWW01
		{
			public:
					MsgRRWW01( );
					~MsgRRWW01(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;

			private:
					static MsgRRWW01*	m_pMsgRRWW01;

			public:
					static  MsgRRWW01*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer);

			private:
					bool isJsonStr(const char *jsoncontent);

					bool RRWW01Convert(string jsonStr, 
																string& rgvNo,//���� A01
																string& parkNo,//ͣ��λ�� B01
																long& loadFlag,//�������ر�ʶ 0-�� 1-�� 2-����
																long& troughDir);//��ͷ���� 1-��ͷ��X����  0-��ͷ��XС����

					bool EVTagSnd(string tagName, string tagValue);


		
		};
}

#endif
