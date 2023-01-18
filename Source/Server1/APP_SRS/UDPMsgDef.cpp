//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建人：张晓荣
//** 类名称\文件名：UDPMsgDef.h
//** 类功能：UDP电文数据结构
//** 描述：
//** 创建日期：2016-12-09
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************

#include "UDPMsgDef.h"

using namespace Monitor;

void
UdpUtil::trans2SmartData(MY_UDP_MSG* msg, const int lenMsgData, Ice::ByteSeq& sd)
{
	if (msg == NULL)
		throw invalid_argument("trans2SmartData失败!(MY_UDP_MSG*未赋值)");
	else if (msg->lenMsgId == 0)
		throw invalid_argument("trans2SmartData失败!(电文号长度为空)");

	// 组成powertranser需要的数据格式
	byte header[POWER_TRANS_HEAD];
	memset(header, 0x00, POWER_TRANS_HEAD);

	// 组织电文头 关于宏定义的情况 http://blog.sina.com.cn/s/blog_4a0824490102vvo5.html
	int lenHeader = 0;
	// 32位与64位powertranser的电文头不一样
#ifdef _WIN64 
	lenHeader = msg->lenMsgId + 8; // 1byte[电文长度] + 7byte[0x00] + 电文号[变长]
	header[0]=msg->lenMsgId;	 // 首字节:电文号长度
	for (int i = 0; i < 7; i ++) // 后续7个字节0x00
		header[i+1] = 0x00;
	memcpy(header+8, msg->msgId, msg->lenMsgId); // 最后几位是电文号	
#else
	lenHeader = msg->lenMsgId + 4; // 1byte[电文长度] + 3byte[0x00] + 电文号[变长]
	header[0]=msg->lenMsgId;	 // 首字节:电文号长度
	for (int i = 0; i < 3; i ++) // 后续3个字节0x00
		header[i+1] = 0x00;
	memcpy(header+4, msg->msgId, msg->lenMsgId); // 最后几位是电文号	
#endif

	// 组织电文内容
	byte data[MAX_BUFFER_LENGTH];
	memset(data, 0x00, MAX_BUFFER_LENGTH);
	memcpy(data, msg->msgData, lenMsgData);

	// 写入powertrans数组
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
		throw invalid_argument("rcv2UdpMsg参数有误! (参数lenMsgId不能设为0)");

	// 计算电文头长度
	int lenRcvHeader =  0;
#ifdef _WIN64
	lenRcvHeader =  rcv[0] + 8; // 1byte[电文长度] + 7byte[0x00] + 电文号[变长]
#else
	lenRcvHeader = rcv[0] + 4; // 1byte[电文长度] + 4byte[0x00] + 电文号[变长]
#endif

	int lenRcvData = rcv.size() - lenRcvHeader;
	if (lenRcvData < lenMsgId)
		throw invalid_argument("rcv2UdpMsg参数有误! (电文长度小于参数lenMsgId设定值)");

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
			vecField.push_back(strField); // 本字段结束
			strField="";// 重置
		}
		else
		{
			char szTmp[2];
			//sprintf(szTmp, "%c", msg.msgData[i]);
			strField += szTmp; // 本字段继续
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