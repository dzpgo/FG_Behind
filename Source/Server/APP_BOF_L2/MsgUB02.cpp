//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
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
		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues.size() <> 2,  error  return............."<<endl;
			return ret;
		}

		//sd["SPARE"] = "            ";//12���ո�  Ӧ��ͷ�̶�����
		//sd["MSGID"] = m_strMsgId;

		//��ȡtag��
		string steelno = kValues[0];
		string carno = kValues[1];

		log.Info()<<"STEEL_NO = "<<steelno<<endl;
		log.Info()<<"RGV_NO = "<<carno<<endl;

		sd["STEEL_NO"] = StringHelper::ToNumber<int>(steelno);
		sd["RGV_NO"] = StringHelper::ToNumber<int>(carno);

		DealData dealdata = DealData();
		
		ByteSeq data;
		sd.writeTo(data);
		//�������
		string dataStr = dealdata.DumpValue(sd,",");
		//��ȡ���ID��
		int ID = dealdata.GetMaxId();
		//���ID�ż�1
		ID += 1; 
		//�����ݴ浽���ͱ���
		dealdata.InsertSendData(m_strMsgId,dataStr,data,ID);
		//���͵���
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//��ȡ����
		proxy->SendMsg(m_strMsgId, data);
		//�÷��ͱ�־λ
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

