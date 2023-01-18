#pragma once
#ifndef _MsgLU01_
#define _MsgLU01_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"
#include "tagUtility.h"
#include <iXcomTCP2.h>
#include <json/json.h>

namespace Monitor
{
	class MsgLU01
	{
	public:
		MsgLU01();
		~MsgLU01(void);

	private:
		string m_strMsgId;
	public:
		string getMsgID();
		void  setMsgID(string theVal);

	private:
		static MsgLU01*	m_pMsgLU01;

	public:
		static  MsgLU01* getInstance(void);

	public:
		//ByteSeq HandleMessage(const SmartData& sd);
		ByteSeq HandleMessage(const SmartData& sd);

	private:
		bool isJsonStr(const char *jsoncontent);
		//json½âÎö
		bool MsgLU01Convert(string jsonStr, SmartData& sdJson);

		bool EVTagSnd(string tagName, string tagValue);
		
	};
}
#endif
