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
	// 加锁保护参数值
	IceUtil::Mutex::Lock lock(m_mutexValue);
	LOG log(__FUNCTION__, "APP_ORDER");	

	try
	{
		mLogFileName = GetLogFileName(strEventName);

		//负责生成 电炉 L3 计划指令
		if (strEventName == "EV_PARKING_CAR_ARRIVE_PK")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			EventParkingHandler	handler;
			handler.OrderCreateReqForL3EAFL2(strValue, mLogFileName);
			log.Info()<<"End......"<<endl;
		}


		//收到来自parking模块的车辆离开信号
		//1. L3的卸料车离开：检测质检标记->检测是否可以质检信号（tag点）  满足条件 更新EXE_ENABLE  =1 
		//2. L3的装车车离开：无事情做
		//3. （待定）EAF的装车车离开：采集电炉L2的 UACS_EAF_L2_PLAN_DETAIL表数据，发送tag：EV_EAFL2_SND_UE01点给EAF

		if (strEventName == "EV_PARKING_CAR_LEAVE_PK")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			
			log.Info()<<"End......"<<endl;
		}


		//负责生成 转炉L2计划指令生成
		//接收到来自RGV模块的tag点通知：rgv车辆到位：停车位号，车号
		if (strEventName == "EV_RGV_CAR_ARRIVE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......"<<endl;
			
			log.Info()<<"End......"<<endl;
		}


		//负责处理来自行车模块的指令状态变化通知
		//EV点：EV_CRANE_ORDER_CMD_STATUS   格式：指令号orderNO，执行次数序号cmdSeq，状态cmdStatus，当次作业量CurWeight
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
* 析构
*/
Monitor::CWatchEventHandlerI::~CWatchEventHandlerI(void)
{

}