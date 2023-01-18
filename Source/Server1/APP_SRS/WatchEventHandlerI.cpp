#include "WatchEventHandlerI.h"
#include "MsgUL01.h"
#include "MsgUL02.h"

Monitor::CWatchEventHandlerI::CWatchEventHandlerI(string theCraneNO, string logFileName)
{
	craneNO = theCraneNO;
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

	try
	{
		//strEventName格式： EV_CRANE_E1_UL01   EV_CRANE_E1_UL02
		if (strEventName.find("UL01") == string::npos && strEventName.find("UL02") == string::npos)
		{
			return;
		}
		string craneNOInTag = strEventName.substr(9, 2);
		if (craneNO != craneNOInTag)
		{
			return;
		}

		log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;

		string telIDInTag = strEventName.substr(12, 4);

		if (telIDInTag == "UL01")
		{
			log.Info()<<"Start......................................................................................................................"<<endl;
			MsgUL01	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		if (telIDInTag == "UL02")
		{
			log.Info()<<"Start......................................................................................................................"<<endl;
			MsgUL02	handler;
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
* 析构
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}