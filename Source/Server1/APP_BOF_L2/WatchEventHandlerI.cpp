#include "WatchEventHandlerI.h"
#include "MsgUB01.h"
#include "MsgUB02.h"

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
		if (strEventName == "EV_BOFL2_SND_UB01")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			//��mLogFileName�����Ӧ�����������Ϊд�����־��
			MsgUB01	handler = MsgUB01("UB01");
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_BOFL2_SND_UB02")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			//��mLogFileName�����Ӧ�����������Ϊд�����־��
			MsgUB02	handler = MsgUB02("UB02");
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
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