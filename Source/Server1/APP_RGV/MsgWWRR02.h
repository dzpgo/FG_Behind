//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "DealData.h"

class MsgWWRR02
{
	
	private:
		string m_strMsgId;

	public:
		MsgWWRR02(string msgid);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
