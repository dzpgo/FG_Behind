#pragma once
#ifndef _MsgHCP412_
#define _MsgHCP412_

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
	class MsgHCP412
	{
	public:
		MsgHCP412(void);
		~MsgHCP412(void);
		MsgHCP412(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //µçÎÄºÅ
	};
}
#endif