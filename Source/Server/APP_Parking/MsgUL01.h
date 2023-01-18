
//激光扫描启动电文MsgUL01
#pragma once
#ifndef _MsgUL01_
#define _MsgUL01_

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
	class MsgUL01
	{
	public:
		MsgUL01(void);
		~MsgUL01(void);
		MsgUL01(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //电文号
	};
}
#endif