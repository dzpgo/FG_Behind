//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#include "MsgWWRR02.h"
#include <PowerTranser/MsgComponent.h>

using namespace Monitor;

MsgWWRR02::MsgWWRR02(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgWWRR02::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgWWRR02::HandleMessage",logFileName);

	try
	{
		log.Info()<<"WWRR02 tel data is ready to start....................................................."<<endl;
		//�����ʽ: ����,�ƻ���,���ϴ���1#��������1#������1,���ϴ���2#��������2#������2,���ϴ���3#��������3#������3
		//  A01,309192,1211#1211#341,1251#1251#128,1253#1253#89


		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 3)
		{
			log.Info()<<"kValues.size() <> 3,  error  return............."<<endl;
			return ret;
		}

		int kSize = kValues.size();
		//����  �ƻ���
		string rgvNo = kValues[0];
		string orderNo = kValues[1];

		string recipeInfoList = "";
		string recipeInfoList1 = "";
		//�ƻ���Ϣ
		for (int i=2; i < kSize; ++i)
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
			string jsonAll = "{\n" + json1 + "\n" + json2 + "\n" + json3 + "\n}";//��ӡ����

			string jsonAll1 = "{" + json1 + json2 + json3 + "}";//ʵ�ʷ���
			if (i == kSize - 1)//���һ�������Ӷ���
			{
				recipeInfoList = recipeInfoList + jsonAll + "\n";
				recipeInfoList1 = recipeInfoList1 + jsonAll1;
			}
			else
			{
				recipeInfoList = recipeInfoList + jsonAll + ",\n";
				recipeInfoList1 = recipeInfoList1 + jsonAll1 + ",";
			}
		}

		//��֯json��ʽ����
		string json1 = "\"rgvNo\":\"" + rgvNo + "\",";
		string json2 = "\"orderNo\":" + orderNo + "," ;
		string json3 = "\"recipeInfoList\":[\n" + recipeInfoList + "]";//��ӡ����

		string json31 = "\"recipeInfoList\":[" + recipeInfoList1 + "]";//ʵ�ʷ���

		string sndTelJson = "{\n" + json1 + "\n" + json2 + "\n" + json3 + "\n}";

		string sndTelJson2 = "{" + json1 + json2 + json31 + "}";
		log.Info()<<"sndTelJson = \n"<<sndTelJson<<endl;

		//��֯����SD����
		sd["JsonData"] =sndTelJson2;
		
		ByteSeq data;
		sd.writeTo(data);
		//���͵���
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//��ȡ����
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

