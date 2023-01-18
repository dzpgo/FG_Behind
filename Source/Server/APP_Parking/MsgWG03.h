
//	料格启动作业通知电文 MsgWG03
#pragma once
#ifndef _MsgWG03_
#define _MsgWG03_

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
	class MsgWG03
	{
	public:
		MsgWG03(void);
		~MsgWG03(void);
		MsgWG03(string msgID);

		void HandleMessage(const string strValue, const string logFileName);

	public:
		string m_strMsgId;            //电文号
	};
}
#endif