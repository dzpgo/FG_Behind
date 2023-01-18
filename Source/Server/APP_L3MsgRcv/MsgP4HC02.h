/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgP4HC02.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgP4HC02_
#define _MsgP4HC02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "SQL4L3.h"

namespace Monitor
{
		class MsgP4HC02
		{
			public:
					MsgP4HC02( );
					~MsgP4HC02(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgP4HC02*	m_pMsgP4HC02;

			public:
					static  MsgP4HC02*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd, string logFileName);

					void DelMatCodeCompCode(string matCode, vector<string> vecCompCode, string matCodeRelate);
					void InsMatCodeCompCode(string exterSystem, string matCode, vector<string> vecCompCode, string matCodeRelate);
					

					


		
		};
}

#endif
