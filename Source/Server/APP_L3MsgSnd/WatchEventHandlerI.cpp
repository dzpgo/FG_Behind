#include "WatchEventHandlerI.h"
#include "MsgHCP401.h"
#include "MsgHCP411.h"
#include "MsgHCP412.h"
#include "MsgHCP421.h"

Monitor::CWatchEventHandlerI::CWatchEventHandlerI(string logFileName)
{
	mLogFileName = logFileName;
}

void Monitor::CWatchEventHandlerI::EventWatchWithData(const iPlature::TAGVALUEMAP& tagValueMap,
																											  const std::string& strEventName,
																											  const std::string& strValue,
																											  const Ice::Current&)
{
	// 加锁保护参数值
	IceUtil::Mutex::Lock lock(m_mutexValue);
	LOG log(__FUNCTION__, mLogFileName);

	log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;

	try
	{
		if (strEventName == "EV_L3MSG_SND_HCP401")
		{
			log.Info()<<"Start......"<<endl;
			MsgHCP401	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_L3MSG_SND_HCP411")
		{
			log.Info()<<"Start......"<<endl;
			MsgHCP411	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_L3MSG_SND_HCP412")
		{
			log.Info()<<"Start......"<<endl;
			MsgHCP412	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_L3MSG_SND_HCP421")
		{
			log.Info()<<"Start......"<<endl;
			MsgHCP421	handler;
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
* 析构
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}