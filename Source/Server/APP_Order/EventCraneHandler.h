/*----------------------------------------------------------------------------------------
��������PARKINGϵͳ���¼�֪ͨ��
1. ��������ͣ��λ  �������� ���� ͣ��λ��
2. �����뿪ͣ��λ  �� ������ ���� ͣ��λ��

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

	//���eaf�ƻ���Ƶ�ȡ��map���� map<���, vectro<�ϸ��, ���ϴ���, ȡ����>>
	typedef map<long, vector<string> > MapGridMatWgtEAF;

	//���bof�ƻ���Ƶ�ȡ��map���� map<����˳���, vectro<�ϸ��, ���ϴ���, ȡ����>>
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