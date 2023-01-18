//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
//********************************************************************
#include "MsgUE01.h"
#include <PowerTranser/MsgComponent.h>
#include <iXcomTCP2.h>

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgUE01::MsgUE01(void) 
{
}

ByteSeq MsgUE01::HandleMessage(const string strValue, const string logFileName)
{
	ByteSeq ret;
	LOG log("MsgUE01::HandleMessage",logFileName);

	try
	{
		log.Info()<<"UE01 tel data is ready to start....................................................."<<endl;

		//��ʽ��
		//PONO,HTNO,B_SEQ_NUM,PIT_NUM,WEIGHT_STATUS,LAY_NO,CAR_NO,SCR_ID,WEIGHT,eafNewOrOldFlag
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 10)
		{
			log.Info()<<"kValues.size() < 10,  error  return............."<<endl;
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

		string eafNewOrOldFlag = kValues[9];//1-�µ�¯  2-�ϵ�¯
		log.Info()<<"eafNewOrOldFlag = "<<eafNewOrOldFlag<<endl;
		if (eafNewOrOldFlag == "1")
		{
			m_strMsgId = "6250";
			log.Info()<<"this is new EAF, telID = "<<m_strMsgId<<endl;
		}
		else if (eafNewOrOldFlag == "2")
		{
			m_strMsgId = "6650";
			log.Info()<<"this is old EAF, telID = "<<m_strMsgId<<endl;
		}
		else
		{
			log.Info()<<"eafNewOrOldFlag  is NOT valid,  return......................"<<endl;
			return ret;
		}

		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//��ȡtag��
		sd["PONO"] = kValues[0];
		sd["HTNO"] = kValues[1];
		sd["B_SEQ_NUM"] = kValues[2];
		sd["PIT_NUM"] = kValues[3];
		sd["WEIGHT_STATUS"] = kValues[4];
		sd["LAY_NO"] = kValues[5];
		sd["CAR_NO"] = kValues[6];
		sd["SCR_ID"] = kValues[7];
		sd["WEIGHT"] = kValues[8];

		log.Info()<<"PONO = "<<kValues[0]<<endl;
		log.Info()<<"HTNO = "<<kValues[1]<<endl;
		log.Info()<<"B_SEQ_NUM = "<<kValues[2]<<endl;
		log.Info()<<"PIT_NUM = "<<kValues[3]<<endl;
		log.Info()<<"WEIGHT_STATUS = "<<kValues[4]<<endl;
		log.Info()<<"LAY_NO = "<<kValues[5]<<endl;
		log.Info()<<"CAR_NO = "<<kValues[6]<<endl;
		log.Info()<<"SCR_ID = "<<kValues[7]<<endl;
		log.Info()<<"WEIGHT = "<<kValues[8]<<endl;
		

		//�µ�¯ ���ĺ�:6250
		//�ϵ�¯ ���ĺ�:6650
		
		ByteSeq data;
		sd.writeTo(data);
		//�������
		DealData dealdata = DealData();
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

