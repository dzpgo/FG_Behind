#pragma once
#ifndef _MsgHCP421_
#define _MsgHCP421_

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
	class MsgHCP421
	{
	public:
		MsgHCP421(void);
		~MsgHCP421(void);
		MsgHCP421(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //µçÎÄºÅ
	};
}
#endif