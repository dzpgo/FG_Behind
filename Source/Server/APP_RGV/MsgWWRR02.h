//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
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
