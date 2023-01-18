#pragma once
#ifndef _SQL4BOF_
#define _SQL4BOF_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "DataAccess.h"


namespace Monitor
{
	class SQL4BOF
	{
	public:
		SQL4BOF(void);
		~SQL4BOF(void);

		//�����������Ĳ�������⣬�������·����г���ָ����Ĵ������ݿ�
		static bool InsertBOFL2PlanMain(SmartData sd);

		static bool InsertBOFL2PlanDetail(SmartData sd);	
	
		static bool InsertBOFL2PlanDetailSingle(string steelNO, 
																				string strScrID, 
																				int scrWeight);	

		static bool BOFL2PlanExist(string steelNO, string& planStatus);

		static bool UpdatePlanMain(string steelNO, string planType, string planFlag);

		static bool UpdatePlanDetailPlanValid(string steelNO);

		static bool DelPlanDetail(string steelNO);

		static bool UpdatePlanMainPlanValid(string steelNO, string planType, string planFlag);

		static bool SelectPlanDetailMatWgt(string steelNO, map<string, long>& matDetail);

		static bool SelOperID4LG(string& operID);

	};
}

#endif

