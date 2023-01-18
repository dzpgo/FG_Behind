//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#include "MsgWWRR03.h"
#include <PowerTranser/MsgComponent.h>

using namespace Monitor;

MsgWWRR03::MsgWWRR03(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgWWRR03::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgWWRR03::HandleMessage",logFileName);

	try
	{
		log.Info()<<"WWRR03 tel data is ready to start....................................................."<<endl;
		//�����ʽ: ����1,����2,����3
		//                 C01,B02,D03


		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 1)
		{
			log.Info()<<"kValues.size() < 1,  error  return............."<<endl;
			return ret;
		}

		int kSize = kValues.size();
		string parkStoreList = "";
		string parkStoreList1 = "";

		for (int i=0; i < kSize; ++i)
		{
			string parkStore = kValues[i];
			string jsonParkStore = "\"" + parkStore +"\"";
			if (i == kSize - 1)//���һ�������Ӷ���
			{
				parkStoreList = parkStoreList + jsonParkStore + "\n";
				parkStoreList1 = parkStoreList1 + jsonParkStore;
			}
			else
			{
				parkStoreList = parkStoreList + jsonParkStore + ",\n";
				parkStoreList1 = parkStoreList1 + jsonParkStore + ",";
			}
		}

		//��֯json��ʽ����
		string json1 = "\"parkStoreList\":[\n" + parkStoreList + "]";
		string json2 =  "\"parkStoreList\":[" + parkStoreList1 + "]";
		string sndTelJson = "{\n" + json1 + "\n}";

		string sndTelJson2 = "{" + json2 + "}";
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

