//********************************************************************
//** Copyright (c) 2016 �������
//** �޸��ˣ�
//** �޸����ڣ�
//** �������ڣ�
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
		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		vector<string> kValues;

		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));	
		if (kValues.size() < 24)
		{
			log.Info()<<"kValues.size() <> 24,  error  return............."<<endl;
			return ret;
		}

		//sd["SPARE"] = "            ";//12���ո�  Ӧ��ͷ�̶�����
		//sd["MSGID"] = m_strMsgId;


		//��ȡtag��
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

		//ѭ���� 20��
		for ( int index=0 ; index < 20;  ++index )
		{
			log.Info()<<"\t Index in Loop  = "<<index<<" : ";
			log.Info()<<"  SCRAP_CODE = "<<kValues[4+index*2];
			log.Info()<<"  WEIGHT = "<<kValues[5+index*2]<<endl;

			string vecData = kValues[4+index*2];
			string vecData1 = kValues[5+index*2];
			sd["UB01_DETAIL"][index]["SCRAP_CODE"]  = StringHelper::ToNumber<int>(vecData);
			sd["UB01_DETAIL"][index]["WEIGHT"]  = StringHelper::ToNumber<int>(vecData1);

			//�����0����ֵ INT_MIN = -2147483648  HEX=0x80  ת¯L2���Ĺ���Ϊ0�ģ���0x80��
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

		//��ӡʮ�����Ƶ�������
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

