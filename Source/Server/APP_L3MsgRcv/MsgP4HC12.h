/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgP4HC12.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgP4HC12_
#define _MsgP4HC12_

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
		class MsgP4HC12
		{
			public:
					MsgP4HC12( );
					~MsgP4HC12(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgP4HC12*	m_pMsgP4HC12;

			public:
					static  MsgP4HC12*  getInstance(void);

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
