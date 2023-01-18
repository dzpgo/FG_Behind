/*********************************************************************
 *		
 *  文      件:    MsgEU01.h   		
 *
 *
*********************************************************************/

#pragma once
#ifndef _MsgEU01_
#define _MsgEU01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"
#include "SQL4EAF.h"

#include "EAFPlanInfoDetail.h"
#include "EAFPlanInfoMain.h"

namespace Monitor
{
		class MsgEU01
		{
			public:
					MsgEU01( );
					~MsgEU01(void);
			private:
					string msgId;
					bool readSmartDataSuccessed;
					bool writeToTagSystemTapper;
			private:
					SmartData sd;

			private:
					static MsgEU01*	m_pMsgEU01;

			public:
					static  MsgEU01*  getInstance(void);

			public:

					ByteSeq HandleMessage(const ByteSeq& ParamBuffer, string msgIDInTrans);

			private:
					
					void HandleDataIntoDB(SmartData sd);

					void HandlePlanDetailDel(EAFPlanInfoDetail planInfoDetail);

					long Str2Num(string strNum);

					void HandleSDVecPlanDetail(string pono, 
																		string basketID, 
																		string pitNO, 
																		long layNO, 
																		string scrID, 
																		long scrWeight, 
																		vector<EAFPlanInfoDetail> vecPlanInfoDetail, 
																		map<long, bool>& mapDetailID);

					//把vecPlanInfoDetail中的detailID 插入到map中,  初始设置成 true，当比对sd数据的时候,  如果sd中无, map中有, 则认为此detailID无效了，设置value=false
					map<long, bool> Vec2Map1(vector<EAFPlanInfoDetail>  vecPlanInfoDetail);//map格式： <detailID， true/false>  如<1313， true>
					map<long, EAFPlanInfoDetail> Vec2Map2(vector<EAFPlanInfoDetail>  vecPlanInfoDetail);//map格式： <detailID， EAFPlanInfoDetail>  如<1313， EAFPlanInfoDetail>

					void HandleMapDetailID(map<long, bool> mapDetailID, map<long, EAFPlanInfoDetail> mapPlanInfoDetail);

					void InsEAFL2PlanDetail(SmartData sd);

					
		
		};
}

#endif
