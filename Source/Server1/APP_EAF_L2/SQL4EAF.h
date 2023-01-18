#pragma once
#ifndef _SQL4EAF_
#define _SQL4EAF_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"
#include "EAFPlanInfoDetail.h"
#include "EAFPlanInfoMain.h"


namespace Monitor
{
	class SQL4EAF
	{
	public:
		SQL4EAF(void);
		~SQL4EAF(void);

		//除了心跳电文不插入表外，其它的下发给行车的指令电文存入数据库
		static bool InsEAFL2PlanMain(SmartData sd);

		static bool InsEAFL2PlanDetailSingle(string pono,			//制造命令号
																				string basketID,	//料篮号
																				string pitNO,			//坑位号
																				long layNO,			//层好
																				string scrID,			//废钢ID
																				long scrWeight,	//废钢量
																				string layValid,     //层配方合法标志 1-合法  2-非法
																				string status);			//装车状态 （1-未开始 2-已启动 3-已完成）

		static bool SelEAFPlanInfoMain(string pono, EAFPlanInfoMain& planInfoMain);
		static bool SelEAFPlanInfoDetail(string pono, vector<EAFPlanInfoDetail>& vecEAFPlanInfoDetail);
		static bool SelEAFPlanInfoDetailByDetailID(long planDetailID, EAFPlanInfoDetail& planInfoDetail);

		static bool UpdatePlanMain(string pono, 
														string htno, 
														string recipeType, 
														string steelGrade, 
														string tapTime, 
														string planSrc);

		static bool SelMainPlanInfo(string planNO, string& recipeType);

		static bool SelDetailPlanInfo(string planNO, 
															long planDetailID, 
															string& status,
															string& layValid);
																	
		static bool UpdCarNOInPlanDetail(string planNO, 
																		long planDetailID, 
																		string carNO);

		static bool SelCarPlanBand(string planNO, 
														long planDetailID, 
														string& enterFlag, 
														string& orderFlag );

		static bool InsCarPlanBand(string carNO, 
														string carType, 
														string workType, 
														string planNO, 
														string planSrc, 
														long planDetailID, 
														string enterFlag, 
														string orderFlag,
														iDA::DateTime bandTime );

		static bool UpdCarPlanBand(string carNO, 
															string planNO, 
															long planDetailID );

		static bool DelCarPlanBandByDetailID(long detailID);

		static bool UpdDetailInvalidByDetailID(long detailID);

		static bool UpdPlanDetailByDetailID(long detailID, string scrID, long scrWeight);

		static bool UpdPlanDetailInvalidByDetailID(long detailID);

		static bool UpdPlanDetailStatusByDetailID(long detailID, string stauts);

		static bool SelOperID4DL(string& operID);

		//20220708
		static bool DelEAFPlanDetailByID(long detailID);

		//20220817 zhangyuhong add
		static bool UpdEAFPlanDetailMatInfo(string pono, 
																			long detailID, 
																			string gridNO, 
																			string matCode, 
																			string compCode, 
																			long matWgt);

		static bool UpdEAFPlanDetailSclWgt(string operID, long sclWgt);

		static bool SelGridMatCompCraneWgt(string operID, 
																				string& gridNO,
																				string& matCode, 
																				string& compCode, 
																				long& craneWgt);

		static bool SelPlanNOByOperID(string operID, string& planNO, long& detailID);

		static bool UpdEAFPlanDetailStatus(long planDetailID, string status);

		
	};
}

#endif

