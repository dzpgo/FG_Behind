//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************
#include "MsgWWRR04.h"
#include <PowerTranser/MsgComponent.h>

using namespace Monitor;

MsgWWRR04::MsgWWRR04(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgWWRR04::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgWWRR04::HandleMessage",logFileName);

	try
	{
		log.Info()<<"WWRR04 tel data is ready to start....................................................."<<endl;
		//传入格式:   装载点号,剩余时间(分钟),计划号,配料代码1#配料名称1#配料量1,配料代码2#配料名称2#配料量2,配料代码3#配料名称3#配料量3
		//                   C01,21,391211,1211#1211#341,1251#1251#128,1253#1253#89


		// 读取powertrans电文结构
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 4)
		{
			log.Info()<<"kValues.size() <> 4,  error  return............."<<endl;
			return ret;
		}

		int kSize = kValues.size();
		//车号  计划号
		string loadingParkNo = kValues[0];
		string remainTime = kValues[1];
		string orderNo = kValues[2];

		string recipeInfoList = "";
		string recipeInfoList1 = "";
		//计划信息
		for (int i=3; i < kSize; ++i)
		{
			vector<string> orderValues;
			string str = kValues[i];
			orderValues = StringHelper::ToVector<string>(str, const_cast<char*>(SPLIT_WELL), static_cast<int>(strlen(SPLIT_WELL)));

			if (orderValues.size() < 3)
			{
				log.Info()<<"orderValues.size() <> 3,  error  return............."<<endl;
				return ret;
			}

			string recipeNo = orderValues[0];
			string recipeName = orderValues[1];
			string recipeWeight = orderValues[2];

			string json1 = "\"recipeNo\":\"" + recipeNo + "\",";
			string json2 = "\"recipeName\":\"" + recipeName + "\",";
			string json3 =  "\"recipeWeight\":" + recipeWeight;
			string jsonAll = "{\n" + json1 + "\n" + json2 + "\n" + json3 + "\n}";

			string jsonAll1 = "{" + json1 + json2 + json3 + "}";

			if (i == kSize - 1)//最后一个，不加逗号
			{
				recipeInfoList = recipeInfoList + jsonAll + "\n";
				recipeInfoList1 = recipeInfoList1 + jsonAll1;
			}
			else
			{
				recipeInfoList = recipeInfoList + jsonAll + ",\n";
				recipeInfoList1 = recipeInfoList1 + jsonAll1 +",";
			}
		}

		//组织json格式数据
		string json1 = "\"loadingParkNo\":\"" + loadingParkNo + "\",";
		string json2 = "\"remainTime\":" + remainTime + "," ;
		string json3 = "\"orderNo\":" + orderNo + "," ;
		string json4 = "\"recipeInfoList\":[\n" + recipeInfoList + "]";
		
		string json41 = "\"recipeInfoList\":[" + recipeInfoList1 + "]";

		string sndTelJson = "{\n" + json1 + "\n" + json2 + "\n" + json3 + "\n" + json4 + "\n}";

		string sndTelJson2 = "{" + json1 + json2 + json3 + json41 + "}";

		log.Info()<<"sndTelJson = \n"<<sndTelJson<<endl;

		//组织发送SD数据
		sd["JsonData"] =sndTelJson2;
		
		ByteSeq data;
		sd.writeTo(data);
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

