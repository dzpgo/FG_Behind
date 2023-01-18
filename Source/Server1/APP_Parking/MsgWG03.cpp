
//料格启动作业通知电文 MsgWG03
#include "MsgWG03.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "SQL4Parking.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgWG03::MsgWG03(void)
{
	m_strMsgId = "WG03";
}

MsgWG03::~MsgWG03(void)
{

}

void MsgWG03::HandleMessage(const string strValue, const string logFileName)
{
	string functionName="MsgWG03::HandleMessage";
	LOG log(functionName, logFileName);
	//LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		log.Info()<<"WG03 send handle start.............."<<endl;

		string gridNO = strValue;

		log.Info()<<"WG03 data: gridNO = "<<gridNO<<endl;

		//组织发送数据电文格式
		string sndTel = m_strMsgId + "," + gridNO;

		ArrayMsg arrayMsgDataBuf;
		for (int i = 0; i < sndTel.length(); i ++)
		{
			arrayMsgDataBuf.push_back(*(sndTel.c_str() + i));
		}
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//根据实际情况设定通信回线号
		int lineNO = 0;
		if (false == SQL4Parking::SelComLineNO("GridMgr", lineNO))
		{
			log.Info()<<"GridMgr  lineNO  SelComLineNO is ERROR......return false.........."<<endl;
			return;
		}

		int ret = PCS_Send(lineNO, m_strMsgId, arrayMsgDataBuf);
		log.Debug()<<"ret="<<ret<<endl;
		log.Info()<<endl<<"WG03 sended out ............ "<<endl;
	}
	catch (std::exception& ex)
	{
		log.Info()<<endl<<"WG03 sended error .............. "<<endl;
	}
	catch (...)
	{
		log.Info()<<endl<<"WG03 sended error ............ "<<endl;
	}
}
