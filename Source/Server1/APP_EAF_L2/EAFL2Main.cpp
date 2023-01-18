/*********************************************************************
*		
*  ��      ��:    EAFL2Main.cpp   		��¯L2���Ľ��ճ���
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ��������¯L2���Ľ���
*
*  �汾��ʷ		
*      1.0    2017-06-07    Zhangyuhong    ����
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
	*  ����: �������
	*  �������� PostInitCall 
	*  ����ֵ�� void	 	
	*  �����б�	��������    					ȡֵ��Χ     		    ����
	*
	*  �汾��ʷ		
	*       1.0    2017-06-07  LuYongyu    ����
	*  
	**********************************************************************/
	void PostInitCall()
	{
		LOG::doConfigure("APP_EAF_L2", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_EAF_L2");
		log.Info()<<"APP_EAF_L2:"<<endl;
		
		InitPowertranserData();

		//���ݿ�����
		CDataAccess::GetInstance()->Initialize();

		//EVtag�¼����� 
		string logFileName = "APP_EAF_L2_EV";
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(logFileName);//ʵ����CWatchEventHandlerI����Ϊ�¼����ⴴ��һ��servant
		this->subscribe("Tag/WatchWithDataTopic", watchEvent);

		//�趨EVtag�¼�������־��
		//������ʱ���Σ���ʽ��Ҫ�ſ�
		/*string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";	*/	

		//������·�� ,��ʽ��Ҫ����
		string logConfgFileFullName="D:\\iPlature\\conf\\App4Log.cfg";
		string logFilePath="D:\\iPlature\\log\\";	


		LOG::doConfigure( logFileName,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);

	}

	/**********************************************************************
	*  ����: ���յ��Ĳ���������
	*  �������� HandleMessage 
	*  ����ֵ�� Ice::ByteSeq	 	��������
	*  �����б�	��������    					ȡֵ��Χ     		    ����
	*    ParamBuffer  :    [IN/OUT] const ByteSeq &	     		  ���յ��ĵ���seq
	*
	*  �汾��ʷ		
	*       1.0    2017-06-07  LuYongyu    ����
	*  
	**********************************************************************/
	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		LOG log(__FUNCTION__,"APP_EAF_L2");

		 string functionName="APP_EAF_L2::HandleMessage()";

		log.Info()<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        data received                                                                                                                         "<<endl;
		log.Info()<<"****************************************************************************************************************************."<<endl; 		

		//pwת������
		ByteSeq receiver(ParamBuffer);
		string msgID;
		receiver>>msgID;
		log.Info()<<"msgID = "<<msgID<<endl;

		try
		{
			//���ĺ�ӳ��
			//�µ�¯L2�ƻ����ģ�EU01---6200
			//�ϵ�¯L2�ƻ����ģ�FU01---6600
			//�ϸּƻ�����
			if (msgID == "6200" || msgID == "6600")
			{
				MsgEU01::getInstance()->HandleMessage(receiver, msgID);
			}
			//���ֱ��֪ͨ����
			//��ʱȡ��
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

	/* ����*/
	virtual ~APP_EAF_L2()
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

PACE_SERVER_INSTALL(APP_EAF_L2);