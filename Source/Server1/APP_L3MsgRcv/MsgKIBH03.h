/*********************************************************************
 *		
 *  нд      ╪Ч:    MsgKIBH03.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgKIBH03_
#define _MsgKIBH03_

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
		class MsgKIBH03
		{
			public:
					MsgKIBH03( );
					~MsgKIBH03(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgKIBH03*	m_pMsgKIBH03;

			public:
					static  MsgKIBH03*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd);
					

					


		
		};
}

#endif
