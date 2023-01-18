#include "EventOrderHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "MsgWG01.h"
#include "MsgWG02.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

EventOrderHandler::EventOrderHandler(void)
{
}

EventOrderHandler::~EventOrderHandler(void)
{
}

//��բʶ���ƺŴ���
void EventOrderHandler::OrderParkingWorkStatus(string strValue, string logFileName)
{
	LOG log("EventOrderHandler::OrderParkingWorkStatus",logFileName);
	try
	{
		log.Info()<<"start........."<<endl;

		//1.����tagֵ�ַ���
		//EV��ʽ��ͣ��λ��,״̬��
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string parkingNO = kValues[0];//ͣ��λ��
		string workStatus = kValues[1];//״̬�� 
		log.Info()<<" parkingNO = "<<parkingNO<<" , workStatus = "<<workStatus<<endl;

		//��� ״̬���� 100  �����ͣ��λ״̬��
		if (workStatus == "305")//�����ҵ���  ��ʼ��ͣ��λ״̬��
		{
			log.Info()<<"XL �����ɣ���ʼ��ͣ��λ״̬��ͣ��λ��="<<parkingNO<<endl;
			SQL4Parking::InitParkingWorkStauts(parkingNO);
			return;
		}

		if (workStatus == "206")//װ����ҵ���  ����ͣ��λ״̬��Ϊ206
		{
			log.Info()<<"ZC װ����ɣ�����ͣ��λ״̬��Ϊ206��ͣ��λ��="<<parkingNO<<endl;
			//֪ͨ �ϸ����ģ�鳵�������뿪 ���ķ���
			//strMsg = ͣ��λ��,����
			string carNO = "";
			SQL4Parking::SelCarNOByParkingNO(parkingNO, carNO);
			string strMsg = parkingNO + "," + carNO;
			MsgWG02	handler;
			handler.HandleMessage(strMsg, logFileName);

			//����ͣ��λ״̬��
			SQL4Parking::UpdParkingStatus(parkingNO, workStatus);
			
			return;
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
}




bool EventOrderHandler::EVTagSnd(string tagName, string tagValue)
{
	string functionName="EventOrderHandler :: EVTagSnd()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		iPlature::TAGVALUEMAP tagPairs;
		log.Info()<<"eventPut tagName="<<tagName<<"    tagValue="<<tagValue<<endl;
		Tag::GetInst().EventPut(tagPairs,tagName,tagValue);
		ret=true;
		return ret;
	}
	catch(...)
	{
		log.Debug()<<"EVTagSnd  error..........."<<endl;
	}
	return ret;
}
