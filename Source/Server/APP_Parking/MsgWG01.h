
//车辆引导目的料格电文 MsgWG01
#pragma once
#ifndef _MsgWG01_
#define _MsgWG01_

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
	class MsgWG01
	{
	public:
		MsgWG01(void);
		~MsgWG01(void);
		MsgWG01(string msgID);

		void HandleMessage(const string strValue);

	public:
		string m_strMsgId;            //电文号
	};
}
#endif