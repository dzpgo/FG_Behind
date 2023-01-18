/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgKIBH02.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgKIBH02_
#define _MsgKIBH02_

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
		class MsgKIBH02
		{
			public:
					MsgKIBH02( );
					~MsgKIBH02(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgKIBH02*	m_pMsgKIBH02;

			public:
					static  MsgKIBH02*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd, string logFileName);

					void DelMatCodeCompCode(string matCode, vector<string> vecCompCode, string matCodeRelate);
					void InsMatCodeCompCode(string exterSystem, string matCode, vector<string> vecCompCode, string matCodeRelate);
					

					


		
		};
}

#endif
