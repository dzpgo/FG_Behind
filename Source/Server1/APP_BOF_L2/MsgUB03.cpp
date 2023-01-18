//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "MsgUB03.h"
#include <PowerTranser/MsgComponent.h>
#include <climits>

using namespace Monitor;

MsgUB03::MsgUB03(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgUB03::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgUB03::HandleMessage",logFileName);

	try
	{
		log.Info()<<"start........."<<endl;
		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;
		DealData dealdata = DealData();

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 23)
		{
			log.Info()<<"kValues.size() <> 23,  error  return............."<<endl;
			return ret;
		}

		
		sd["SPARE"] = "            ";//12个空格  应用头固定部分		
		sd["MSGID"] = m_strMsgId;


		//获取tag点
		string steelno = kValues[0];
		string scrapecode = kValues[1];
		
		sd["STEEL_NO"] = StringHelper::ToNumber<int>(steelno);		
		sd["SCRAP_CODE"] = StringHelper::ToNumber<int>(scrapecode);

		//循环体 20次
		for ( int index=0 ; index < 20;  ++index )
		{
			string vecData = kValues[2+index*2];//接kValues[1]序号
			string vecData1 = kValues[3+index*2];			
			sd["UB03_DETAIL"][index]["REQ_WEIGHT"]  = StringHelper::ToNumber<int>(vecData);
			sd["UB03_DETAIL"][index]["STK_WEIGHT"]  = StringHelper::ToNumber<int>(vecData1);

			//如果是0，则赋值 INT_MIN = -2147483648  HEX=0x80  转炉L2电文规则：为0的，用0x80补
			if (vecData == "0")
			{
				sd["UB03_DETAIL"][index]["REQ_WEIGHT"] = INT_MIN;
			}
			if (vecData == "0")
			{
				sd["UB03_DETAIL"][index]["STK_WEIGHT"] = INT_MIN;
			}
		}
		// 
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

