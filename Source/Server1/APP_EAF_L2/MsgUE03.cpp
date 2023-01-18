//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "MsgUE03.h"
#include <PowerTranser/MsgComponent.h>

using namespace Monitor;

MsgUE03::MsgUE03(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgUE03::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgUE03::HandleMessage",logFileName);

	try
	{
		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;
		DealData dealdata = DealData();

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 7)
		{
			log.Info()<<"kValues.size() <> 7，  error  return............."<<endl;
			return ret;
		}
		//获取tag点
		sd["PONO"] = kValues[0];
		sd["HTNO"] = kValues[1];
		sd["B_SEQ_NUM"] = kValues[2];
		sd["PIT_NUM"] = kValues[3];
		sd["SCR_ID"] = kValues[4];
		sd["REQ_WEIGHT"] = kValues[5];
		sd["STK_WEIGHT"] = kValues[6];
		
		ByteSeq data;
		sd.writeTo(data);
		//明码电文
		//string dataStr = dealdata.DumpValue(sd,",");
		//获取最大ID号
		//int ID = dealdata.GetMaxId();
		//最大ID号加1
		//ID += 1; 
		//将数据存到发送表中
		//dealdata.InsertSendData(m_strMsgId,dataStr,data,ID);
		//发送电文
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//获取代理
		proxy->SendMsg(m_strMsgId, data);
		//置发送标志位
		//dealdata.UpdateSendDataFlag(ID);

		//CDataAccess::GetInstance()->m_DBCon.Commit();
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

