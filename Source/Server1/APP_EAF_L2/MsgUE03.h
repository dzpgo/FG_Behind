//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************

//ȱ�Ϸ������ķ���  UE03

#include "DealData.h"

class MsgUE03
{
	
	private:
		string m_strMsgId;

	public:
		MsgUE03(string msgid);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
