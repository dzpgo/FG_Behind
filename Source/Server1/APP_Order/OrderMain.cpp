#include <pace/P99Component.h>
#include <pace/CycSchedule.h>
#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>

#include <iXcom-TCP2/iXcomDefine.h>
#include <iXcomTCP2.h>

#include "WatchEventHandlerI.h"
#include "DataAccess.h"

using namespace iPlature;
using namespace Monitor;

class APP_Order : public P99Component
{
public:
	void PostInitCall()
	{
		LOG::doConfigure("APP_Order", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_Order");
		log.Info()<<"APP_Order:"<<endl;
		//数据库连接
		CDataAccess::GetInstance()->Initialize();
		//初始化电文
		//InitPowertranserData();
		//监听tag事件
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI();//实例化CWatchEventHandlerI对象，为事件主题创建一个servant
		this->subscribe("Tag/WatchWithDataTopic", watchEvent);

		//设定接收L3电文日志名
		string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";		
		LOG::doConfigure( "APP_ORDER_EV_PARKING",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( "APP_ORDER_EV_CRANE",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( "APP_ORDER_EV_L3",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		
	}

	ByteSeq HandleMessage(const ByteSeq & ParamBuffer) //其他程序用时入的入口
	{
		LOG log(__FUNCTION__);
		ByteSeq ret;
		MsgNameArray_t arry;
		return ret;
	}


	/* 析构*/
	virtual ~APP_Order()
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

PACE_SERVER_INSTALL(APP_Order) //应用程序主入口传入参数为定义的类名