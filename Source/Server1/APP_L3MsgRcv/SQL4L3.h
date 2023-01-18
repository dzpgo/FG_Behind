#pragma once
#ifndef _SQL4L3_
#define _SQL4L3_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "L3PlanInfo.h"


namespace Monitor
{
	class SQL4L3
	{
	public:
		SQL4L3(void);
		~SQL4L3(void);

//============MsgKIBH01====================================

		static bool DelMatInfo(string matCode);

		static bool InsertMatInfo(string baseResource, string matCode, string matCName, string matType);

		static bool DelMatOutInfo(string planNO);

		static bool InsertMatOutInfo(string operateFlag, string planNO, string bofNO, int count, string matCode_1, int weight_1, string matCode_2, int weight_2, string matCode_3, int weight_3, string matCode_4, int weight_4, string matCode_5, int weight_5, string matCode_6, int weight_6, string matCode_7, int weight_7, string matCode_8, int weight_8, string matCode_9, int weight_9, string matCode_10, int weight_10);


//===========MsgKIBH02=====================================

		static bool DelMatRelationInfo(string matCode, string compCode, string matCodeRelate);

		static bool InsertMatRelationInfo(string exterSystem, string matCode, string compCode, string matCodeRelate);

		static bool UpdateMatCarRelationInfo(string arriveFlag, string hopperNO, string positionNO, string loadFlag);


//===========MsgKIBH03=====================================

		static bool DelMatGridInfo(string stockPlaceCode);

		static bool InsertMatGridInfo(string stockCode, //库区代码
															string stockPlaceCode, //料格代码
															string stockLocCode, //料条/跨跨代码
															long storermAddrMin, //料条/跨起点地址
															long storermAddrMax, //料条跨终点地址
															string matCode, //物料代码
															string compCode, //废钢钢制码
															string startTime);//开始时刻		

		static bool UpdYardMapGridInfo(string gridNO, string matCode, string compCode, int curWt);

		static bool InitYardMapGridInfo(string gridNO);

//===========MsgKIBH04=====================================

		static bool SelL3PlanInfo(string workSeqNO, L3PlanInfo& planInfo );

		static bool DelMatInOutInfo(string workSeqNO);

		static bool InsertMatInOutInfo(SmartData sd, string planType);

		static bool UpdateMatInOutInfo(SmartData sd);

		static bool UpdateMatInOutInfoValid(SmartData sd);	

		static bool UpdL3PlanInfoPlanVlaid(string workSeqNO, string planValid);

		static bool UpdateMatOutInfo_WT(string planNO, string hopperNO, int netWeight);


//===========MsgKIBH05=====================================

		static bool MatWeightInfoExist(string workSeqNO);

		static bool InsertMatWeightTable(SmartData sd);

		static bool InsertMatWeightInfo(SmartData sd);

		static bool InsertMatWeightRGVInfo(SmartData sd);
		static bool InsertMatWeightRGVInfoSingle(string workSeqNO, 
																					string stockPlaceCode, 
																					string matCode, 
																					string compCode, 
																					int wgt);

		static bool UpdateMatWeightInfo(SmartData sd);

		static bool DelMatWeightRGVInfo(string workSeqNO);


		//===========绑定车辆计划表相关操作=====================
		static bool SelCarPlanBandInfoExist(string carNO, 
																		string planNO, 
																		string workType);

		static bool InsCarPlanBandInfo(string carNO, 
																string carType,  
																string workType, 
																string workSeqNO, 
																string planSrc, 
																string enterFlag, 
																string orderFlag, 
																iDA::DateTime bandTime);

		static bool DelCarPlanBandInfo(string carNO, string workSeqNO );

		static bool DelCarPlanBandInfoByWorkType(string carNO, string workSeqNO, string workType );

		static bool SelCarStatus(string carNO, string planNO, string& enterFlag);

		static bool SelCarStatusByWokrType(string carNO, string planNO, string workType, string& enterFlag);





		

	};
}

#endif

