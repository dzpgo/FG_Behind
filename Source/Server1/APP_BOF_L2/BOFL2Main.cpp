/*********************************************************************
*		
*  ��      ��:    BOFL2Main.cpp   		ת¯L2���Ľ��ճ���
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
#include "MsgBU01.h"

using namespace iXcomTCP2;
using namespace iPlature;
using namespace Monitor;


class APP_BOF_L2:public iPlature::P99Component
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
		LOG::doConfigure("APP_BOF_L2", ROOT_CONFIG);
		LOG log(__FUNCTION__,"APP_BOF_L2");
		log.Info()<<"APP_BOF_L2:"<<endl;
		
		InitPowertranserData();

		//���ݿ�����
		CDataAccess::GetInstance()->Initialize();

		//EVtag�¼����� 
		string logFileName = "APP_BOF_L2_EV";
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
		
		log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//�������ݳ���=�����ܳ���-����ͷ-������
		//��ȡ����
		data<<stRecvMsg.textbuf;
		try
		{
			if (msgID == "BU01")
			{
				MsgBU01::getInstance()->HandleMessage(data);							
			}


/*
			if (msgID == "AP001")//���ĺż��Զ���Э���е�5λ���ĺ�  AP��  Ҳ����ת¯L2�ù���Э���е�AP��
			{
				//����������Ӧ��ͷ�������Ҫ�Ƚ���Ӧ��ͷ
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

	/* ����*/
	virtual ~APP_BOF_L2()
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

PACE_SERVER_INSTALL(APP_BOF_L2);