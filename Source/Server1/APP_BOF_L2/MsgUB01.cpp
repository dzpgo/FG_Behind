//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "MsgUB01.h"
#include <PowerTranser/MsgComponent.h>
#include <climits>
#include <iXcomTCP2.h>

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgUB01::MsgUB01(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgUB01::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgUB01::HandleMessage",logFileName);

	try
	{
		log.Info()<<"UB01 tel data is ready to start....................................................."<<endl;
		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 24)
		{
			log.Info()<<"kValues.size() <> 24,  error  return............."<<endl;
			return ret;
		}

		//sd["SPARE"] = "            ";//12个空格  应用头固定部分
		//sd["MSGID"] = m_strMsgId;


		//获取tag点
		string steelno = kValues[0];
		string type = kValues[1];
		string carno = kValues[2];
		string weightcode = kValues[3];

		log.Info()<<"STEEL_NO = "<<steelno<<endl;
		log.Info()<<"TYPE = "<<type<<endl;
		log.Info()<<"CAR_NO = "<<carno<<endl;
		log.Info()<<"WEIGHT_CODE = "<<weightcode<<endl;

		sd["STEEL_NO"] = StringHelper::ToNumber<int>(steelno);
		sd["TYPE"] = StringHelper::ToNumber<int>(type);
		sd["CAR_NO"] = StringHelper::ToNumber<int>(carno);
		sd["WEIGHT_CODE"] = StringHelper::ToNumber<int>(weightcode);	

		//循环体 20次
		for ( int index=0 ; index < 20;  ++index )
		{
			log.Info()<<"\t Index in Loop  = "<<index<<" : ";
			log.Info()<<"  SCRAP_CODE = "<<kValues[4+index*2];
			log.Info()<<"  WEIGHT = "<<kValues[5+index*2]<<endl;

			string vecData = kValues[4+index*2];
			string vecData1 = kValues[5+index*2];
			sd["UB01_DETAIL"][index]["SCRAP_CODE"]  = StringHelper::ToNumber<int>(vecData);
			sd["UB01_DETAIL"][index]["WEIGHT"]  = StringHelper::ToNumber<int>(vecData1);

			//如果是0，则赋值 INT_MIN = -2147483648  HEX=0x80  转炉L2电文规则：为0的，用0x80补
			if (vecData == "0")
			{
				sd["UB01_DETAIL"][index]["SCRAP_CODE"] = INT_MIN;
			}
			if (vecData1 == "0")
			{
				sd["UB01_DETAIL"][index]["WEIGHT"] = INT_MIN;
			}

		}
		// 

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


		DealData dealdata = DealData();
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

