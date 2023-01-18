
//车辆准许离开通知电文 MsgWG02
#pragma once
#ifndef _MsgWG02_
#define _MsgWG02_

#include <map>
#include <vector>
#include <tag/Tag.h>
#include <utility/StringHelper.h>
#include <tag/Tag.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
//#include <CLTS.h>

namespace Monitor
{
	class MsgWG02
	{
	public:
		MsgWG02(void);
		~MsgWG02(void);
		MsgWG02(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //电文号
	};
}
#endif