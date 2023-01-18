/*********************************************************************
 *		
 *  文      件:    MsgP4HC11.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgP4HC11_
#define _MsgP4HC11_

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
		
		static const string SCRAP_YARD_NAME = "ZSOO";//202220811 和L3所测确定

		class MsgP4HC11
		{
			public:
					MsgP4HC11( );
					~MsgP4HC11(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgP4HC11*	m_pMsgP4HC11;

			public:
					static  MsgP4HC11*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd);

					//assignFlag：指定标记  0：不指定workType  1：指定workType
					void BandCarPlanInfo(SmartData sd, L3PlanInfo planInfoDB, string assignFlag, string workType);

					string GetL3PlanType(SmartData sd);

					bool SrcInfoNotChange(L3PlanInfo planInfo, SmartData sd);

					bool DstInfoNotChange(L3PlanInfo planInfo, SmartData sd);

					bool CarNONotChange(L3PlanInfo planInfo, SmartData sd);

					void CheckZCSrcInfo(L3PlanInfo planInfo, SmartData sd, string& planValid);

					void CheckXLDstInfo(L3PlanInfo planInfo, SmartData sd, string& planValid);

					void CheckWorkProg(L3PlanInfo planInfo, string workType, string& planValid);

					//L3建议归堆启动通知:采用EVtag点通知
					void CanXLStartNotify(SmartData sd);

					bool EVTagSnd(string tagName, string tagValue);


					

					


		
		};
}

#endif
