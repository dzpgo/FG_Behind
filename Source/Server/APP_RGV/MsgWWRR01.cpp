//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#include "MsgWWRR01.h"
#include <PowerTranser/MsgComponent.h>

using namespace Monitor;

MsgWWRR01::MsgWWRR01(string msgid) 
{
	m_strMsgId=msgid;
}

ByteSeq MsgWWRR01::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgWWRR01::HandleMessage",logFileName);

	try
	{
		log.Info()<<"WWRR01 tel data is ready to start....................................................."<<endl;
		//�����ʽ: ����,�������
		//                 A01,1


		// ��ȡpowertrans���Ľṹ
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
		string requestLockingFlag = kValues[1];

		//��֯json��ʽ����
		string json1 = "\"rgvNo\":\"" + rgvNo + "\",";
		string json2 =  "\"requestLockingFlag\":" + requestLockingFlag;
		string sndTelJson = "{\n" + json1 + "\n" + json2 + "\n}";

		string sndTelJson2 = "{" + json1 + json2 +"}";

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

