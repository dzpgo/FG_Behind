/*----------------------------------------------------------------------------------------
处理来自PARKING系统的事件通知：
1. 车辆到达停车位  ：车类型 车号 停车位号
2. 车辆离开停车位  ： 车类型 车号 停车位号

------------------------------------------------------------------------------------------*/

#pragma once
#ifndef _EventParkingHandler_
#define _EventParkingHandler_

#include <map>
#include <vector>
#include <tag/Tag.h>
#include <utility/StringHelper.h>
#include <tag/Tag.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
//#include "DealData.h"
#include "OrderDataBase.h"
#include "CarPlanBandInfo.h"
#include "OrderQueueBase.h"
#include "SQL4Order.h"
//#include <CLTS.h>

namespace Monitor
{
	typedef map<long, OrderDataBase> MapOrderDataBase;

	//针对eaf计划设计的取料map类型 map<序号, vectro<料格号, 物料代码, 取料量>>
	typedef map<long, vector<string> > MapGridMatWgtEAF;

	//针对bof计划设计的取料map类型 map<放料顺序号, vectro<料格号, 物料代码, 取料量>>
	typedef map<long, vector<string> > MapGridMatWgtBOF;


	class EventParkingHandler
	{
	public:
			EventParkingHandler(void);
			~EventParkingHandler(void);
			//
			const static string EXTER_SYSTEM_EAF;
			const static string EXTER_SYSTEM_BOF;

			const static long MPE_WGT;	

			void OrderCreateReqForL3EAFL2(string strValue, string logFileName);

		private:

			//bool OrderCreateL3(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, MapOrderDataBase& mapOrderData);
			bool OrderCreateL3(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, OrderDataBase& orderDataBaseL3);

			bool OrderCreateEAFMap(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, MapOrderDataBase& mapOrderData);
			bool OrderCreateEAF(CarPlanBandInfo carPlanBandInfoBase,  string parkingNO, OrderDataBase& orderDataBaseEAF);

			bool GetScrapCodeReqWgt(CarPlanBandInfo carPlanBandInfoBase, string& locCode, string& scrapCode, string& compCode, long& reqWgt);

			bool MakeSingleOrderEAF(CarPlanBandInfo  carPlanBandInfoBase, 
															long orderGroupNO, 
															string parkingNO, 
															long exeSeq, 
															string gridNO, 
															string matCode, 
															long calWgt, 
															OrderDataBase& orderDataBaseEAF);

			string GetOrderType(string planSrc, string workType);

			bool GetOrderQueue(OrderDataBase orderData, OrderQueueBase& orderQueue);

			bool GetRecCraneNO(OrderDataBase orderData, string& recCraneNO);

			//根据跨长 几等分 实际X坐标 来确定对应的是第几等分  按照X从小到达排序
			long GetXPosSeqInBayDivide(long bayLength, long divideNum, long xPos);

			//根据指令类型获取料格编号
			string GetGridNOByOrderType(OrderDataBase orderData);


		
	};

	
}
#endif