#include "WatchEventHandlerI.h"
#include "MsgUL01.h"
#include "MsgUL02.h"
#include "EventGateHandler.h"
#include "MsgWG02.h"
#include "MsgWG03.h"
#include "EventOrderHandler.h"

Monitor::CWatchEventHandlerI::CWatchEventHandlerI()
{
}

void Monitor::CWatchEventHandlerI::EventWatchWithData(const iPlature::TAGVALUEMAP& tagValueMap,
																											  const std::string& strEventName,
																											  const std::string& strValue,
																											  const Ice::Current&)
{
	// ������������ֵ
	IceUtil::Mutex::Lock lock(m_mutexValue);
	LOG log(__FUNCTION__, mLogFileName);

	try
	{
		mLogFileName = GetLogFileName(strEventName);

		if (strEventName == "EV_CRANE_UL01")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			//��mLogFileName�����Ӧ�����������Ϊд�����־��
			MsgUL01	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		if (strEventName == "EV_CRANE_UL02")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			//��mLogFileName�����Ӧ�����������Ϊд�����־��
			MsgUL02	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//ģ���յ����������ſڵ�բ֪ͨ�����ƺ�,��բ���
		if (strEventName == "EV_GATE_CAR_ARRIVE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			EventGateHandler	handler;
			handler.CarArriveGateHandler(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//ģ���յ��ſڵ�բ̧��֪ͨ�����ƺ�,��բ���
		if (strEventName == "EV_GATE_CAR_ENTER")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			EventGateHandler	handler;
			handler.CarEnterGateHandler(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//ָ��ģ�鷢�͵�װ����ҵ��ɣ����һ������ʱ���޸�ͣ��λ״̬�� 
		//���Һ������  EV_ORDER_CAR_CAN_LEAVE  һ��֪ͨ
		if (strEventName == "EV_ORDER_PARKING_WORK_STATUS")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			EventOrderHandler	handler;
			handler.OrderParkingWorkStatus(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//ָ��ģ�鷢�͵ĳ���׼���뿪֪ͨ
		if (strEventName == "EV_ORDER_CAR_CAN_LEAVE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			MsgWG02	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//ָ��ģ�鷢�͵��ϸ�������ҵ֪ͨ
		if (strEventName == "EV_ORDER_GRID_WORK_START")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			MsgWG03	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}


	}
	catch(...)
	{

	}
}


string Monitor::CWatchEventHandlerI::GetLogFileName(string tagName)
{
	string logFileName = "";
	if (tagName.find("EV_CRANE") != string::npos)
	{
		logFileName = "APP_PARKING_EV_CRANE";
	}
	else if (tagName.find("EV_GATE") != string::npos)
	{
		logFileName = "APP_PARKING_EV_GATE";
	}
	else if (tagName.find("EV_GRID") != string::npos)
	{
		logFileName = "APP_PARKING_EV_GRID";
	}
	else if (tagName.find("EV_ORDER") != string::npos)
	{
		logFileName = "APP_PARKING_EV_ORDER";
	}
	else
	{
		logFileName = "APP_PARKING";
	}
	return logFileName;
}



/*
* 
* ����
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}