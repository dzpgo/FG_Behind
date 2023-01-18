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

//============MsgP4HC01====================================

		static bool DelMatInfo(string matCode);

		static bool InsertMatInfo(string baseResource, string matCode, string matCName, string matType);

//===========MsgP4HC02=====================================

		static bool DelMatRelationInfo(string matCode, string compCode, string matCodeRelate);

		static bool InsertMatRelationInfo(string exterSystem, string matCode, string compCode, string matCodeRelate);


//===========MsgP4HC03=====================================

		static bool DelMatGridInfo(string stockPlaceCode);

		static bool InsertMatGridInfo(string stockCode, //��������
															string stockPlaceCode, //�ϸ����
															string stockLocCode, //����/������
															long storermAddrMin, //����/������ַ
															long storermAddrMax, //�������յ��ַ
															string matCode, //���ϴ���
															string compCode, //�ϸָ�����
															string startTime);//��ʼʱ��		

		static bool UpdYardMapGridInfo(string gridNO, string matCode, string compCode);

		static bool InitYardMapGridInfo(string gridNO);

//===========MsgP4HC11=====================================

		static bool SelL3PlanInfo(string workSeqNO, L3PlanInfo& planInfo );

		static bool DelMatInOutInfo(string workSeqNO);

		static bool InsertMatInOutInfo(SmartData sd, string planType);

		static bool UpdateMatInOutInfo(SmartData sd);

		static bool UpdateMatInOutInfoValid(SmartData sd);	

		static bool UpdL3PlanInfoPlanVlaid(string workSeqNO, string planValid);


//===========MsgP4HC12=====================================

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


		//===========�󶨳����ƻ�����ز���=====================
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

