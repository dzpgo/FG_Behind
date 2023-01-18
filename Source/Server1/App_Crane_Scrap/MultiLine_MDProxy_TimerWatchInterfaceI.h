#ifndef __MultiLine_MDProxy_TimerWatchInterfaceI__
#define __MultiLine_MDProxy_TimerWatchInterfaceI__

#include <imultilink/TimerWatch.h>
#include "CranePLCStatusBase.h"
#include <log4cplus/LOG.h>
#include "CraneMonitor.h"
#include "CranePLCOrderBase.h"
//#include <cstdlib>

namespace iPlature
{

namespace iMultiLink
{

class MultiLine_MDProxy_TimerWatchInterfaceI : virtual public TimerWatchInterface
{
public:

	MultiLine_MDProxy_TimerWatchInterfaceI(string theCraneNO);

    virtual void TimerWatch(const ::std::string&,
			    const ::iPlature::iMultiLink::MAPTAGVALUE&,
			    const Ice::Current&);


private:
	// ��������ֵ�Ļ�����
	IceUtil::Mutex m_mutexValue;

private:
	string myCraneNO;
	

public:
			//1���г�Scheduler����
			 const static  string SCHEDULER_NAME_CRANE_1;
			//2���г�Scheduler����
			 const static  string SCHEDULER_NAME_CRANE_2;	
			//3���г�Scheduler����
			 const static  string SCHEDULER_NAME_CRANE_3;	
			 //4���г�Scheduler����
			 const static  string SCHEDULER_NAME_CRANE_4;


			//PLC BadValue
			 const static  string PLC_BAD_VALUE;	

			 const static  double motor_RPM_X;
			 const static  double motor_VPM_X;
			 const static  double motor_acc_X;

			 const static  double motor_RPM_Y;
			 const static  double motor_VPM_Y;
			 const static  double motor_acc_Y;

public:
			static string getSchedulerName(string craneNO);


private:
			void Transform_AntiWave_AlarmList(unsigned int theVal, string craneNO);

			//����Tag
			void readCraneStop(long &theVal, string craneNO);


};

}

}

#endif
