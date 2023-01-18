#include "MsgHCP421.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgHCP421::MsgHCP421(void)
{
	m_strMsgId = "HCP421";
}

MsgHCP421::~MsgHCP421(void)
{

}

void MsgHCP421::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgHCP421::HandleMessage",logFileName);
	try
	{
		log.Info()<<"send tel data is ready to start........................................................"<<endl;
		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//strValue格式：
		//OPERATE_FLAG,  WORK_TIME,  LOOP_COUNT,  STOCK_PLACE_CODE#MAT_CODE#COMP_CODE#STOCK_WGT，STOCK_PLACE_CODE#MAT_CODE#COMP_CODE#STOCK_WGT
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 4)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string OPERATE_FLAG = kValues[0];
		string WORK_TIME = kValues[1];
		string LOOP_COUNT = kValues[2];

		log.Info()<<"OPERATE_FLAG = "<<OPERATE_FLAG<<endl;
		log.Info()<<"WORK_TIME = "<<WORK_TIME<<endl;
		log.Info()<<"LOOP_COUNT = "<<LOOP_COUNT<<endl;

		int nLoopCount = StringHelper::ToNumber<int>(LOOP_COUNT);

		//组织smartdata数据
		sd["OPERATE_FLAG"] = OPERATE_FLAG;
		sd["WORK_TIME"] = WORK_TIME;
		sd["LOOP_COUNT"] = nLoopCount;

		//KCSJ数据组织
		vector<string> KCSJValues;
		for (int i = 0; i < nLoopCount; ++i)
		{
			KCSJValues = StringHelper::ToVector<string>(kValues[3+i], const_cast<char*>("#"), static_cast<int>(strlen("#")));
			log.Info()<<"\t Index in loop =  "<<i<<" : ";

			sd["HCP421_DETAIL"][i]["STOCK_PLACE_CODE"] = KCSJValues[0];
			log.Info()<<"  STOCK_PLACE_CODE = "<<KCSJValues[0];

			sd["HCP421_DETAIL"][i]["MAT_CODE"] = KCSJValues[1];
			log.Info()<<"  MAT_CODE = "<<KCSJValues[1];

			sd["HCP421_DETAIL"][i]["COMP_CODE"] = KCSJValues[2];
			log.Info()<<"  COMP_CODE = "<<KCSJValues[2];

			sd["HCP421_DETAIL"][i]["STOCK_WGT"] = StringHelper::ToNumber<int>(KCSJValues[3]);
			log.Info()<<"  STOCK_WGT = "<<KCSJValues[3]<<endl;
		}

		//打印十六进制电文数据
		ByteSeq data;
		sd.writeTo(data);
		string sndTel = "";
		sndTel.assign(data.begin(), data.end());
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
