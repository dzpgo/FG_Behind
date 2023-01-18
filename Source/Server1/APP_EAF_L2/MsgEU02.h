/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgEU02.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgEU02_
#define _MsgEU02_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"

namespace Monitor
{
		class MsgEU02
		{
			public:
					MsgEU02( );
					~MsgEU02(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;

			private:
					static MsgEU02*	m_pMsgEU02;

			public:
					static  MsgEU02*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer);

			private:
					

					


		
		};
}

#endif
