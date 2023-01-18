#pragma once
#ifndef _MsgHCP411_
#define _MsgHCP411_

#include <map>
#include <vector>
#include <tag/Tag.h>
#include <utility/StringHelper.h>
#include <tag/Tag.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
#include "DealData.h"
//#include <CLTS.h>

namespace Monitor
{
	class MsgHCP411
	{
	public:
		MsgHCP411(void);
		~MsgHCP411(void);
		MsgHCP411(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //µçÎÄºÅ

	private:
		string GetPlanStatus(string workTye, string workStatus);
	};
}
#endif