#pragma once

#include <iostream>
#include <sstream>
#include <pace/Proxy.h>
#include <pace/ProxyWrapper.h>
#include <alarm/Alarm.h>

#include <log4cplus/LOG.h>

using namespace std;

namespace iPlature{

const int ALARM_FATAL_ERROR = 1;
const int ALARM_NORMAL_ERROR = 2;
const int ALARM_FATAL_WARN = 3;
const int ALARM_NORMAL_WARN = 4;
const int ALARM_OPERATION = 5;
const int ALARM_INFO = 6;

class AlarmWrapper
{
public:
	 typedef AlarmWrapper& (*Manipulator)(AlarmWrapper&);
	 typedef std::vector<std::string> MsgSeq;

	 AlarmWrapper(const std::string& name);
	 AlarmWrapper();
	~AlarmWrapper(void);

	static void initialize();
	static void destroy();

	template<typename T> 
	AlarmWrapper& operator <<(const T& t)
	{
		std::ostringstream o;
		o << t;
		m_strMsgVec.push_back(o.str());
		return *this;
	}

	AlarmWrapper& operator<<(Manipulator aw)
	{
		return (*aw)(*this);
	}

	int AlarmLevel(int nLogID, string strModule, MsgSeq strMsgVec);
	//int AlarmFatalError(std::string strMsg);
	//int AlarmNormalError(std::string strMsg);
	//int AlarmFatalWarn(std::string strMsg);
	//int AlarmNormalWarn(std::string strMsg);
	//int AlarmOperation(std::string strMsg);
	//int AlarmInfo(std::string strMsg);
	int AlarmMsg(int nLogID,MsgSeq strMsgVec);

	//AlarmWrapper& FatalError();
	//AlarmWrapper& NormalError();
	//AlarmWrapper& FatalWarn();
	//AlarmWrapper& NormalWarn();
	//AlarmWrapper& Operation();
	//AlarmWrapper& Info();
	AlarmWrapper& AlarmMsg(int nLogID);

	AlarmWrapper& flush();

private:
	static iPlature::AlarmPrx _alarm ;
	//int m_nLevel;
	int m_nLogID;
	std::string m_modulename;
	MsgSeq m_strMsgVec;

};

}

namespace std
{
	iPlature::AlarmWrapper& endl(iPlature::AlarmWrapper&);
}


