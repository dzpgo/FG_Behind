#include <pace/P99Component.h>
#include <pace/CycSchedule.h>
#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>

#include <iXcom-TCP2/iXcomDefine.h>
#include <iXcomTCP2.h>

#include "MsgLU01.h"
#include "MsgLU02.h"
#include "MsgGW01.h"
#include "WatchEventHandlerI.h"
#include "DataAccess.h"
#include "UDPMsgDef.h"

class APP_Parking: public P99Component
{
public:
	/**********************************************************************
	*  概述: 程序入口
	*  函数名： PostInitCall 
	*  返回值： void	 	
	*  参数列表：	参数类型    					取值范围     		    描述
	*
	*  版本历史		
	*       1.0    2017-06-07  LuYongyu    新增
	*  
	**********************************************************************/
	void PostInitCall()
	{
			LOG::doConfigure("APP_PARKING", ROOT_CONFIG);
			LOG log(__FUNCTION__,"APP_PARKING");
			log.Info()<<"APP_Parking:"<<endl;	

			//电文初始化
			InitPowertranserData();
			//数据库连接
			CDataAccess::GetInstance()->Initialize();

			//EVtag事件触发 			
			WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI();//实例化CWatchEventHandlerI对象，为事件主题创建一个servant
			this->subscribe("Tag/WatchWithDataTopic", watchEvent);

			//设定接收EVtag时日志名
			string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
			string logFilePath="/iPlature/log/";		
			LOG::doConfigure( "APP_PARKING_EV_CRANE",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//来自行车控制系统的通知
			LOG::doConfigure( "APP_PARKING_EV_GATE",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//来自道闸控制系统的通知
			LOG::doConfigure( "APP_PARKING_EV_GRID",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//来自料格管理系统的通知
			LOG::doConfigure( "APP_PARKING_EV_ORDER",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//来自指令模块系统的通知
	}

	//电文初始化
	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		//SRS电文 接收 与发送
		arry.push_back("LU01");
		arry.push_back("LU02");

		arry.push_back("GW01");
		
		//json格式定义的标记
		//库区扫描结果数据解析
		arry.push_back("LU01SD");
		//车辆扫描结果数据解析
		arry.push_back("LU02SD");

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		LOG log(__FUNCTION__,"APP_Parking");

		string functionName="APP_Parking::HandleMessage()";

		log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        data received                                                                                                                                         "<<endl;
		log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

		ByteSeq receiver(ParamBuffer);
		log.DebugHex((void*)&ParamBuffer.front(),(int)ParamBuffer.size());
        iXcomTCP2::stru_recvtext0 stRecvMsg;
        memcpy((char *)&stRecvMsg, (char *)&ParamBuffer[0], ParamBuffer.size());             

        log.Info()<<"lineno="<<stRecvMsg.lineno<<endl;
        log.Info()<<"Tel. Received from XCOM-PCS OK!  数据长度="<< stRecvMsg.textlenth<<"byte ,msg id端口号:"<<stRecvMsg.ctextno<<endl;
        log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//电文内容长度 = 电文总长度-电文头-结束符

		ByteSeq teleBuffer;
		teleBuffer<<stRecvMsg.textbuf;

		try
		{	
			//stRecvMsg.textbuf格式 ：
			//激光电文：LU01#json_data_string
			//料格管理通知电文: GW01,停车位号,车号,到达离开标记

			MY_UDP_MSG udpMsg;
			const int lenMsgId = 4;

			memset(&udpMsg, 0, sizeof(MY_UDP_MSG));

			//UDP电文电文号长度
			udpMsg.lenMsgId = lenMsgId;
			memcpy(udpMsg.msgId, stRecvMsg.textbuf, lenMsgId); 
			memcpy(udpMsg.msgData, stRecvMsg.textbuf, stRecvMsg.textlenth);

			// MY_UDP_MSG 2 SmartData
			Ice::StringSeq vecString;
			int index = 0;
			SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(string((char*)udpMsg.msgId));

			string mestext = stRecvMsg.textbuf;    //电文内容，#分隔符数据
			string splitStr = "#";

			string strMsgID = (char*)udpMsg.msgId;
			//接收激光电文格式解析：电文号#JSON格式字符串
			if (strMsgID.find("LU") != string::npos)
			{
				splitStr = "#";
			}
			//接收料格电文格式解析：电文号,实际字段
			if (strMsgID.find("GW") != string::npos)
			{
				splitStr = ",";
			}
			vecString = StringHelper::ToVector<string>(mestext, const_cast<char*>(splitStr.c_str()), static_cast<int>(strlen(splitStr.c_str())));
			UdpUtil::wrapSmartData(vecString, sd, index);

			// process smartdata
			if (!strcmp((char*)udpMsg.msgId, "LU01"))
			{
				//库区扫描
				log.Debug()<<"Receive LU01"<<endl;
				MsgLU01::getInstance()->setMsgID("LU01");
				MsgLU01::getInstance()->HandleMessage(sd);
			}
			if (!strcmp((char*)udpMsg.msgId, "LU02"))
			{
				//车辆扫描
				log.Debug()<<"Receive LU02"<<endl;
				MsgLU02::getInstance()->setMsgID("LU02");
				MsgLU02::getInstance()->HandleMessage(sd);
			}
			if (!strcmp((char*)udpMsg.msgId, "GW01"))
			{
				//料格管理系统：车辆到达/离开通知电文
				log.Debug()<<"Receive GW01"<<endl;
				MsgGW01::getInstance()->setMsgID("GW01");
				MsgGW01::getInstance()->HandleMessage(sd);
			}
		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch (...)
		{
			
		}

		LOG::remove("PARKING_HANDLE_MESSAGE");
		return receiver;
	}


	/* 析构*/
	virtual ~APP_Parking()
	{
		try
		{
			//断开数据库连接
			CDataAccess::GetInstance()->UnInitialize();
		}
		catch(...)
		{
		}
	}

private:
		//string strJson;

	


};

PACE_SERVER_INSTALL(APP_Parking);