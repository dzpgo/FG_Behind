#include "WatchEventHandlerI.h"
#include "MsgWWRR01.h"
#include "MsgWWRR02.h"
#include "MsgWWRR03.h"
#include "MsgWWRR04.h"
#include "MsgWWRR05.h"

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
	LOG log(__FUNCTION__);
	
	

	try
	{
		if (strEventName == "EV_RGV_WWRR01")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			//把mLogFileName传入对应处理参数，作为写入的日志名
			MsgWWRR01	handler = MsgWWRR01("WWRR01");
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_RGV_WWRR02")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			//把mLogFileName传入对应处理参数，作为写入的日志名
			MsgWWRR02	handler = MsgWWRR02("WWRR02");
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_RGV_WWRR03")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			//把mLogFileName传入对应处理参数，作为写入的日志名
			MsgWWRR03	handler = MsgWWRR03("WWRR03");
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_RGV_WWRR04")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			//把mLogFileName传入对应处理参数，作为写入的日志名
			MsgWWRR04	handler = MsgWWRR04("WWRR04");
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}

		if (strEventName == "EV_RGV_WWRR05")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			//把mLogFileName传入对应处理参数，作为写入的日志名
			MsgWWRR05	handler = MsgWWRR05("WWRR05");
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