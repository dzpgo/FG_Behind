/*----------------------------------------------------------------------------------------
�������Ի����EAF�ƻ����䳵���ŵ��¼�֪ͨ��
1. �˹���WMS�����Ͻ��г������������Ϻ���EVtag�����ģ��

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

		const static string EXTER_SYSTEM_EAF;//ж��
		const static string EXTER_SYSTEM_BOF;//װ��

		const static long MPE_WGT;

	private:

		string GetMsgUE02Text(EAFPlanInfoMain planInfoMain, EAFPlanInfoDetail planInfoDetail);

		string GetStrMsg(vector<string> vecStr, string splitFlag);





	};


}
#endif