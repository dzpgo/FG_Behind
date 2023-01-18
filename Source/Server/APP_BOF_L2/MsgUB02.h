//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "DealData.h"

class MsgUB02
{
	
	private:
		string m_strMsgId;

	public:
		MsgUB02(string msgid);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
