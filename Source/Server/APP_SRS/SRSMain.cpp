#include <pace/P99Component.h>
#include <pace/CycSchedule.h>
#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>
#include <algorithm>

#include <iXcom-TCP2/iXcomDefine.h>
#include <iXcomTCP2.h>

#include "MsgLU01.h"
#include "MsgLU02.h"
#include "WatchEventHandlerI.h"
#include "DataAccess.h"
#include "UDPMsgDef.h"

class APP_SRS: public P99Component
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
			LOG log("PostInitCall");

			log.Info()<<"APP_SRS in PostInitCall :"<<endl;	

			iPlature::MsgTubePtr heatServicePtr = new iPlature::MsgTubeI(this);

			Ice::PropertiesPtr ptrProp = Component::instance()->properties();

			craneNO = ptrProp->getPropertyWithDefault("CraneNO", "");
			StringHelper::Trim(craneNO);
			log.Debug()<<"the SRS in Crane is : "<<craneNO<<endl;

			// ��֯ICEGrid�й�����ServiceName
			string strServiceNameAll = "iPlature/APP_SRS_" + craneNO;
			this->add(strServiceNameAll, heatServicePtr);
			log.Debug()<<"strServiceNameAll="<<strServiceNameAll<<endl;

			//����

			//���ĳ�ʼ��
			InitPowertranserData();
			//���ݿ�����
			CDataAccess::GetInstance()->Initialize();


			logConfgFileFullName="/iPlature/conf/App4Log.cfg";
			logFilePath="/iPlature/log/SRS/";

			logFileName_Handle_Message = "SRS_"+craneNO+"_HandleMessage";
			logFileName_Send_Message = "SRS_"+craneNO+"_SendMessage";

			LOG::doConfigure( logFileName_Send_Message,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//�����г�����ϵͳ��֪ͨ

			//EVtag�¼����� 			
			WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(craneNO, logFileName_Send_Message);//ʵ����CWatchEventHandlerI����Ϊ�¼����ⴴ��һ��servant
			this->subscribe("Tag/WatchWithDataTopic", watchEvent);

			
	}

	//���ĳ�ʼ��
	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		//SRS���� ���� �뷢��
		arry.push_back("LU01");
		arry.push_back("LU02");
		
		//json��ʽ����ı��
		//����ɨ�������ݽ���
		arry.push_back("LU01SD");
		//����ɨ�������ݽ���
		arry.push_back("LU02SD");

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}


	bool json2string(string jsonStr, string& messageNO)
	{
		bool ret=false;
		string functionName="json2string";
		LOG log(functionName, AUTO_CATCH_PID);
		try
		{
			bool bIsJsonStr = isJsonStr(jsonStr.c_str());
			if (!bIsJsonStr)
			{
				log.Info()<<"Receive From SRS TEL Result String IS NOT Json format! Exit........."<<endl;
				return ret;
			}

			Json::Value root;
			Json::Reader reader;

			if (jsonStr !="{}" && reader.parse(jsonStr, root))
			{
				messageNO = root["KEY_MessageNo"].asString();//�¼���
				ret = true;
				return ret;
			}
		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName +"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch (...)
		{
			string msg = functionName +"   error:";
			log.Debug()<<msg<<endl;
		}
		return ret;

	}

	bool isJsonStr(const char *jsoncontent)
	{
		std::stack<char> jsonstr;
		const char *p = jsoncontent;
		char startChar = jsoncontent[0];
		char endChar = '\0';
		bool isObject = false; //��ֹ {}{}���ж�
		bool isArray = false;  //��ֹ[][]���ж�

		while (*p != '\0')
		{
			endChar = *p;
			switch (*p)
			{
			case '{':
				if (!isObject)
				{
					isObject = true;
				}
				else if (jsonstr.empty()) //�����ظ���ջ
				{
					return false;
				}
				jsonstr.push('{');
				break;
			case '"':
				if (jsonstr.empty() || jsonstr.top() != '"')
				{
					jsonstr.push(*p);
				}
				else
				{
					jsonstr.pop();
				}
				break;
			case '[':
				if (!isArray)
				{
					isArray = true;
				}
				else if (jsonstr.empty()) //�����ظ���ջ
				{
					return false;
				}
				jsonstr.push('[');
				break;
			case ']':
				if (jsonstr.empty() || jsonstr.top() != '[')
				{
					return false;
				}
				else
				{
					jsonstr.pop();
				}
				break;
			case '}':
				if (jsonstr.empty() || jsonstr.top() != '{')
				{
					return false;
				}
				else
				{
					jsonstr.pop();
				}
				break;
			case '\\': //��ת����ַ�,����
				p++;
				break;
			default:;
			}
			p++;
		}

		if (jsonstr.empty())
		{
			//ȷ���Ƕ������������,֮��Ķ�������Ч
			switch (startChar) //ȷ����β���Ŷ�Ӧ
			{
			case '{':
				{
					if (endChar = '}')
					{
						return true;
					}
					return false;
				}
			case '[':
				{
					if (endChar = ']')
					{
						return true;
					}
					return false;
				}
			default:
				return false;
			}

			return true;
		}
		else
		{
			return false;
		}
	}


	ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
	{
		string functionName="APP_SRS :: HandleMessage()";
		LOG::doConfigure(logFileName_Handle_Message , logConfgFileFullName , logFilePath ,THREAD_CONFIG);
		LOG log(functionName, AUTO_CATCH_PID);

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
			string strTeleBuffer;
			teleBuffer>>strTeleBuffer;

			string messageNO = "";//udp��������е��¼���  �������ֵ��ĵĽṹ  ������Ϊ�� ��ͳ�����ϵĵ��ĺ�
			if ( false == json2string(strTeleBuffer, messageNO) )
			{
				log.Info()<<"json2string = false, return false............................"<<endl;
				return receiver;
			}

			// process smartdata
			if (messageNO == "1001" || messageNO == "1003")//�������� ��  �������� 
			{
				//����ɨ��
				log.Debug()<<"Receive MessageNO = "<<messageNO<<" , The telID is defined LU01"<<endl;
				MsgLU01::getInstance()->setMsgID("LU01");
				MsgLU01::getInstance()->HandleMessage(strTeleBuffer, craneNO);
			}
			if (messageNO == "101" )
			{
				//����ɨ��
				log.Debug()<<"Receive MessageNO = "<<messageNO<<" , The telID is defined LU02"<<endl;
				MsgLU02::getInstance()->setMsgID("LU02");
				MsgLU02::getInstance()->HandleMessage(strTeleBuffer, craneNO);
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

		return receiver;
	}


	/* ����*/
	virtual ~APP_SRS()
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

		string craneNO;

		string logConfgFileFullName;
		string logFilePath;
		string logFileName_Handle_Message;
		string logFileName_Send_Message;


	


};

PACE_SERVER_INSTALL(APP_SRS);