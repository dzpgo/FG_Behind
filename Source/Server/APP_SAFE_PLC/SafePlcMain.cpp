#include <pace/P99Component.h>
#include <pace/CycSchedule.h>
#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>

#include <iXcom-TCP2/iXcomDefine.h>
#include <iXcomTCP2.h>

#include "MsgS1.h"
#include "WatchEventHandlerI.h"
#include "DataAccess.h"
#include "UDPMsgDef.h"

#include "SafePLC4EAFYardBase.h"

using namespace Monitor;

class APP_SAFE_PLC: public P99Component
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
			LOG::doConfigure("APP_SAFE_PLC", ROOT_CONFIG);
			LOG log(__FUNCTION__,"APP_SAFE_PLC");
			log.Info()<<"APP_SAFE_PLC :"<<endl;	

			//���ĳ�ʼ��
			InitPowertranserData();
			//���ݿ�����
			CDataAccess::GetInstance()->Initialize();

			//EVtag�¼����� 			
			WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI();//ʵ����CWatchEventHandlerI����Ϊ�¼����ⴴ��һ��servant
			this->subscribe("Tag/WatchWithDataTopic", watchEvent);

			//�趨����EVtagʱ��־��
			string logConfgFileFullName="/iPlature/conf/App4Log.cfg";
			string logFilePath="/iPlature/log/";	
			LOG::doConfigure( "APP_SAFE_PLC_EV",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//�����г�����ϵͳ��֪ͨ
	}

	//���ĳ�ʼ��
	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		//SRS���� ���� �뷢��
		arry.push_back("S1");
		arry.push_back("S2");

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		LOG log(__FUNCTION__,"APP_SAFE_PLC");

		string functionName="APP_SAFE_PLC::HandleMessage()";

		log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        data received                                                                                                                                         "<<endl;
		log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

		ByteSeq receiver(ParamBuffer);
		log.DebugHex((void*)&ParamBuffer.front(),(int)ParamBuffer.size());
        iXcomTCP2::stru_recvtext0 stRecvMsg;
        memcpy((char *)&stRecvMsg, (char *)&ParamBuffer[0], ParamBuffer.size());             

        log.Info()<<"lineno="<<stRecvMsg.lineno<<endl;
        log.Info()<<"Tel. Received from XCOM-PCS OK!  ���ݳ���="<< stRecvMsg.textlenth<<"byte ,msg id�˿ں�:"<<stRecvMsg.ctextno<<endl;
        log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//�������ݳ��� = �����ܳ���-����ͷ-������

		ByteSeq teleBuffer;
		teleBuffer<<stRecvMsg.textbuf;

		try
		{
			byte btMsgID[2];

			MY_UDP_MSG udpMsg;

			memset(&udpMsg, 0, sizeof(MY_UDP_MSG));
			memcpy(udpMsg.msgData, stRecvMsg.textbuf, stRecvMsg.textlenth);

			//��ȫPLC���õ��Ǳ��� PLC,�����յ��ĵ��ĺ����, 
			//���ĺ����ַ��Ļ�, ���һ��NULL��ascii���Ӧ0����ʾ������־���� .����������Ҫȡָ��λ�õ��ֽ�
			//e.g.     53-00-31-00 00-00-00-00 00-00-00-00 00-00-00-00   S.1.............
			btMsgID[0] = udpMsg.msgData[0];
			btMsgID[1] = udpMsg.msgData[2];

			string msgID = string((char*)btMsgID);
			log.Info()<<"msgID = "<<msgID<<endl;

			StringHelper::Trim(msgID);

			if (msgID == "S1")
			{
				log.Debug()<<"Receive S1"<<endl;
				MsgS1::getInstance()->HandleMessage(teleBuffer, safePLC4EAFYard_Last);
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

		LOG::remove("APP_SAFE_PLC");
		return receiver;
	}


	/* ����*/
	virtual ~APP_SAFE_PLC()
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

private:

		SafePLC4EAFYardBase safePLC4EAFYard_Last;

	


};

PACE_SERVER_INSTALL(APP_SAFE_PLC);