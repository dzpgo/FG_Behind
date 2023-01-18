#pragma once
#ifndef _MsgHCP401_
#define _MsgHCP401_

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
	class MsgHCP401
	{
	public:
		MsgHCP401(void);
		~MsgHCP401(void);
		MsgHCP401(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //µçÎÄºÅ
	};
}
#endif