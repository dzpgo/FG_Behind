/*----------------------------------------------------------------------------------------
处理来自道闸系统的事件通知：
1. 道闸扫描到车牌发送通知
2. 道闸抬杆通知

------------------------------------------------------------------------------------------*/

#pragma once
#ifndef _EventOrderHandler_
#define _EventOrderHandler_

#include <map>
#include <vector>
#include <tag/Tag.h>
#include <utility/StringHelper.h>
#include <tag/Tag.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
//#include "DealData.h"
#include "SQL4Parking.h"
#include "CarPlanBandInfo.h"

namespace Monitor
{
	class EventOrderHandler
	{
	public:
		EventOrderHandler(void);
		~EventOrderHandler(void);

		void OrderParkingWorkStatus(string strValue, string logFileName);

	private:

		bool EVTagSnd(string tagName, string tagValue);





	};


}
#endif