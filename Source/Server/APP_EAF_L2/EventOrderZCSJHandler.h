/*----------------------------------------------------------------------------------------
处理来自画面的EAF计划分配车辆号的事件通知：
1. 人工在WMS画面上进行车辆分配操作完毕后发送EVtag点给本模块

------------------------------------------------------------------------------------------*/

#pragma once
#ifndef _EventOrderZCSJHandler_
#define _EventOrderZCSJHandler_

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
	class EventOrderZCSJHandler
	{
	public:
		EventOrderZCSJHandler(void);
		~EventOrderZCSJHandler(void);

		void OrderZCSJHandler(string strValue, string logFileName);

		void L3WgtHandler(string strValue, string logFileName);

		const static string EXTER_SYSTEM_EAF;//卸料
		const static string EXTER_SYSTEM_BOF;//装车

		const static long MPE_WGT;

	private:

		string GetStrMsg(vector<string> vecStr, string splitFlag);

		bool EVTagSnd(string tagName, string tagValue);





	};


}
#endif