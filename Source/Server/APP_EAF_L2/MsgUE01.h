//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************

//װ��ʵ�����ķ���  UE01

#include "DealData.h"

class MsgUE01
{
	
	private:
		string m_strMsgId;

	public:
		MsgUE01(void);
		ByteSeq HandleMessage(const string strValue, const string logFileName);
};
