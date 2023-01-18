#include "WatchEventHandlerI.h"
#include "MsgU1.h"

Monitor::CWatchEventHandlerI::CWatchEventHandlerI()
{
}

void Monitor::CWatchEventHandlerI::EventWatchWithData(const iPlature::TAGVALUEMAP& tagValueMap,
																										  const std::string& strEventName,
																										  const std::string& strValue,
																										  const Ice::Current&)
{
	// 加锁保护参数值
	IceUtil::Mutex::Lock lock(m_mutexValue);
	LOG log(__FUNCTION__, "APP_SAFE_PLC_EV");	

	try
	{
		//mLogFileName = GetLogFileName(strEventName);

		if (strEventName == "EV_SAFE_PLC_E_GRID")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			vector<string> vecSafePlcEValue;
			vecSafePlcEValue= StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

			if (vecSafePlcEValue.size() < 24)
			{
				log.Info()<<"EV_SAFE_PLC_E_GRID  tagValue  numbers < 24， return false...................."<<endl;
				return;
			}

			vector<long> vecSafePlcEValue2;
			vector<string>::iterator itor;
			for (itor = vecSafePlcEValue.begin(); itor != vecSafePlcEValue.end(); itor ++)
			{
				long longValue = StringHelper::ToNumber<long>(*itor);
				vecSafePlcEValue2.push_back(longValue);
			}

			MsgU1::getInstance()->SendOutMessage(vecSafePlcEValue2);

		}
	}
	catch(...)
	{

	}
}


string Monitor::CWatchEventHandlerI::GetLogFileName(string tagName)
{
	string logFileName = "APP_SAFE_PLC_EV";
	return logFileName;
}






/*
* 
* 析构
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}