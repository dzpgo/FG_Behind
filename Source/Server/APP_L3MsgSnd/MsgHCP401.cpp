#include "MsgHCP401.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgHCP401::MsgHCP401(void)
{
	m_strMsgId = "HCP401";
}

MsgHCP401::~MsgHCP401(void)
{

}

void MsgHCP401::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgHCP401::HandleMessage",logFileName);
	try
	{
		log.Info()<<"send tel data is ready to start........................................................"<<endl;
		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//strValue格式：
		//OPERATE_FLAG,CAR_NO,SLOT_NO,WORK_TIME,REC_CREATOR
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 5)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string OPERATE_FLAG = kValues[0];
		string CAR_NO = kValues[1];
		string SLOT_NO = kValues[2];
		string WORK_TIME = kValues[3];
		string REC_CREATOR = kValues[4];

		log.Info()<<"OPERATE_FLAG = "<<OPERATE_FLAG<<endl;
		log.Info()<<"CAR_NO = "<<CAR_NO<<endl;
		log.Info()<<"SLOT_NO = "<<SLOT_NO<<endl;
		log.Info()<<"WORK_TIME = "<<WORK_TIME<<endl;
		log.Info()<<"REC_CREATOR = "<<REC_CREATOR<<endl;

		//组织smartdata数据
		sd["OPERATE_FLAG"] = OPERATE_FLAG;
		sd["CAR_NO"] = CAR_NO;
		sd["SLOT_NO"] = SLOT_NO;
		sd["WORK_TIME"] = WORK_TIME;
		sd["REC_CREATOR"] = REC_CREATOR;		

		//打印十六进制电文数据
		ByteSeq data;
		sd.writeTo(data);
		string sndTel = "";
		sndTel.assign(data.begin(), data.end());
		//data>>sndTel;
		ArrayMsg arrayMsgDataBuf;
		for (int i = 0; i < sndTel.length(); i ++)
		{
			arrayMsgDataBuf.push_back(*(sndTel.c_str() + i));
		}
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//将发送数据记录到数据库表中
		DealData dealdata = DealData();
		//明码电文
		string dataStr = dealdata.DumpValue(sd,",");
		//获取最大ID号
		int ID = dealdata.GetMaxId();
		//最大ID号加1
		ID += 1; 
		//将数据存到发送表中
		dealdata.InsertSendData(m_strMsgId,dataStr,data,ID);

		//开始发送电文
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//获取代理
		proxy->SendMsg(m_strMsgId, data);

		log.Info()<<"m_strMsgId = "<<m_strMsgId<<"  send ok....................................................."<<endl;

		//置发送标志位
		dealdata.UpdateSendDataFlag(ID);
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
}
