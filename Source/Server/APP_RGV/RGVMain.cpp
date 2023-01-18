/*********************************************************************
*		
*  ��      ��:    RGVMain.cpp   		RGV���Ľ��ճ���
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ������RGV���Ľ���
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
#include "MsgRRWW01.h"
#include "MsgRRWW02.h"

using namespace iXcomTCP2;
using namespace iPlature;
using namespace Monitor;


class APP_RGV:public iPlature::P99Component
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
		LOG::doConfigure("APP_RGV", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_RGV");
		log.Info()<<"APP_RGV:"<<endl;
		
		InitPowertranserData();

		//���ݿ�����
		CDataAccess::GetInstance()->Initialize();

		//EVtag�¼����� 
		string logFileName = "APP_RGV_EV";
		WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(logFileName);//ʵ����CWatchEventHandlerI����Ϊ�¼����ⴴ��һ��servant
		this->subscribe("Tag/WatchWithDataTopic", watchEvent);

		//�趨EVtag�¼�������־��
		string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
		string logFilePath="/iPlature/log/";		
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
		LOG::doConfigure("APP_RGV", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_RGV");

		 string functionName="APP_RGV::HandleMessage()";

		log.Info()<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        data received                                                                                                                         "<<endl;
		log.Info()<<"****************************************************************************************************************************."<<endl; 

		ByteSeq receiver(ParamBuffer);

		iXcomTCP2::stru_recvtext0 stRecvMsg;

		memcpy((char *)&stRecvMsg, (char *)&ParamBuffer[0], ParamBuffer.size());

		log.Info()<<"lineno="<<stRecvMsg.lineno<<endl;
		log.Info()<<"Tel. Received from XCOM-PCS OK!  data length="<< stRecvMsg.textlenth<<"byte ,msg id:"<<stRecvMsg.ctextno<<endl;

		ByteSeq data, data1, data2;
		
		string msgID = stRecvMsg.ctextno;		
		
		log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//�������ݳ���=�����ܳ���-����ͷ-������
		//��ȡ����
		data<<stRecvMsg.textbuf;
		try
		{
			//RGV������λ����
			if (msgID == "RRWW01")
			{
				MsgRRWW01::getInstance()->HandleMessage(data);
			}
			else if (msgID == "RRWW02")
			{
				MsgRRWW02::getInstance()->HandleMessage(data);
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
		arry.push_back("RRWW01");
		arry.push_back("RRWW02");

		arry.push_back("WWRR01");
		arry.push_back("WWRR02");
		arry.push_back("WWRR03");
		arry.push_back("WWRR04");
		arry.push_back("WWRR05");

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	/* ����*/
	virtual ~APP_RGV()
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

PACE_SERVER_INSTALL(APP_RGV);