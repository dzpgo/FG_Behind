#include "MsgHCP412.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgHCP412::MsgHCP412(void)
{
	m_strMsgId = "HCP412";
}

MsgHCP412::~MsgHCP412(void)
{

}

void MsgHCP412::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgHCP412::HandleMessage",logFileName);
	try
	{
		log.Info()<<"send tel data is ready to start........................................................"<<endl;
		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//strValue��ʽ��
		//ע�⣺��ֵ��@��������ʶ
		//OPERATE_FLAG,  HC_WORK_SEQ_NO,  CAR_NO,  CAR_TYPE,  DST_STOCK_CODE,  DL_POS��TAP_NO��PONO��ST_NO����BACK�ֶξ��㲻�ˣ�LOOP_COUNT��
		// STOCK_PLACE_CODE#MAT_CODE#COMP_CODE#WGT ,STOCK_PLACE_CODE#MAT_CODE#COMP_CODE#WGT  //װ��ʵ����ʽ��#�ָ�
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 10)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		vector<string>::iterator itor;
		for (itor = kValues.begin(); itor != kValues.end(); itor ++)
		{
			if (*itor == "@")
			{
				*itor = "";
			}
		}

		string OPERATE_FLAG = kValues[0];
		string HC_WORK_SEQ_NO = kValues[1];
		string CAR_NO = kValues[2];
		string CAR_TYPE = kValues[3];
		string DST_STOCK_CODE = kValues[4];
		string DL_POS = kValues[5];
		string TAP_NO = kValues[6];
		string PONO = kValues[7];
		string ST_NO = kValues[8];
		string LOOP_COUNT = kValues[9];

		int nLoopCount = StringHelper::ToNumber<int>(LOOP_COUNT);

		log.Info()<<"OPERATE_FLAG = "<<OPERATE_FLAG<<endl;
		log.Info()<<"HC_WORK_SEQ_NO = "<<HC_WORK_SEQ_NO<<endl;
		log.Info()<<"CAR_NO = "<<CAR_NO<<endl;
		log.Info()<<"CAR_TYPE = "<<CAR_TYPE<<endl;
		log.Info()<<"DST_STOCK_CODE = "<<DST_STOCK_CODE<<endl;
		log.Info()<<"DL_POS = "<<DL_POS<<endl;
		log.Info()<<"TAP_NO = "<<TAP_NO<<endl;
		log.Info()<<"PONO = "<<PONO<<endl;
		log.Info()<<"ST_NO = "<<ST_NO<<endl;
		log.Info()<<"LOOP_COUNT = "<<LOOP_COUNT<<endl;

		//��֯smartdata����
		sd["OPERATE_FLAG"] = OPERATE_FLAG;
		sd["HC_WORK_SEQ_NO"] = HC_WORK_SEQ_NO;
		sd["CAR_NO"] = CAR_NO;
		sd["CAR_TYPE"] = CAR_TYPE;
		sd["DST_STOCK_CODE"] = DST_STOCK_CODE;
		sd["DL_POS"] = DL_POS;
		sd["TAP_NO"] = TAP_NO;
		sd["PONO"] = PONO;
		sd["ST_NO"] = ST_NO;
		sd["LOOP_COUNT"] = nLoopCount;

		//ZCSJ������֯
		vector<string> ZCSJValues;
		for (int i = 0; i < nLoopCount; ++i)
		{
			ZCSJValues = StringHelper::ToVector<string>(kValues[10+i], const_cast<char*>("#"), static_cast<int>(strlen("#")));
			log.Info()<<"\t Index in loop =  "<<i<<" : ";
			
			sd["HCP412_DETAIL"][i]["STOCK_PLACE_CODE"] = ZCSJValues[0];
			log.Info()<<"  STOCK_PLACE_CODE = "<<ZCSJValues[0];

			sd["HCP412_DETAIL"][i]["MAT_CODE"] = ZCSJValues[1];
			log.Info()<<"  STOCK_PLACE_CODE = "<<ZCSJValues[1];

			sd["HCP412_DETAIL"][i]["COMP_CODE"] = ZCSJValues[2];
			log.Info()<<"  STOCK_PLACE_CODE = "<<ZCSJValues[2];

			sd["HCP412_DETAIL"][i]["WGT"] = ZCSJValues[3];
			log.Info()<<"  WGT = "<<ZCSJValues[3]<<endl;
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
