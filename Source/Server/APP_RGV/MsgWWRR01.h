//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#include "DealData.h"

class MsgWWRR01
{
	
	private:
		string m_strMsgId;

	public:
		MsgWWRR01(string msgid);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
