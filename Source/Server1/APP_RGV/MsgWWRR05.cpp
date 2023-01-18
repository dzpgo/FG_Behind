//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "MsgWWRR05.h"
#include <PowerTranser/MsgComponent.h>

using namespace Monitor;

MsgWWRR05::MsgWWRR05(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgWWRR05::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgWWRR05::HandleMessage",logFileName);

	try
	{
		log.Info()<<"WWRR05 tel data is ready to start....................................................."<<endl;
		//传入格式: 车号,停车位号
		//                 A01,P01


		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues.size() <> 2,  error  return............."<<endl;
			return ret;
		}

		//
		string rgvNo = kValues[0];
		string parkName = kValues[1];

		//组织json格式数据
		string json1 = "\"rgvNo\":\"" + rgvNo + "\",";
		string json2 =  "\"parkName\":\"" + parkName + "\"";
		string sndTelJson = "{\n" + json1 + "\n" + json2 + "\n}";

		string sndTelJson2 = "{" + json1 + json2 + "}";
		log.Info()<<"sndTelJson = \n"<<sndTelJson<<endl;

		//组织发送SD数据
		sd["JsonData"] =sndTelJson2;
		
		ByteSeq data;
		sd.writeTo(data);
		//发送电文
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//获取代理
		proxy->SendMsg(m_strMsgId, data);

	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}

    return ret;
}

