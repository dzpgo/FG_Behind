#include <pace/P99Component.h>
#include <pace/CycSchedule.h>
#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>

#include <iXcom-TCP2/iXcomDefine.h>
#include <iXcomTCP2.h>

#include "MsgLU01.h"
#include "MsgLU02.h"
#include "MsgGW01.h"
#include "WatchEventHandlerI.h"
#include "DataAccess.h"
#include "UDPMsgDef.h"

class APP_Parking: public P99Component
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
			LOG::doConfigure("APP_PARKING", ROOT_CONFIG);
			LOG log(__FUNCTION__,"APP_PARKING");
			log.Info()<<"APP_Parking:"<<endl;	

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
			LOG::doConfigure( "APP_PARKING_EV_CRANE",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//�����г�����ϵͳ��֪ͨ
			LOG::doConfigure( "APP_PARKING_EV_GATE",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//���Ե�բ����ϵͳ��֪ͨ
			LOG::doConfigure( "APP_PARKING_EV_GRID",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//�����ϸ����ϵͳ��֪ͨ
			LOG::doConfigure( "APP_PARKING_EV_ORDER",  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//����ָ��ģ��ϵͳ��֪ͨ
	}

	//���ĳ�ʼ��
	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		//SRS���� ���� �뷢��
		arry.push_back("LU01");
		arry.push_back("LU02");

		arry.push_back("GW01");
		
		//json��ʽ����ı��
		//����ɨ�������ݽ���
		arry.push_back("LU01SD");
		//����ɨ�������ݽ���
		arry.push_back("LU02SD");

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}

	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		LOG log(__FUNCTION__,"APP_Parking");

		string functionName="APP_Parking::HandleMessage()";

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
			//stRecvMsg.textbuf��ʽ ��
			//������ģ�LU01#json_data_string
			//�ϸ����֪ͨ����: GW01,ͣ��λ��,����,�����뿪���

			MY_UDP_MSG udpMsg;
			const int lenMsgId = 4;

			memset(&udpMsg, 0, sizeof(MY_UDP_MSG));

			//UDP���ĵ��ĺų���
			udpMsg.lenMsgId = lenMsgId;
			memcpy(udpMsg.msgId, stRecvMsg.textbuf, lenMsgId); 
			memcpy(udpMsg.msgData, stRecvMsg.textbuf, stRecvMsg.textlenth);

			// MY_UDP_MSG 2 SmartData
			Ice::StringSeq vecString;
			int index = 0;
			SmartData sd = MsgSmartDataManager::InsRef().GetMsgSmartData(string((char*)udpMsg.msgId));

			string mestext = stRecvMsg.textbuf;    //�������ݣ�#�ָ�������
			string splitStr = "#";

			string strMsgID = (char*)udpMsg.msgId;
			//���ռ�����ĸ�ʽ���������ĺ�#JSON��ʽ�ַ���
			if (strMsgID.find("LU") != string::npos)
			{
				splitStr = "#";
			}
			//�����ϸ���ĸ�ʽ���������ĺ�,ʵ���ֶ�
			if (strMsgID.find("GW") != string::npos)
			{
				splitStr = ",";
			}
			vecString = StringHelper::ToVector<string>(mestext, const_cast<char*>(splitStr.c_str()), static_cast<int>(strlen(splitStr.c_str())));
			UdpUtil::wrapSmartData(vecString, sd, index);

			// process smartdata
			if (!strcmp((char*)udpMsg.msgId, "LU01"))
			{
				//����ɨ��
				log.Debug()<<"Receive LU01"<<endl;
				MsgLU01::getInstance()->setMsgID("LU01");
				MsgLU01::getInstance()->HandleMessage(sd);
			}
			if (!strcmp((char*)udpMsg.msgId, "LU02"))
			{
				//����ɨ��
				log.Debug()<<"Receive LU02"<<endl;
				MsgLU02::getInstance()->setMsgID("LU02");
				MsgLU02::getInstance()->HandleMessage(sd);
			}
			if (!strcmp((char*)udpMsg.msgId, "GW01"))
			{
				//�ϸ����ϵͳ����������/�뿪֪ͨ����
				log.Debug()<<"Receive GW01"<<endl;
				MsgGW01::getInstance()->setMsgID("GW01");
				MsgGW01::getInstance()->HandleMessage(sd);
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

		LOG::remove("PARKING_HANDLE_MESSAGE");
		return receiver;
	}


	/* ����*/
	virtual ~APP_Parking()
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
		//string strJson;

	


};

PACE_SERVER_INSTALL(APP_Parking);