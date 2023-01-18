//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
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
		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;
		DealData dealdata = DealData();

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 7)
		{
			log.Info()<<"kValues.size() <> 7��  error  return............."<<endl;
			return ret;
		}
		//��ȡtag��
		sd["PONO"] = kValues[0];
		sd["HTNO"] = kValues[1];
		sd["B_SEQ_NUM"] = kValues[2];
		sd["PIT_NUM"] = kValues[3];
		sd["SCR_ID"] = kValues[4];
		sd["REQ_WEIGHT"] = kValues[5];
		sd["STK_WEIGHT"] = kValues[6];
		
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

