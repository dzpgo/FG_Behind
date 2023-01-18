//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************

//装车实绩电文发送  UE01

#include "DealData.h"

class MsgUE01
{
	
	private:
		string m_strMsgId;

	public:
		MsgUE01(void);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
