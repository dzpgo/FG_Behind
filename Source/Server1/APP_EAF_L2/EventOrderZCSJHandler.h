/*----------------------------------------------------------------------------------------
�������Ի����EAF�ƻ����䳵���ŵ��¼�֪ͨ��
1. �˹���WMS�����Ͻ��г������������Ϻ���EVtag�����ģ��

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

		const static string EXTER_SYSTEM_EAF;//ж��
		const static string EXTER_SYSTEM_BOF;//װ��

		const static long MPE_WGT;

	private:

		string GetStrMsg(vector<string> vecStr, string splitFlag);

		bool EVTagSnd(string tagName, string tagValue);





	};


}
#endif