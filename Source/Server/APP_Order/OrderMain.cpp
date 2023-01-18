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
		//���ݿ�����
		CDataAccess::GetInstance()->Initialize();
		//��ʼ������
		//InitPowertranserData();
		//����tag�¼�
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI();//ʵ����CWatchEventHandlerI����Ϊ�¼����ⴴ��һ��servant
		this->subscribe("Tag/WatchWithDataTopic", watchEvent);

		//�趨����L3������־��
		string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";		
		LOG::doConfigure( "APP_ORDER_EV_PARKING",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( "APP_ORDER_EV_CRANE",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		LOG::doConfigure( "APP_ORDER_EV_L3",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
		
	}

	ByteSeq HandleMessage(const ByteSeq & ParamBuffer) //����������ʱ������
	{
		LOG log(__FUNCTION__);
		ByteSeq ret;
		MsgNameArray_t arry;
		return ret;
	}


	/* ����*/
	virtual ~APP_Order()
	{
		try
		{
			//�Ͽ����ݿ�����
			CDataAccess::GetInstance()->UnInitialize();
		}
		catch(...)
		{
		}
	}

};

PACE_SERVER_INSTALL(APP_Order) //Ӧ�ó�������ڴ������Ϊ���������