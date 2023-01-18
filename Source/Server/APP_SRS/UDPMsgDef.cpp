//********************************************************************
//** Copyright (c) 2016 �������
//** �����ˣ�������
//** ������\�ļ�����UDPMsgDef.h
//** �๦�ܣ�UDP�������ݽṹ
//** ������
//** �������ڣ�2016-12-09
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************

#include "UDPMsgDef.h"

using namespace Monitor;

void
UdpUtil::trans2SmartData(MY_UDP_MSG* msg, const int lenMsgData, Ice::ByteSeq& sd)
{
	if (msg == NULL)
		throw invalid_argument("trans2SmartDataʧ��!(MY_UDP_MSG*δ��ֵ)");
	else if (msg->lenMsgId == 0)
		throw invalid_argument("trans2SmartDataʧ��!(���ĺų���Ϊ��)");

	// ���powertranser��Ҫ�����ݸ�ʽ
	byte header[POWER_TRANS_HEAD];
	memset(header, 0x00, POWER_TRANS_HEAD);

	// ��֯����ͷ ���ں궨������ http://blog.sina.com.cn/s/blog_4a0824490102vvo5.html
	int lenHeader = 0;
	// 32λ��64λpowertranser�ĵ���ͷ��һ��
#ifdef _WIN64 
	lenHeader = msg->lenMsgId + 8; // 1byte[���ĳ���] + 7byte[0x00] + ���ĺ�[�䳤]
	header[0]=msg->lenMsgId;	 // ���ֽ�:���ĺų���
	for (int i = 0; i < 7; i ++) // ����7���ֽ�0x00
		header[i+1] = 0x00;
	memcpy(header+8, msg->msgId, msg->lenMsgId); // ���λ�ǵ��ĺ�	
#else
	lenHeader = msg->lenMsgId + 4; // 1byte[���ĳ���] + 3byte[0x00] + ���ĺ�[�䳤]
	header[0]=msg->lenMsgId;	 // ���ֽ�:���ĺų���
	for (int i = 0; i < 3; i ++) // ����3���ֽ�0x00
		header[i+1] = 0x00;
	memcpy(header+4, msg->msgId, msg->lenMsgId); // ���λ�ǵ��ĺ�	
#endif

	// ��֯��������
	byte data[MAX_BUFFER_LENGTH];
	memset(data, 0x00, MAX_BUFFER_LENGTH);
	memcpy(data, msg->msgData, lenMsgData);

	// д��powertrans����
	for (int i = 0; i < lenHeader; i ++)
		sd.push_back(header[i]);
	for (int i = 0; i < lenMsgData; i ++)
		sd.push_back(data[i]);
}

void
UdpUtil::rcv2UdpMsg(const Ice::ByteSeq& rcv, MY_UDP_MSG& msg, const int lenMsgId)
{
	// clear
	memset(&msg, 0x00, sizeof(MY_UDP_MSG));
	msg.lenMsgId = lenMsgId;

	if (lenMsgId == 0)
		throw invalid_argument("rcv2UdpMsg��������! (����lenMsgId������Ϊ0)");

	// �������ͷ����
	int lenRcvHeader =  0;
#ifdef _WIN64
	lenRcvHeader =  rcv[0] + 8; // 1byte[���ĳ���] + 7byte[0x00] + ���ĺ�[�䳤]
#else
	lenRcvHeader = rcv[0] + 4; // 1byte[���ĳ���] + 4byte[0x00] + ���ĺ�[�䳤]
#endif

	int lenRcvData = rcv.size() - lenRcvHeader;
	if (lenRcvData < lenMsgId)
		throw invalid_argument("rcv2UdpMsg��������! (���ĳ���С�ڲ���lenMsgId�趨ֵ)");

	memcpy(msg.msgId, (byte*) &rcv[0] + lenRcvHeader, lenMsgId);
	memcpy(msg.msgData, (byte*) &rcv[0] + lenRcvHeader, lenRcvData);
}

void
UdpUtil::splitUdpMsg(MY_UDP_MSG& msg, const int lenMsgData, Ice::StringSeq& vecField, char split)
{
	string strField;
	for (int i = 0; i < lenMsgData; i ++)
	{
		if (msg.msgData[i] == split)
		{
			vecField.push_back(strField); // ���ֶν���
			strField="";// ����
		}
		else
		{
			char szTmp[2];
			//sprintf(szTmp, "%c", msg.msgData[i]);
			strField += szTmp; // ���ֶμ���
		}
	}
}

void
UdpUtil::wrapSmartData(const Ice::StringSeq& vecField, iPlature::SmartData& sd, int& index)
{
	for (int m = 0; m < sd.size(); m ++)
	{
		if (sd[m].type() == iPlature::SmartData::COMPOSITE)
		{
			for (int i = 0; i < sd[m].size(); i ++)
			{
				wrapSmartData(vecField, sd[m][i], index);
			}
		}
		else if (sd[m].type() == iPlature::SmartData::STRING)
		{
			//index < vecField.size() ? sd[m].setString(vecField[index]) : 1;
			if (index < vecField.size())
			{
				sd[m].setString(vecField[index]);
			}
			index ++;
		}
	}
}