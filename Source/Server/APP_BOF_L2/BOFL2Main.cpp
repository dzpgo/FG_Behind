/*********************************************************************
*		
*  文      件:    BOFL2Main.cpp   		转炉L2电文接收程序
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：电炉L2电文接收
*
*  版本历史		
*      1.0    2017-06-07    Zhangyuhong    新增
*********************************************************************/
#include "WatchEventHandlerI.h"
#include <pace/P99Component.h>
#include <iXcomTCP2.h>


#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>

#include "DataAccess.h"
#include "MsgBU01.h"

using namespace iXcomTCP2;
using namespace iPlature;
using namespace Monitor;


class APP_BOF_L2:public iPlature::P99Component
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
		LOG::doConfigure("APP_BOF_L2", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_BOF_L2");
		log.Info()<<"APP_BOF_L2:"<<endl;
		
		InitPowertranserData();

		//数据库连接
		CDataAccess::GetInstance()->Initialize();

		//EVtag事件触发 
		string logFileName = "APP_BOF_L2_EV";
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(logFileName);//实例化CWatchEventHandlerI对象，为事件主题创建一个servant
		this->subscribe("Tag/WatchWithDataTopic", watchEvent);

		//设定EVtag事件触发日志名
		string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";		
		LOG::doConfigure( logFileName,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);

	}

	/**********************************************************************
	*  概述: 接收电文并处理数据
	*  函数名： HandleMessage 
	*  返回值： Ice::ByteSeq	 	电文序列
	*  参数列表：	参数类型    					取值范围     		    描述
	*    ParamBuffer  :    [IN/OUT] const ByteSeq &	     		  接收到的电文seq
	*
	*  版本历史		
	*       1.0    2017-06-07  LuYongyu    新增
	*  
	**********************************************************************/
	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		LOG log(__FUNCTION__,"APP_BOF_L2");

		 string functionName="APP_BOF_L2::HandleMessage()";

		log.Info()<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        data received                                                                                                                         "<<endl;
		log.Info()<<"****************************************************************************************************************************."<<endl; 

		ByteSeq receiver(ParamBuffer);
		iXcomTCP2::stru_recvtext0 stRecvMsg;
		memcpy((char *)&stRecvMsg, (char *)&ParamBuffer[0], ParamBuffer.size());

		log.Info()<<"lineno="<<stRecvMsg.lineno<<endl;
		log.Info()<<"Tel. Received from XCOM-PCS OK!  data length="<< stRecvMsg.textlenth<<"byte ,msg id:"<<stRecvMsg.ctextno<<endl;

		ByteSeq data;		
		string msgID = stRecvMsg.ctextno;		
		log.Info()<<"msgID = "<<msgID<<endl;
		
		log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//电文内容长度=电文总长度-电文头-结束符
		//获取数据
		data<<stRecvMsg.textbuf;
		try
		{
			if (msgID == "BU01")
			{
				MsgBU01::getInstance()->HandleMessage(data);							
			}


/*
			if (msgID == "AP001")//电文号即自定义协议中的5位电文号  AP名  也就是转炉L2用过的协议中的AP名
			{
				//真正电文在应用头里，所以需要先解析应用头
				SmartData sd;
				sd = MsgSmartDataManager::InsRef().GetMsgSmartData(msgID);
				sd.readFrom(data);
				
				string telID = sd["MSGID"].toString();
				log.Info()<<"telID = "<<telID<<endl;

				if (telID == "BU01")
				{
					MsgBU01::getInstance()->HandleMessage(data);
				}				
			}
*/



		
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
		return	 receiver;
	}

	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		arry.push_back("AP001");
		arry.push_back("BU01");
		arry.push_back("UB01");
		arry.push_back("UB02");
		arry.push_back("UB03");
		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	/* 析构*/
	virtual ~APP_BOF_L2()
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

};

PACE_SERVER_INSTALL(APP_BOF_L2);