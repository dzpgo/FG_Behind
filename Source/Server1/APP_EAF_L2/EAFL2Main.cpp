/*********************************************************************
*		
*  文      件:    EAFL2Main.cpp   		电炉L2电文接收程序
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
#include "MsgEU01.h"
#include "MsgEU02.h"

using namespace iXcomTCP2;
using namespace iPlature;
using namespace Monitor;


class APP_EAF_L2:public iPlature::P99Component
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
		LOG::doConfigure("APP_EAF_L2", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_EAF_L2");
		log.Info()<<"APP_EAF_L2:"<<endl;
		
		InitPowertranserData();

		//数据库连接
		CDataAccess::GetInstance()->Initialize();

		//EVtag事件触发 
		string logFileName = "APP_EAF_L2_EV";
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(logFileName);//实例化CWatchEventHandlerI对象，为事件主题创建一个servant
		this->subscribe("Tag/WatchWithDataTopic", watchEvent);

		//设定EVtag事件触发日志名
		//测试暂时屏蔽，正式版要放开
		/*string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";	*/	

		//测试用路径 ,正式版要屏蔽
		string logConfgFileFullName="D:\\iPlature\\conf\\App4Log.cfg";
		string logFilePath="D:\\iPlature\\log\\";	


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
		LOG log(__FUNCTION__,"APP_EAF_L2");

		 string functionName="APP_EAF_L2::HandleMessage()";

		log.Info()<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        data received                                                                                                                         "<<endl;
		log.Info()<<"****************************************************************************************************************************."<<endl; 		

		//pw转发给我
		ByteSeq receiver(ParamBuffer);
		string msgID;
		receiver>>msgID;
		log.Info()<<"msgID = "<<msgID<<endl;

		try
		{
			//电文号映射
			//新电炉L2计划电文：EU01---6200
			//老电炉L2计划电文：FU01---6600
			//废钢计划电文
			if (msgID == "6200" || msgID == "6600")
			{
				MsgEU01::getInstance()->HandleMessage(receiver, msgID);
			}
			//钢种变更通知电文
			//暂时取消
			/*if (msgID == "EU02")
			{
				MsgEU02::getInstance()->HandleMessage(receiver);
			}*/		
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
		arry.push_back("EU01");
		arry.push_back("EU02");
		arry.push_back("UE01");
		arry.push_back("UE02");

		arry.push_back("6200");
		arry.push_back("6250");
		arry.push_back("6251");

		arry.push_back("6600");
		arry.push_back("6650");
		arry.push_back("6651");


		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	/* 析构*/
	virtual ~APP_EAF_L2()
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

PACE_SERVER_INSTALL(APP_EAF_L2);