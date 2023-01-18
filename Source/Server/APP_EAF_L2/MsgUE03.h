//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************

//缺料反馈电文发送  UE03

#include "DealData.h"

class MsgUE03
{
	
	private:
		string m_strMsgId;

	public:
		MsgUE03(string msgid);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
