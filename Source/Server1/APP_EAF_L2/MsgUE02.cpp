//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "MsgUE02.h"
#include <PowerTranser/MsgComponent.h>
#include <iXcomTCP2.h>

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgUE02::MsgUE02(void) 
{
}

ByteSeq MsgUE02::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgUE02::HandleMessage",logFileName);

	try
	{
		log.Info()<<"UE02 tel data is ready to start....................................................."<<endl;
		

		//格式：
		//PONO,HTNO,B_SEQ_NUM,PIT_NUM,LAY_NO,SCR_ID,WEIGHT,CAR_NO,eafNewOrOldFlag
		vector<string> kValues;	
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 9)
		{
			log.Info()<<"kValues.size() < 9，  error  return............."<<endl;
			return ret;
		}

		vector<string>::iterator itor;
		for (itor = kValues.begin(); itor != kValues.end(); itor ++)
		{
			if (*itor == "@")
			{
				*itor = "";
			}
		}

		string eafNewOrOldFlag = kValues[8];//1-新电炉  2-老电炉

		log.Info()<<"eafNewOrOldFlag = "<<eafNewOrOldFlag<<endl;
		if (eafNewOrOldFlag == "1")
		{
			m_strMsgId = "6251";
			log.Info()<<"this is new EAF, telID = "<<m_strMsgId<<endl;
		}
		else if (eafNewOrOldFlag == "2")
		{
			m_strMsgId = "6651";
			log.Info()<<"this is old EAF, telID = "<<m_strMsgId<<endl;
		}
		else
		{
			log.Info()<<"eafNewOrOldFlag  is NOT valid,  return......................"<<endl;
			return ret;
		}

		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//获取tag点
		sd["PONO"] = kValues[0];
		sd["HTNO"] = kValues[1];
		sd["B_SEQ_NUM"] = kValues[2];
		sd["PIT_NUM"] = kValues[3];
		sd["LAY_NO"] = kValues[4];
		sd["SCR_ID"] = kValues[5];
		sd["WEIGHT"] = kValues[6];
		sd["CAR_NO"] = kValues[7];
		
		ByteSeq data;
		sd.writeTo(data);
		//明码电文
		DealData dealdata = DealData();
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

