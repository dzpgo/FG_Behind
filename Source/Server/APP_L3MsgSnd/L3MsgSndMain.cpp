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
        //���ݿ�����
        CDataAccess::GetInstance()->Initialize();
        //��ʼ������
        InitPowertranserData();
        //����tag�¼�
		string logFileName = "APP_L3MsgSnd";
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(logFileName);//ʵ����CWatchEventHandlerI����Ϊ�¼����ⴴ��һ��servant
        this->subscribe("Tag/WatchWithDataTopic", watchEvent);
       
    }

    ByteSeq HandleMessage(const ByteSeq & ParamBuffer) //����������ʱ������
    {
        LOG log(__FUNCTION__);
        ByteSeq ret;
        MsgNameArray_t arry;
		return ret;
    }

    //��ʼ��poerTranser
    void InitPowertranserData()
    {
		LOG log(__FUNCTION__);
        MsgNameArray_t arry;

        arry.push_back("HCP401"); //RGV������ۺŶ�Ӧ��ϵ
        arry.push_back("HCP411"); //��Ʒ�ַϸֽ��������ַϸֶѳ�װж�����Ϣ
        arry.push_back("HCP412"); //�ϸ�װ��װ����Ϣ������ʵ����
        arry.push_back("HCP421"); //�����ֽ����϶ѳ���ʱ�����Ϣ

        MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
    }

	/* ����*/
	virtual ~APP_L3MsgSnd()
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

PACE_SERVER_INSTALL(APP_L3MsgSnd) //Ӧ�ó�������ڴ������Ϊ���������