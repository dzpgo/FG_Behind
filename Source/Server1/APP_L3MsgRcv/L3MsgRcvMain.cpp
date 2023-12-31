/*********************************************************************
*		
*  文      件:    L3MsgRcv.cpp   		
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：L3电文接收
*
*  版本历史		
*      1.0    2017-06-07    Zhangyuhong    新增
*********************************************************************/
#include <pace/P99Component.h>
#include <iXcomTCP2.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
#include "DataAccess.h"
#include "MsgKIBH01.h"
#include "MsgKIBH02.h"
#include "MsgKIBH03.h"
#include "MsgKIBH04.h"
#include "MsgKIBH05.h"

using namespace iXcomTCP2;
using namespace iPlature;
using namespace Monitor;


class APP_L3MsgRcv:public iPlature::P99Component
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
		LOG::doConfigure("APP_L3MsgRcv", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_L3MsgRcv");
		log.Info()<<"APP_L3MsgRcv:"<<endl;
		
		InitPowertranserData();

		//数据库连接
		CDataAccess::GetInstance()->Initialize();

		logFileNameKIBH01 = "KIBH01";
		logFileNameKIBH02 = "KIBH02";
		logFileNameKIBH03 = "KIBH03";
		logFileNameKIBH04 = "KIBH04";
		logFileNameKIBH05 = "KIBH05";

		//设定接收L3电文日志名
		string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";		
		LOG::doConfigure( logFileNameKIBH01,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH02,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH03,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH04,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( logFileNameKIBH05,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
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
		LOG log(__FUNCTION__,"APP_L3MsgRcv");

		 string functionName="APP_L3MsgRcv::HandleMessage()";

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
			//废钢品名信息电文
			if (msgID == "KIBH01")
			{
				MsgKIBH01::getInstance()->HandleMessage(receiver, logFileNameKIBH01);
			}
			//堆场废钢品名与厂内品名对照关系电文
			else if (msgID == "KIBH02")
			{
				MsgKIBH02::getInstance()->HandleMessage(receiver, logFileNameKIBH02);
			}
			//堆场废钢品名与厂内品名对照关系电文
			else if (msgID == "KIBH03")
			{
				MsgKIBH03::getInstance()->HandleMessage(receiver, logFileNameKIBH03);
			}
			//堆场废钢品名与厂内品名对照关系电文
			else if (msgID == "KIBH04")
			{
				MsgKIBH04::getInstance()->HandleMessage(receiver, logFileNameKIBH04);
			}
			//堆场废钢品名与厂内品名对照关系电文
			else if (msgID == "KIBH05")
			{
				MsgKIBH05::getInstance()->HandleMessage(receiver, logFileNameKIBH05);
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
		return	 receiver;
	}

	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		arry.push_back("KIBH01");
		arry.push_back("KIBH02");
		arry.push_back("KIBH03");
		arry.push_back("KIBH04");
		arry.push_back("KIBH05");


		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	/* 析构*/
	virtual ~APP_L3MsgRcv()
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
		//电文对应的打印日志文件名
		string logFileNameKIBH01;
		string logFileNameKIBH02;
		string logFileNameKIBH03;
		string logFileNameKIBH04;
		string logFileNameKIBH05;

};

PACE_SERVER_INSTALL(APP_L3MsgRcv);