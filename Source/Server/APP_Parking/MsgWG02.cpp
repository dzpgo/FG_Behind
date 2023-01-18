
//车辆车辆准许离开通知电文 MsgWG02
#include "MsgWG02.h"
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

MsgWG02::MsgWG02(void)
{
	m_strMsgId = "WG02";
}

MsgWG02::~MsgWG02(void)
{

}

void MsgWG02::HandleMessage(const string strValue, const string logFileName)
{	
	string functionName="MsgWG02::HandleMessage";
	LOG log(functionName, logFileName);
	//LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		log.Info()<<"WG02 send handle start.............."<<endl;
		//strValue格式：
		//停车位号 ,车号
		//parkingNO,carNO
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string parkingNO = kValues[0];
		string carNO = kValues[1];

		log.Info()<<"WG02 data: parkingNO = "<<parkingNO<<" , carNO = "<<carNO<<endl;

		//组织发送数据电文格式
		string sndTel = m_strMsgId + "," + parkingNO + "," + carNO;

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
		log.Info()<<endl<<"WG02 sended out ............ "<<endl;
	}
	catch (std::exception& ex)
	{
		log.Info()<<endl<<"WG02 sended error .............. "<<endl;
	}
	catch (...)
	{
		log.Info()<<endl<<"WG02 sended error ............ "<<endl;
	}
}
