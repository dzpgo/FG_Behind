#include <pace/P99Component.h>
#include <pace/CycSchedule.h>
#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>

#include <iXcom-TCP2/iXcomDefine.h>
#include <iXcomTCP2.h>

#include "MsgS1.h"
#include "WatchEventHandlerI.h"
#include "DataAccess.h"
#include "UDPMsgDef.h"

#include "SafePLC4EAFYardBase.h"

using namespace Monitor;

class APP_SAFE_PLC: public P99Component
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
			LOG::doConfigure("APP_SAFE_PLC", ROOT_CONFIG);
			LOG log(__FUNCTION__,"APP_SAFE_PLC");
			log.Info()<<"APP_SAFE_PLC :"<<endl;	

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
			LOG::doConfigure( "APP_SAFE_PLC_EV",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//来自行车控制系统的通知
	}

	//电文初始化
	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		//SRS电文 接收 与发送
		arry.push_back("S1");
		arry.push_back("S2");

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		LOG log(__FUNCTION__,"APP_SAFE_PLC");

		string functionName="APP_SAFE_PLC::HandleMessage()";

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
			byte btMsgID[2];

			MY_UDP_MSG udpMsg;

			memset(&udpMsg, 0, sizeof(MY_UDP_MSG));
			memcpy(udpMsg.msgData, stRecvMsg.textbuf, stRecvMsg.textlenth);

			//安全PLC采用的是宝信 PLC,所以收到的电文很奇怪, 
			//电文号是字符的话, 会多一个NULL（ascii码对应0，显示电文日志里是 .），所以需要取指定位置的字节
			//e.g.     53-00-31-00 00-00-00-00 00-00-00-00 00-00-00-00   S.1.............
			btMsgID[0] = udpMsg.msgData[0];
			btMsgID[1] = udpMsg.msgData[2];

			string msgID = string((char*)btMsgID);
			log.Info()<<"msgID = "<<msgID<<endl;

			StringHelper::Trim(msgID);

			if (msgID == "S1")
			{
				log.Debug()<<"Receive S1"<<endl;
				MsgS1::getInstance()->HandleMessage(teleBuffer, safePLC4EAFYard_Last);
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

		LOG::remove("APP_SAFE_PLC");
		return receiver;
	}


	/* 析构*/
	virtual ~APP_SAFE_PLC()
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

		SafePLC4EAFYardBase safePLC4EAFYard_Last;

	


};

PACE_SERVER_INSTALL(APP_SAFE_PLC);