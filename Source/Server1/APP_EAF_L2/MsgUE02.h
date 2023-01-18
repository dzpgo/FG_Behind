//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************

//装车启动电文发送 UE02

#include "DealData.h"

class MsgUE02
{
	
	private:
		string m_strMsgId;

	public:
		MsgUE02(void);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
