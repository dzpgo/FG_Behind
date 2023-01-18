/*********************************************************************
 *		
 *  文      件:    MsgRRWW01.h   		
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
																string& rgvNo,//车号 A01
																string& parkNo,//停车位号 B01
																long& loadFlag,//空载重载标识 0-空 1-重 2-卡料
																long& troughDir);//车头方向 1-车头朝X大方向  0-车头朝X小方向

					bool EVTagSnd(string tagName, string tagValue);


		
		};
}

#endif
