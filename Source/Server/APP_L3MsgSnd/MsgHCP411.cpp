#include "MsgHCP411.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "SQL4L3.h"

using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

MsgHCP411::MsgHCP411(void)
{
	m_strMsgId = "HCP411";
}

MsgHCP411::~MsgHCP411(void)
{

}

void MsgHCP411::HandleMessage(const string strValue, const string logFileName)
{
	LOG log("MsgHCP411::HandleMessage",logFileName);
	try
	{
		log.Info()<<"send tel data is ready to start........................................................"<<endl;
		// ��ȡpowertrans���Ľṹ
		SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(m_strMsgId);

		//strValue��ʽ��
		//OPERATE_FLAG, WORK_SEQ_NO,  WORK_TYPE��WORK_STATUS,  WORK_TIME
		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 5)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}

		string OPERATE_FLAG = kValues[0];//������־
		string WORK_SEQ_NO = kValues[1];//��ˮ��
		string WORK_TYPE = kValues[2];//��ҵ���ͣ�1��ZC  2��XL
		string WORK_STATUS = kValues[3];//��ҵ״̬�� 1�������볡  2�������ϸ�  3�������뿪  4����ѿ�ʼ   5����ѽ���
		string WORK_TIME = kValues[4];//

		log.Info()<<"OPERATE_FLAG = "<<OPERATE_FLAG<<endl;
		log.Info()<<"WORK_SEQ_NO = "<<WORK_SEQ_NO<<endl;
		log.Info()<<"WORK_TYPE = "<<WORK_TYPE<<endl;
		log.Info()<<"WORK_STATUS = "<<WORK_STATUS<<endl;
		log.Info()<<"WORK_TIME = "<<WORK_TIME<<endl;

		//��UACS_L3_MAT_IN_OUT_INFO���е�PLAN_STATUS���и���
		string planStatus = GetPlanStatus(WORK_TYPE, WORK_STATUS);
		if (!planStatus.empty())
		{
			log.Info()<<"update L3PLAN STATUS.................."<<endl;
			//���±� PLAN_STATUS�ֶ�
			SQL4L3::UpdL3PLanStatus(WORK_SEQ_NO, planStatus);
		}

		//������ ��������
		if (kValues.size() == 6)
		{
			long craneWgt = StringHelper::ToNumber<long>( kValues[5] );
			if (WORK_TYPE == "1") // װ������  ���¶�Ӧ�����ֶ�
			{
				log.Info()<<"update L3PLAN CraneWgtZC.................."<<endl;
				SQL4L3::UpdL3PlanCraneWgtZC(WORK_SEQ_NO, craneWgt);
			}
			if (WORK_TYPE == "2") // ж������  ���¶�Ӧ�����ֶ�
			{
				log.Info()<<"update L3PLAN CraneWgtXL.................."<<endl;
				SQL4L3::UpdL3PlanCraneWgtXL(WORK_SEQ_NO, craneWgt);
			}

		}

		//ֻ�� 1  2  3  4  5  ״̬����Ҫ��L3���͵���֪ͨ��
		if (WORK_STATUS != "1" && WORK_STATUS != "2" && WORK_STATUS != "3" && WORK_STATUS != "4" && WORK_STATUS != "5")
		{
			log.Info()<<"WORK_STATUS = "<<WORK_STATUS<<" , NOT 1 or 2 or 3 or 4 or 5,  no need to send HCP411 to L3..........return..........."<<endl;
			return;
		}

		//��֯smartdata����
		sd["OPERATE_FLAG"] = OPERATE_FLAG;
		sd["WORK_SEQ_NO"] = WORK_SEQ_NO;
		sd["WORK_TYPE"] = WORK_TYPE;
		sd["WORK_STATUS"] = WORK_STATUS;
		sd["WORK_TIME"] = WORK_TIME;
		
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


string MsgHCP411::GetPlanStatus(string workType, string workStaus)
{
	LOG log("MsgHCP411::GetPlanStatus", AUTO_CATCH_PID);
	string planStatus = "";
	try
	{
		if (workType == "1")
		{
			if (workStaus == "1")
			{
				planStatus = "2";//װ����ʼ
			}
			if (workStaus == "F")
			{
				planStatus = "3";//װ������
			}
		}

		if (workType == "2")
		{
			if (workStaus == "1")
			{
				planStatus == "4";//ж�Ͽ�ʼ
			}
			if (workStaus == "5")
			{
				planStatus == "5";//ж�Ͻ���
			}
		}
		

	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}

	return planStatus;
}
