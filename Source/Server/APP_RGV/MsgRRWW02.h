/*********************************************************************
 *		
 *  ÎÄ      ¼þ:    MsgRRWW02.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgRRWW02_
#define _MsgRRWW02_

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
		class MsgRRWW02
		{
			public:
					MsgRRWW02( );
					~MsgRRWW02(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;

			private:
					static MsgRRWW02*	m_pMsgRRWW02;

			public:
					static  MsgRRWW02*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer);

			private:
				bool isJsonStr(const char *jsoncontent);

				bool RRWW02Convert(string jsonStr, 
															map<string, long>& mapRGVLocking);//³µºÅ A01

				bool EVTagSnd(string tagName, string tagValue);

		
		};
}

#endif
