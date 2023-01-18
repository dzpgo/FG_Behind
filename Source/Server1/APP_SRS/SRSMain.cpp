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
	*  概述: 程序入口
	*  函数名： PostInitCall 
	*  返回值： void	 	
	*  参数列表：	参数类型    					取值范围     		    描述
	*
	*  版本历史		
	*       1.0    2017-06-07  LuYongyu    新增
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

			// 组织ICEGrid中公布的ServiceName
			string strServiceNameAll = "iPlature/APP_SRS_" + craneNO;
			this->add(strServiceNameAll, heatServicePtr);
			log.Debug()<<"strServiceNameAll="<<strServiceNameAll<<endl;

			//根据

			//电文初始化
			InitPowertranserData();
			//数据库连接
			CDataAccess::GetInstance()->Initialize();


			logConfgFileFullName="/iPlature/conf/App4Log.cfg";
			logFilePath="/iPlature/log/SRS/";

			logFileName_Handle_Message = "SRS_"+craneNO+"_HandleMessage";
			logFileName_Send_Message = "SRS_"+craneNO+"_SendMessage";

			LOG::doConfigure( logFileName_Send_Message,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);//来自行车控制系统的通知

			//EVtag事件触发 			
			WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(craneNO, logFileName_Send_Message);//实例化CWatchEventHandlerI对象，为事件主题创建一个servant
			this->subscribe("Tag/WatchWithDataTopic", watchEvent);

			
	}

	//电文初始化
	void InitPowertranserData()
	{
		MsgNameArray_t arry;
		//SRS电文 接收 与发送
		arry.push_back("LU01");
		arry.push_back("LU02");
		
		//json格式定义的标记
		//库区扫描结果数据解析
		arry.push_back("LU01SD");
		//车辆扫描结果数据解析
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
				messageNO = root["KEY_MessageNo"].asString();//事件号
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
		bool isObject = false; //防止 {}{}的判断
		bool isArray = false;  //防止[][]的判断

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
				else if (jsonstr.empty()) //对象重复入栈
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
				else if (jsonstr.empty()) //数组重复入栈
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
			case '\\': //被转义的字符,跳过
				p++;
				break;
			default:;
			}
			p++;
		}

		if (jsonstr.empty())
		{
			//确保是对象或者是数组,之外的都不算有效
			switch (startChar) //确保首尾符号对应
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
        log.Info()<<"Tel. Received from XCOM-PCS OK!  数据长度="<< stRecvMsg.textlenth<<"byte ,msg id端口号:"<<stRecvMsg.ctextno<<endl;
        log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//电文内容长度 = 电文总长度-电文头-结束符

		ByteSeq teleBuffer;
		teleBuffer<<stRecvMsg.textbuf;

		


		try
		{
			string strTeleBuffer;
			teleBuffer>>strTeleBuffer;

			string messageNO = "";//udp激光电文中的事件号  用来区分电文的结构  可以认为是 传统意义上的电文号
			if ( false == json2string(strTeleBuffer, messageNO) )
			{
				log.Info()<<"json2string = false, return false............................"<<endl;
				return receiver;
			}

			// process smartdata
			if (messageNO == "1001" || messageNO == "1003")//车辆上料 和  库区倒料 
			{
				//库区扫描
				log.Debug()<<"Receive MessageNO = "<<messageNO<<" , The telID is defined LU01"<<endl;
				MsgLU01::getInstance()->setMsgID("LU01");
				MsgLU01::getInstance()->HandleMessage(strTeleBuffer, craneNO);
			}
			if (messageNO == "101" )
			{
				//车辆扫描
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


	/* 析构*/
	virtual ~APP_SRS()
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

private:
		//string strJson;

		string craneNO;

		string logConfgFileFullName;
		string logFilePath;
		string logFileName_Handle_Message;
		string logFileName_Send_Message;


	


};

PACE_SERVER_INSTALL(APP_SRS);