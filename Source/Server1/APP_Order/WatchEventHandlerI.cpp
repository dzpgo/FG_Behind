#include "WatchEventHandlerI.h"
#include "EventParkingHandler.h"
#include "EventCraneHandler.h"

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
	LOG log(__FUNCTION__, "APP_ORDER");	

	try
	{
		mLogFileName = GetLogFileName(strEventName);

		//�������� ��¯ L3 �ƻ�ָ��
		if (strEventName == "EV_PARKING_CAR_ARRIVE_PK")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			EventParkingHandler	handler;
			handler.OrderCreateReqForL3EAFL2(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}


		//�յ�����parkingģ��ĳ����뿪�ź�
		//1. L3��ж�ϳ��뿪������ʼ���->����Ƿ�����ʼ��źţ�tag�㣩  �������� ����EXE_ENABLE  =1 
		//2. L3��װ�����뿪����������
		//3. ��������EAF��װ�����뿪���ɼ���¯L2�� UACS_EAF_L2_PLAN_DETAIL�����ݣ�����tag��EV_EAFL2_SND_UE01���EAF

		if (strEventName == "EV_PARKING_CAR_LEAVE_PK")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			
			log.Info()<<"End......"<<endl;
		}


		//�������� ת¯L2�ƻ�ָ������
		//���յ�����RGVģ���tag��֪ͨ��rgv������λ��ͣ��λ�ţ�����
		if (strEventName == "EV_RGV_CAR_ARRIVE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			
			log.Info()<<"End......"<<endl;
		}


		//�����������г�ģ���ָ��״̬�仯֪ͨ
		//EV�㣺EV_CRANE_ORDER_CMD_STATUS   ��ʽ��ָ���orderNO��ִ�д������cmdSeq��״̬cmdStatus��������ҵ��CurWeight
		if (strEventName == "EV_CRANE_ORDER_CMD_STATUS")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			EventCraneHandler handler;
			handler.OrderCmdStatusRcv(strValue, mLogFileName);

			log.Info()<<"End......"<<endl;
		}


		
	}
	catch(...)
	{

	}
}


string Monitor::CWatchEventHandlerI::GetLogFileName(string tagName)
{
	string logFileName = "";
	if (tagName.find("EV_PARKING") != string::npos)
	{
		logFileName = "APP_ORDER_EV_PARKING";
	}
	else if (tagName.find("EV_CRANE") != string::npos)
	{
		logFileName = "APP_ORDER_EV_CRANE";
	}
	else if (tagName.find("EV_L3") != string::npos)
	{
		logFileName = "APP_ORDER_EV_L3";
	}
	else
	{
		logFileName = "APP_ORDER";
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