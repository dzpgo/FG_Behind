//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************

//װ���������ķ��� UE02

#include "DealData.h"

class MsgUE02
{
	
	private:
		string m_strMsgId;

	public:
		MsgUE02(void);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
