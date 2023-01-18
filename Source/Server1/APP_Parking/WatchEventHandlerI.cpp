#include "WatchEventHandlerI.h"
#include "MsgUL01.h"
#include "MsgUL02.h"
#include "EventGateHandler.h"
#include "MsgWG02.h"
#include "MsgWG03.h"
#include "EventOrderHandler.h"

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
	LOG log(__FUNCTION__, mLogFileName);

	try
	{
		mLogFileName = GetLogFileName(strEventName);

		if (strEventName == "EV_CRANE_UL01")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			//把mLogFileName传入对应处理参数，作为写入的日志名
			MsgUL01	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		if (strEventName == "EV_CRANE_UL02")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			//把mLogFileName传入对应处理参数，作为写入的日志名
			MsgUL02	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//模拟收到车辆到达门口道闸通知：车牌号,道闸编号
		if (strEventName == "EV_GATE_CAR_ARRIVE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			EventGateHandler	handler;
			handler.CarArriveGateHandler(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//模拟收到门口道闸抬杆通知：车牌号,道闸编号
		if (strEventName == "EV_GATE_CAR_ENTER")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			EventGateHandler	handler;
			handler.CarEnterGateHandler(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//指令模块发送的装车作业完成（最后一吊放下时）修改停车位状态表 
		//暂且和下面的  EV_ORDER_CAR_CAN_LEAVE  一起通知
		if (strEventName == "EV_ORDER_PARKING_WORK_STATUS")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			EventOrderHandler	handler;
			handler.OrderParkingWorkStatus(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//指令模块发送的车辆准许离开通知
		if (strEventName == "EV_ORDER_CAR_CAN_LEAVE")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			MsgWG02	handler;
			handler.HandleMessage(strValue, mLogFileName);
			log.Info()<<"End........................................................................................................................."<<endl;
		}

		//指令模块发送的料格启动作业通知
		if (strEventName == "EV_ORDER_GRID_WORK_START")
		{
			log.Info()<<"strEventName:" <<strEventName<<" strValue: "<<strValue<<endl;
			log.Info()<<"Start......................................................................................................................"<<endl;
			MsgWG03	handler;
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