#include "MsgHCP421.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgHCP421::MsgHCP421(void)
{
	m_strMsgId = "HCP421";
}

MsgHCP421::~MsgHCP421(void)
{

}

void MsgHCP421::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgHCP421::HandleMessage",logFileName);
	try
	{
		log.Info()<<"send tel data is ready to start........................................................"<<endl;
		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//strValue��ʽ��
		//OPERATE_FLAG,  WORK_TIME,  LOOP_COUNT,  STOCK_PLACE_CODE#MAT_CODE#COMP_CODE#STOCK_WGT��STOCK_PLACE_CODE#MAT_CODE#COMP_CODE#STOCK_WGT
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 4)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string OPERATE_FLAG = kValues[0];
		string WORK_TIME = kValues[1];
		string LOOP_COUNT = kValues[2];

		log.Info()<<"OPERATE_FLAG = "<<OPERATE_FLAG<<endl;
		log.Info()<<"WORK_TIME = "<<WORK_TIME<<endl;
		log.Info()<<"LOOP_COUNT = "<<LOOP_COUNT<<endl;

		int nLoopCount = StringHelper::ToNumber<int>(LOOP_COUNT);

		//��֯smartdata����
		sd["OPERATE_FLAG"] = OPERATE_FLAG;
		sd["WORK_TIME"] = WORK_TIME;
		sd["LOOP_COUNT"] = nLoopCount;

		//KCSJ������֯
		vector<string> KCSJValues;
		for (int i = 0; i < nLoopCount; ++i)
		{
			KCSJValues = StringHelper::ToVector<string>(kValues[3+i], const_cast<char*>("#"), static_cast<int>(strlen("#")));
			log.Info()<<"\t Index in loop =  "<<i<<" : ";

			sd["HCP421_DETAIL"][i]["STOCK_PLACE_CODE"] = KCSJValues[0];
			log.Info()<<"  STOCK_PLACE_CODE = "<<KCSJValues[0];

			sd["HCP421_DETAIL"][i]["MAT_CODE"] = KCSJValues[1];
			log.Info()<<"  MAT_CODE = "<<KCSJValues[1];

			sd["HCP421_DETAIL"][i]["COMP_CODE"] = KCSJValues[2];
			log.Info()<<"  COMP_CODE = "<<KCSJValues[2];

			sd["HCP421_DETAIL"][i]["STOCK_WGT"] = StringHelper::ToNumber<int>(KCSJValues[3]);
			log.Info()<<"  STOCK_WGT = "<<KCSJValues[3]<<endl;
		}

		//��ӡʮ�����Ƶ�������
		ByteSeq data;
		sd.writeTo(data);
		string sndTel = "";
		sndTel.assign(data.begin(), data.end());
		ArrayMsg arrayMsgDataBuf;
		for (int i = 0; i < sndTel.length(); i ++)
		{
			arrayMsgDataBuf.push_back(*(sndTel.c_str() + i));
		}
		log.DebugHex( (void*)&arrayMsgDataBuf.front() , (int)(arrayMsgDataBuf.size()) );

		//���������ݼ�¼�����ݿ����
		DealData dealdata = DealData();
		//�������
		string dataStr = dealdata.DumpValue(sd,",");
		//��ȡ���ID��
		int ID = dealdata.GetMaxId();
		//���ID�ż�1
		ID += 1; 
		//�����ݴ浽���ͱ���
		dealdata.InsertSendData(m_strMsgId,dataStr,data,ID);

		//��ʼ���͵���
		PowerTranserPrx  proxy = ProxyWrapper<PowerTranserPrx>("iPlature/PowerTranserOut");//��ȡ����
		proxy->SendMsg(m_strMsgId, data);

		log.Info()<<"m_strMsgId = "<<m_strMsgId<<"  send ok....................................................."<<endl;

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
}
