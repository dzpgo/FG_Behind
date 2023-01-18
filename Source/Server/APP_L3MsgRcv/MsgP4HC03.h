/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgP4HC03.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgP4HC03_
#define _MsgP4HC03_

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
		class MsgP4HC03
		{
			public:
					MsgP4HC03( );
					~MsgP4HC03(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgP4HC03*	m_pMsgP4HC03;

			public:
					static  MsgP4HC03*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd);
					

					


		
		};
}

#endif
