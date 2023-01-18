#include "EventOrderHandler.h"
#include <log4cplus/LOG.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iXcomTCP2.h>
#include "DataAccess.h"
#include "MsgWG01.h"
#include "MsgWG02.h"


using namespace Monitor;
using namespace std;
using namespace iXcomTCP2;

EventOrderHandler::EventOrderHandler(void)
{
}

EventOrderHandler::~EventOrderHandler(void)
{
}

//道闸识别车牌号处理
void EventOrderHandler::OrderParkingWorkStatus(string strValue, string logFileName)
{
	LOG log("EventOrderHandler::OrderParkingWorkStatus",logFileName);
	try
	{
		log.Info()<<"start........."<<endl;

		//1.解析tag值字符串
		//EV格式：停车位号,状态号
		vector<string>kValues;
		kValues = StringHelper::ToVector<string>(strValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));
		if (kValues.size() < 2)
		{
			log.Info()<<"kValues size="<<kValues.size() <<",  NOT VALID,return......."<<endl;
			return;
		}
		string parkingNO = kValues[0];//停车位号
		string workStatus = kValues[1];//状态号 
		log.Info()<<" parkingNO = "<<parkingNO<<" , workStatus = "<<workStatus<<endl;

		//如果 状态号是 100  ，清空停车位状态表
		if (workStatus == "305")//归堆作业完成  初始化停车位状态表
		{
			log.Info()<<"XL 归堆完成，初始化停车位状态表，停车位号="<<parkingNO<<endl;
			SQL4Parking::InitParkingWorkStauts(parkingNO);
			return;
		}

		if (workStatus == "206")//装车作业完成  更新停车位状态表为206
		{
			log.Info()<<"ZC 装车完成，更新停车位状态表为206，停车位号="<<parkingNO<<endl;
			//通知 料格管理模块车辆可以离开 电文发送
			//strMsg = 停车位号,车号
			string carNO = "";
			SQL4Parking::SelCarNOByParkingNO(parkingNO, carNO);
			string strMsg = parkingNO + "," + carNO;
			MsgWG02	handler;
			handler.HandleMessage(strMsg, logFileName);

			//更新停车位状态表
			SQL4Parking::UpdParkingStatus(parkingNO, workStatus);
			
			return;
		}

		


	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
}




bool EventOrderHandler::EVTagSnd(string tagName, string tagValue)
{
	string functionName="EventOrderHandler :: EVTagSnd()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;
	try
	{
		iPlature::TAGVALUEMAP tagPairs;
		log.Info()<<"eventPut tagName="<<tagName<<"    tagValue="<<tagValue<<endl;
		Tag::GetInst().EventPut(tagPairs,tagName,tagValue);
		ret=true;
		return ret;
	}
	catch(...)
	{
		log.Debug()<<"EVTagSnd  error..........."<<endl;
	}
	return ret;
}
