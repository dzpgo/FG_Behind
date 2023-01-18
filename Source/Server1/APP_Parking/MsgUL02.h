
//激光扫描启动电文MsgUL02
#pragma once
#ifndef _MsgUL02_
#define _MsgUL02_

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
	class MsgUL02
	{
	public:
		MsgUL02(void);
		~MsgUL02(void);
		MsgUL02(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //电文号
	};
}
#endif