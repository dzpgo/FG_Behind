#include "WatchEventHandlerI.h"
#include "MsgUE01.h"
#include "MsgUE02.h"
#include "EventCarDistHandler.h"
#include "EventOrderZCSJHandler.h"

Monitor::CWatchEventHandlerI::CWatchEventHandlerI(string logFileName)
{
			mLogFileName = logFileName;
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
		//20220708 add
		//����ָ��ģ�鷢�͵���ʵ����֪ͨ
		//2����
		//1.���¼ƻ��ӱ����г�װ����������װ�ϸ�ţ� WMS�ķϸִ��� �� WMS�ķϸָ�����
		//2.�ϸ�L2����ʵ��
		if (strEventName == "EV_EAFL2_ORDER_ZCSJ")//tag�����ݸ�ʽ�����ٿ���һ��
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start....................................................................................................."<<endl;
			EventOrderZCSJHandler	handler;
			handler.OrderZCSJHandler(strValue, mLogFileName);
			log.Info()<<"End......................................................................................................"<<endl;
		}

		//�������Ի����EAF�ƻ����������֪ͨ
		//��ʽ�����ƻ���,�Ӽƻ���,������
		//�ѿ�ʼװ�����Ӽƻ����������ٱ��������
		if (strEventName == "EV_EAFL2_HMI_CAR_DIST")//�������Ի����EAF�ƻ����������֪ͨ
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................"<<endl;
			EventCarDistHandler	handler;
			handler.CarDistHandler(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................."<<endl;
		}

		//�յ�����parkingģ��ĳ����ϳ�֪ͨ
		//2����:
		//1.���¼ƻ��ӱ���status=2  �Ѿ���ʼ
		//2. ��ϸ�L2����װ���Ѿ���ʼ����
		if (strEventName == "EV_EAFL2_PARKING_CAR_ARRIVE")//
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start........................................................................................................"<<endl;
			EventCarDistHandler	handler;
			handler.CarArriveHandler(strValue, mLogFileName);
			log.Info()<<"End..........................................................................................................."<<endl;
		}

		if (strEventName == "EV_L3_EAF_ZC_WGT")//operid,netwgt
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start....................................................................................................."<<endl;
			EventOrderZCSJHandler	handler;
			handler.L3WgtHandler(strValue, mLogFileName);
			log.Info()<<"End......................................................................................................."<<endl;
		}
		

		
	}
	catch(...)
	{

	}
}

/*
* 
* ����
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}