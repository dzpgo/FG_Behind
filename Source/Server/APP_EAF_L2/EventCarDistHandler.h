/*----------------------------------------------------------------------------------------
处理来自画面的EAF计划分配车辆号的事件通知：
1. 人工在WMS画面上进行车辆分配操作完毕后发送EVtag点给本模块

------------------------------------------------------------------------------------------*/

#pragma once
#ifndef _EventCarDistHandler_
#define _EventCarDistHandler_

#include <map>
#include <vector>
#include <tag/Tag.h>
#include <utility/StringHelper.h>
#include <tag/Tag.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
//#include "DealData.h"
#include "SQL4EAF.h"

namespace Monitor
{
	class EventCarDistHandler
	{
	public:
		EventCarDistHandler(void);
		~EventCarDistHandler(void);

		void CarDistHandler(string strValue, string logFileName);

		void CarArriveHandler(string strValue, string logFileName);

		const static string EXTER_SYSTEM_EAF;//卸料
		const static string EXTER_SYSTEM_BOF;//装车

		const static long MPE_WGT;

	private:

		string GetMsgUE02Text(EAFPlanInfoMain planInfoMain, EAFPlanInfoDetail planInfoDetail);

		string GetStrMsg(vector<string> vecStr, string splitFlag);





	};


}
#endif