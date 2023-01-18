/*********************************************************************
 *		
 *  ��      ��:    MsgKIBH04.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgKIBH04_
#define _MsgKIBH04_

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
		
		static const string SCRAP_YARD_NAME = "ZSOO";//202220811 ��L3����ȷ��

		class MsgKIBH04
		{
			public:
					MsgKIBH04( );
					~MsgKIBH04(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;
					SmartData sdTrim;

			private:
					static MsgKIBH04*	m_pMsgKIBH04;

			public:
					static  MsgKIBH04*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, const string& LogFileName);

			private:

					void HandleDataIntoDB(SmartData sd);

					//assignFlag��ָ�����  0����ָ��workType  1��ָ��workType
					void BandCarPlanInfo(SmartData sd, L3PlanInfo planInfoDB, string assignFlag, string workType);

					string GetL3PlanType(SmartData sd);

					bool SrcInfoNotChange(L3PlanInfo planInfo, SmartData sd);

					bool DstInfoNotChange(L3PlanInfo planInfo, SmartData sd);

					bool CarNONotChange(L3PlanInfo planInfo, SmartData sd);

					void CheckZCSrcInfo(L3PlanInfo planInfo, SmartData sd, string& planValid);

					void CheckXLDstInfo(L3PlanInfo planInfo, SmartData sd, string& planValid);

					void CheckWorkProg(L3PlanInfo planInfo, string workType, string& planValid);

					//L3����������֪ͨ:����EVtag��֪ͨ
					void CanXLStartNotify(SmartData sd);

					bool EVTagSnd(string tagName, string tagValue);


					

					


		
		};
}

#endif
