/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgBU01.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgBU01_
#define _MsgBU01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "SQL4BOF.h"

namespace Monitor
{
		class MsgBU01
		{
			public:
					MsgBU01( );
					~MsgBU01(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;

			private:
					static MsgBU01*	m_pMsgBU01;

			public:
					static  MsgBU01*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer);

			private:

					void HandleDataIntoDB(SmartData sd);

					bool matDetailSame2SD(map<string, long> matDetail, SmartData sd);
					

					


		
		};
}

#endif
