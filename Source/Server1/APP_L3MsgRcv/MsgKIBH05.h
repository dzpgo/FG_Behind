/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgKIBH05.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgKIBH05_
#define _MsgKIBH05_

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
		class MsgKIBH05
		{
			public:
					MsgKIBH05( );
					~MsgKIBH05(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgKIBH05*	m_pMsgKIBH05;

			public:
					static  MsgKIBH05*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd);
					void L3ZCWgtNotify(SmartData sd);
					bool EVTagSnd(string tagName, string tagValue);

					string GetRgvMatInfo(SmartData sd);
		
		};
}

#endif
