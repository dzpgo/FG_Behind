//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "MsgUB02.h"
#include <PowerTranser/MsgComponent.h>
#include <iXcomTCP2.h>

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgUB02::MsgUB02(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgUB02::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgUB02::HandleMessage",logFileName);

	try
	{
		log.Info()<<"UB02 tel data is ready to start....................................................."<<endl;
		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues.size() <> 2,  error  return............."<<endl;
			return ret;
		}

		//sd["SPARE"] = "            ";//12个空格  应用头固定部分
		//sd["MSGID"] = m_strMsgId;

		//获取tag点
		string steelno = kValues[0];
		string carno = kValues[1];

		log.Info()<<"STEEL_NO = "<<steelno<<endl;
		log.Info()<<"RGV_NO = "<<carno<<endl;

		sd["STEEL_NO"] = StringHelper::ToNumber<int>(steelno);
		sd["RGV_NO"] = StringHelper::ToNumber<int>(carno);

		DealData dealdata = DealData();
		
		ByteSeq data;
		sd.writeTo(data);
		//明码电文
		string dataStr = dealdata.DumpValue(sd,",");
		//获取最大ID号
		int ID = dealdata.GetMaxId();
		//最大ID号加1
		ID += 1; 
		//将数据存到发送表中
		dealdata.InsertSendData(m_strMsgId,dataStr,data,ID);
		//发送电文
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//获取代理
		proxy->SendMsg(m_strMsgId, data);
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

    return ret;
}

