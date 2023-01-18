//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
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
		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;
		DealData dealdata = DealData();

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 23)
		{
			log.Info()<<"kValues.size() <> 23,  error  return............."<<endl;
			return ret;
		}

		
		sd["SPARE"] = "            ";//12���ո�  Ӧ��ͷ�̶�����		
		sd["MSGID"] = m_strMsgId;


		//��ȡtag��
		string steelno = kValues[0];
		string scrapecode = kValues[1];
		
		sd["STEEL_NO"] = StringHelper::ToNumber<int>(steelno);		
		sd["SCRAP_CODE"] = StringHelper::ToNumber<int>(scrapecode);

		//ѭ���� 20��
		for ( int index=0 ; index < 20;  ++index )
		{
			string vecData = kValues[2+index*2];//��kValues[1]���
			string vecData1 = kValues[3+index*2];			
			sd["UB03_DETAIL"][index]["REQ_WEIGHT"]  = StringHelper::ToNumber<int>(vecData);
			sd["UB03_DETAIL"][index]["STK_WEIGHT"]  = StringHelper::ToNumber<int>(vecData1);

			//�����0����ֵ INT_MIN = -2147483648  HEX=0x80  ת¯L2���Ĺ���Ϊ0�ģ���0x80��
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
		//�������
		//string dataStr = dealdata.DumpValue(sd,",");
		//��ȡ���ID��
		//int ID = dealdata.GetMaxId();
		//���ID�ż�1
		//ID += 1; 
		//�����ݴ浽���ͱ���
		//dealdata.InsertSendData(m_strMsgId,dataStr,data,ID);
		//���͵���
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//��ȡ����
		proxy->SendMsg(m_strMsgId, data);
		//�÷��ͱ�־λ
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

