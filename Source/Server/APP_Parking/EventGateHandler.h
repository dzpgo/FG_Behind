/*----------------------------------------------------------------------------------------
处理来自道闸系统的事件通知：
1. 道闸扫描到车牌发送通知
2. 道闸抬杆通知

------------------------------------------------------------------------------------------*/

#pragma once
#ifndef _EventGateHandler_
#define _EventGateHandler_

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
	class EventGateHandler
	{
	public:
		EventGateHandler(void);
		~EventGateHandler(void);
		
		void CarArriveGateHandler(string strValue, string logFileName);

		void CarEnterGateHandler(string strValue, string logFileName);

		const static string EXTER_SYSTEM_EAF;//卸料
		const static string EXTER_SYSTEM_BOF;//装车

		const static long MPE_WGT;

	private:

		string GetArriveStatusByWorkType(string workType);
		 
		void GetFromToPlaceByWorkType(string workType, string gridNO, string parkingNO, string& fromPlace, string& toPlace);

		bool EVTagSnd(string tagName, string tagValue);

		string workTypeConvert(string workType);

		



	};


}
#endif