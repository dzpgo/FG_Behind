//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
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
