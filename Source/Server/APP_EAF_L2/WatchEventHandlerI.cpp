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
	// 加锁保护参数值
	IceUtil::Mutex::Lock lock(m_mutexValue);
	LOG log(__FUNCTION__, mLogFileName);

	try
	{
		//20220708 add
		//接收指令模块发送吊运实绩的通知
		//2件事
		//1.更新计划子表中行车装料重量，所装料格号， WMS的废钢代码 ， WMS的废钢钢制码
		//2.废钢L2发送实绩
		if (strEventName == "EV_EAFL2_ORDER_ZCSJ")//tag点数据格式后续再考虑一下
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start....................................................................................................."<<endl;
			EventOrderZCSJHandler	handler;
			handler.OrderZCSJHandler(strValue, mLogFileName);
			log.Info()<<"End......................................................................................................"<<endl;
		}

		//接收来自画面的EAF计划车辆分配的通知
		//格式：主计划号,子计划号,车辆号
		//已开始装车的子计划，不允许再变更车辆号
		if (strEventName == "EV_EAFL2_HMI_CAR_DIST")//接收来自画面的EAF计划车辆分配的通知
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................"<<endl;
			EventCarDistHandler	handler;
			handler.CarDistHandler(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................."<<endl;
		}

		//收到来自parking模块的车到料场通知
		//2件事:
		//1.更新计划子表中status=2  已经开始
		//2. 向废钢L2发送装车已经开始电文
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
* 析构
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}