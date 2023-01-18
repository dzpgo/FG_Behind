/*----------------------------------------------------------------------------------------
处理来自PARKING系统的事件通知：
1. 车辆到达停车位  ：车类型 车号 停车位号
2. 车辆离开停车位  ： 车类型 车号 停车位号

------------------------------------------------------------------------------------------*/

#pragma once
#ifndef _EventCraneHandler_
#define _EventCraneHandler_

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


	class EventCraneHandler
	{
	public:
			EventCraneHandler(void);
			~EventCraneHandler(void);
			//
			

			void OrderCmdStatusRcv(string strValue, string logFileName);

		private:

			string GetStrMsg(vector<string> vecStr, string splitFlag);

			bool EVTagSnd(string tagName, string tagValue);

			


		
	};

	
}
#endif