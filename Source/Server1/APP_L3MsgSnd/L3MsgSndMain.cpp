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

class APP_L3MsgSnd : public P99Component
{
    public:
    void PostInitCall()
    {
		LOG::doConfigure("APP_L3MsgSnd", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_L3MsgSnd");
		log.Info()<<"APP_L3MsgSnd:"<<endl;
        //数据库连接
        CDataAccess::GetInstance()->Initialize();
        //初始化电文
        InitPowertranserData();
        //监听tag事件
		string logFileName = "APP_L3MsgSnd";
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(logFileName);//实例化CWatchEventHandlerI对象，为事件主题创建一个servant
        this->subscribe("Tag/WatchWithDataTopic", watchEvent);
       
    }

    ByteSeq HandleMessage(const ByteSeq & ParamBuffer) //其他程序用时入的入口
    {
        LOG log(__FUNCTION__);
        ByteSeq ret;
        MsgNameArray_t arry;
		return ret;
    }

    //初始化poerTranser
    void InitPowertranserData()
    {
		LOG log(__FUNCTION__);
        MsgNameArray_t arry;

        arry.push_back("HCP401"); //RGV车号与槽号对应关系
        arry.push_back("HCP411"); //单品种废钢进出二炼钢废钢堆场装卸完成信息
        arry.push_back("HCP412"); //废钢装槽装车信息（吊运实绩）
        arry.push_back("HCP421"); //二炼钢金属料堆场即时库存信息

        MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
    }

	/* 析构*/
	virtual ~APP_L3MsgSnd()
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

PACE_SERVER_INSTALL(APP_L3MsgSnd) //应用程序主入口传入参数为定义的类名