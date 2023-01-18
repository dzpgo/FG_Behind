
#pragma region 头文件

//==================平台头文件==============================
#include <pace/P99Component.h>
#include <pace/CycSchedule.h>
#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>
#include <iXcomTCP2.h>
#include <PowerTranser/MsgComponent.h>
#include <PowerTranser/PowerTranser.h>

#include <iXcom-TCP2/iXcomDefine.h>
#include "pace/P99Component.h"
#include <pace/SmartData.h>
#include <pace/SmartBuffer.h>

//==================应用头文件==============================
#include "MultiLine_MDProxy_TimerWatchInterfaceI.h"
#include "WatchEventHandlerI_Crane.h"
#include "WatchEventHandlerI.h"
#include "SafetyArea_Bay.h"
#include "DataAccess.h"
#include "CraneMonitor.h"

#include "MsgCREU01.h"
#include "MsgCREU02.h"

#include "MsgHMICRANE01.h"
#include "MsgHMICRANE02.h"

#include "MsgUS01.h"
#include "MsgUS04.h"

#include "Crane_Testing_Main.h"
#include "YardMapTracker.h"
#include "WATCH_DOG_LIFT_COIL_DOWN_PHASE.h"
#include "CraneAutoManuSwitch_Tracker.h"

#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"
#include "Adapter_UACS_CRANE_MOVEORDER_MSG.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "CraneEvadeRequestBase.h"
#include "ToBe_Or_Not_ToBe.h"
#include "OrderSelector.h"
#include "WMSCraneOrder_Resolver.h"

#pragma endregion

using namespace iPlature;
using namespace Monitor;

class APP_Crane: public P99Component
{
public:

#pragma region PostInitCall-模块初始化
	void PostInitCall()
    {
		LOG log("PostInitCall");


		//数据库连接
		CDataAccess::GetInstance()->Initialize();

		try
		{
		    log.Info()<<"APP_Crane in PostInitCall"<<endl;
			
			iPlature::MsgTubePtr heatServicePtr = new iPlature::MsgTubeI(this);

			Ice::PropertiesPtr ptrProp = Component::instance()->properties();
 

			log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                            读取配置文件           read from config file                                                                                                    "<<endl;
			log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

			
			//配置文件中读 行车号
			craneNO = ptrProp->getPropertyWithDefault("CraneNO", "");
			StringHelper::Trim(craneNO);
			log.Debug()<<"craneNO="<<craneNO<<endl;

			//配置文件中读 跨别
			bayNO=ptrProp->getPropertyWithDefault("bayNO", "");
			StringHelper::Trim(bayNO);
			log.Debug()<<"bayNO="<<bayNO<<endl;			

			//配置文件中读 该跨中所有的行车号，行车的序列按照X从小到大的顺序
			strQueueOfCranesOrderByXIncrease=ptrProp->getPropertyWithDefault("queueOfCranesOrderByXIncrease", "");
			log.Debug()<<"strQueueOfCranesOrderByXIncrease="<<strQueueOfCranesOrderByXIncrease<<endl;

			vectorQueueOfCranesOrderByXIncrease= StringHelper::ToVector<string>(strQueueOfCranesOrderByXIncrease, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

			//读取配置文件中StormTop名字
			cranePLCStatusTopicName=ptrProp->getPropertyWithDefault("cranePLCStatusTopicName", "");
			log.Debug()<<"cranePLCStatusTopicName="<<cranePLCStatusTopicName<<endl;

			//读取配置文件中Bay的XML定义文件名称
			bayXMLFileName=ptrProp->getPropertyWithDefault("bayXMLName", "");
			log.Debug()<<"bayXMLFileName="<<bayXMLFileName<<endl;

			//2018.6.30 zhangyuhong add
			vecOrderIDAlarmCodeLast.clear();
			vecOrderIDAlarmCodeLast.push_back(DB_INT_NULL);
			vecOrderIDAlarmCodeLast.push_back(DB_INT_NULL);
			
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                  创建iPlature服务名         create service name for iplature                                                                                     "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 

			// 组织ICEGrid中公布的ServiceName
		    string strServiceNameAll = "iPlature/APP_Crane_" + craneNO;
		    this->add(strServiceNameAll, heatServicePtr);
			log.Debug()<<"strServiceNameAll="<<strServiceNameAll<<endl;


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                 定义Log文件路径及文件名           define log files                                                                                                      "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 

			//about log file
#ifdef WIN32
			logConfgFileFullName="F:\\iPlature\\conf\\App4Log.cfg";

			logFilePath="F:\\iPlature\\log\\"+craneNO+"\\";

			logFilePath_Alarm="F:\\iPlature\\log\\CraneAlarm\\";
#else
			logConfgFileFullName="/iPlature/conf/App4Log.cfg";

			logFilePath="/iPlature/log/"+craneNO+"/";

			logFilePath_Alarm="/iPlature/log/CraneAlarm/";
#endif
			logFileName_Handle_Message="APP_Crane_"+craneNO+"_HandleMessage";

			logFileName_Main_Cycle_Clone="APP_Crane_"+craneNO+"_MainCycle_Clone";

			logFileName_YardMap_Cycle="APP_Crane_"+craneNO+"_YardMapCycle";

			logFileName_WmsCraneOrder_Selector="APP_Crane_"+craneNO+"_WmsCraneOrder_Selector";

			logFileName_WatchDog_LiftCoil_Down_Phase="APP_Crane_"+craneNO+"_WatchDog_LiftCoil_Down_Phase";
			
			logFileName_CraneAutoManuSwitchTracker="APP_Crane_"+craneNO+"_AutoManuSwitch";

			logFileName_HeatBeatMsg_Cycle="APP_Crane_"+craneNO+"_HeatBeatMsg";



			log.Debug()<<"logConfgFileFullName="<<logConfgFileFullName<<endl;

			log.Debug()<<"logFilePath="<<logFilePath<<endl;

			log.Debug()<<"logFileName_Handle_Message="<<logFileName_Handle_Message<<endl;

			log.Debug()<<"logFileName_WmsCraneOrder_Selector="<<logFileName_WmsCraneOrder_Selector<<endl;

			log.Debug()<<"logFileName_WatchDog_LiftCoil_Down_Phase="<<logFileName_WatchDog_LiftCoil_Down_Phase<<endl;

			log.Debug()<<"logFileName_CraneAutoManuSwitchTracker="<<logFileName_CraneAutoManuSwitchTracker<<endl;

			log.Debug()<<"logFileName_HeatBeatMsg_Cycle="<<logFileName_HeatBeatMsg_Cycle<<endl;
			//end of log file

			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"																			Init Powertranser																													  "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 

			//初始化电文
			InitPowertranserData();

			LOG::doConfigure("MDProxy" ,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
			LOG::doConfigure("EvadeRequestReceiver",logConfgFileFullName,logFilePath, BRANCH_CONFIG);

			//SRS激光反馈电文tag点收到处理日志
			LOG::doConfigure("SrsMsgRcvHandler", logConfgFileFullName,logFilePath, BRANCH_CONFIG);


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      read from XML for the config of area define in the bay                                                   "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 

			string bayXmlFullName = "";

#ifdef WIN32	
			bayXmlFullName="F:\\iPlature\\conf\\APP_Crane\\"+bayXMLFileName;
#else
			bayXmlFullName="/iPlature/conf/APP_Crane/"+bayXMLFileName;
#endif

			log.Debug()<<"bayXmlFullName="<<bayXmlFullName<<endl;
			SafetyArea_Bay::getInstance()->ReadFromXML(bayXmlFullName);
			mapSafeyArea = SafetyArea_Bay::getInstance()->getMapSafeAreaBase();

			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      Init CraneMonitor                                                                                                                    "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			CraneMonitor::getInstance()->setCraneNO(craneNO);
			CraneMonitor::getInstance()->initialise_MapCranePLCStatusPhototAlbum(vectorQueueOfCranesOrderByXIncrease);	


			log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      WatchEventHandlerI_Crane                                                                                                                    "<<endl;
			log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
			CLTS::CranePublisherPtr cranePublisher = new WatchEventHandlerI_Crane(craneNO);
			this->subscribe(cranePLCStatusTopicName, cranePublisher);//


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      WatchEventHandlerI                                                                                                                "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			WatchWithDataInterfacePtr watchEvent = new CWatchEventHandlerI(craneNO);
			this->subscribe("Tag/WatchWithDataTopic", watchEvent);

			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      订阅MDProxy如果tag恢复正常模式，需要取消订阅                      "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//*iMultiLink::TimerWatchInterfacePtr mdProxy = new iMultiLink::MultiLine_MDProxy_TimerWatchInterfaceI(craneNO);
			//this->subscribe("iMultiLink/TimerWatchTopic", mdProxy);*/
			iPlature::iMultiLink::TimerWatchInterfacePtr  mdProxy = new  iMultiLink::MultiLine_MDProxy_TimerWatchInterfaceI(craneNO);
			//this->subscribe("iMultiLink/TimerWatchTopic", mdProxy);
		    this->subscribe("iMultiLink/TimerWatchTopic", mdProxy);


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      Start MainCycle_Clone                                                                                                           "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//定义线程
			threadCycle_MainCycle_Clone = CycSchedule::GetObject("MainCycle_Clone");
			threadCycle_MainCycle_Clone->registerMethod(this,(CycSchedule::Method)&APP_Crane::MainCycle_Clone, 1);//
			//启动线程
			threadCycle_MainCycle_Clone->startScheduling(CycSchedule::ORDERED);
			
			

			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      Start Yard Map Tracker  Cycle                                                                                                               "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			InitTrackTagValue();
			//定义线程
			threadCycle_YardMap_Track= CycSchedule::GetObject("YardMapCycle");
			threadCycle_YardMap_Track->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_YardMap_Track, 1);
		    //启动线程
			threadCycle_YardMap_Track->startScheduling(CycSchedule::ORDERED);
			

			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      WmsCraneOrderSelector  Cycle                                                                                                                                  "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//定义线程
			threadCycle_WmsCraneOrder_Selector= CycSchedule::GetObject("Cycle_WmsCraneOrder_Selector");
			threadCycle_WmsCraneOrder_Selector->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_WmsCraneOrder_Selector, 2);
		    //启动线程
			threadCycle_WmsCraneOrder_Selector->startScheduling(CycSchedule::ORDERED);

					
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      WATCH_DOG_LIFT_COIL_DOWN_PHASE                                                                                                       "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//定义线程
			threadCycle_WatchDog_LiftCoil_Down_Phase= CycSchedule::GetObject("Cycle_WatchDog_LiftCoil_Down_Phase");
			threadCycle_WatchDog_LiftCoil_Down_Phase->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_WatchDog_LiftCoil_Down_Phase, 1);
		    //启动线程
			threadCycle_WatchDog_LiftCoil_Down_Phase->startScheduling(CycSchedule::ORDERED);		


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      Start CraneAutoManuSwitchTracker  CYCLE                                                                                     "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//定义线程
			threadCycle_CraneAutoManuSwitchTracker= CycSchedule::GetObject("Cycle_CraneAutoManuSwitchTracker");
			threadCycle_CraneAutoManuSwitchTracker->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_CraneAutoManuSwitchTracker, 1);
		    //启动线程
			threadCycle_CraneAutoManuSwitchTracker->startScheduling(CycSchedule::ORDERED);

			//2017.12.11 zhangyuhong add 向行车发送心跳电文
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      Start Sending to CranePLC HeartBeat Msg                                                                       "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//定义线程
			threadCycle_HeartBeatMsg = CycSchedule::GetObject("Cycle_HeartBeatMsg");
			threadCycle_HeartBeatMsg->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_HeartBeatMsg, 1);//
			//启动线程
			threadCycle_HeartBeatMsg->startScheduling(CycSchedule::ORDERED);

		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg="   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch(...)
		{
		}
    }
#pragma endregion
	 

#pragma region InitTrackTagValue
	void InitTrackTagValue()
	{
		//2017.10.9 zhangyuhong add
		//初始化tracktag点：CRANE_NO+_ACTIONS_TRACKER
		TAGVALUEMAP mapTagValue;
		string tagName = craneNO + "_ACTIONS_TRACKER";
		mapTagValue.insert(map<string,string>::value_type(tagName , "INIT"));
		TAGVALUEMAP TagTimeStamp;
		Tag::GetInst().MDPut(TagTimeStamp,mapTagValue);
	}
#pragma endregion


#pragma region InitPowertranserData
	//初始化poerTranser
	void InitPowertranserData()
	{
		MsgNameArray_t arry;

		//安全PLC电文
		arry.push_back("SU01");
		arry.push_back("SU02");	
		
		//行车PLC电文
		arry.push_back("CU01");
		arry.push_back("CU02");	

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}
#pragma endregion


#pragma region 0-HandleMessage 
	//电文接收入口  直接接收版本
    ByteSeq HandleMessage(const ByteSeq& ParamBuffer)
    {
		 string functionName="APP_Crane :: HandleMessage()";
		LOG::doConfigure(logFileName_Handle_Message , logConfgFileFullName , logFilePath ,THREAD_CONFIG);
		LOG log(functionName, AUTO_CATCH_PID);

		log.Info()<<"****************************************************************************************************************************."<<endl; 
		log.Info()<<"                                                                        HandleMessage  data received                                                                                          "<<endl;
		log.Info()<<"****************************************************************************************************************************."<<endl; 

		ByteSeq receiver(ParamBuffer);
        log.DebugHex((void*)&ParamBuffer.front(),(int)ParamBuffer.size());
        iXcomTCP2::stru_recvtext0 stRecvMsg;
        memcpy((char *)&stRecvMsg, (char *)&ParamBuffer[0], ParamBuffer.size());

        log.Info()<<"lineno="<<stRecvMsg.lineno<<endl;
        log.Info()<<"Tel. Received from XCOM-PCS OK!  data length="<< stRecvMsg.textlenth<<"byte ,msg id:"<<stRecvMsg.ctextno<<endl;

		string msgID=stRecvMsg.ctextno;
		log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//电文内容长度=电文总长度-电文头-结束符
		ByteSeq teleBuffer;
		teleBuffer<<stRecvMsg.textbuf;

		try
		{		
			//CREU01 行车状态信息
			if( msgID == "CU01")
			{
				//MsgCREU01::getInstance()->HandleMessage(craneNO, cranePLCStatusTopicName,teleBuffer, vecOrderIDAlarmCodeLast, cranePLCStatus_Last);
			}
			//CREU02 行车报警信息
			else if( msgID == "CU02" )
			{
				//MsgCREU02::getInstance()->HandleMessage(craneNO,teleBuffer);
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

		LOG::remove(logFileName_Handle_Message);

		return receiver;
	}
#pragma endregion


#pragma region 1.5-MainCycle_Clone
	//1.5
	void MainCycle_Clone(const float para)
	{
		//IceUtil::Mutex::Lock lock(m_mutexValue);

		string functionName="APP_Crane :: MainCycle_Clone()";

		LOG::doConfigure(logFileName_Main_Cycle_Clone , logConfgFileFullName , logFilePath ,THREAD_CONFIG);

		LOG log(functionName, AUTO_CATCH_PID);

		//2019.4.13 zhangyuhong add
		//延迟100ms 读取夏之晨的避让tag点
#ifdef WIN32
		DWORD intervelXia=100;
#else
		unsigned int  intervelXia = 100000;
#endif


#ifdef WIN32
		DWORD intervel=1000;
#else
		unsigned int  intervel = 1;
#endif

		try
		{

			while(true)
			{
							log.Info()<<"*******************************************************************************************************************************************"<<endl; 
							log.Info()<<"                                                                                       MainCycle_Clone Start                                                                                                                   " <<endl; 
							log.Info()<<"*******************************************************************************************************************************************"<<endl; 

//----------------------------------------1...check: read crane plc status--------------------------------------------------------------------------
							log.Info()<<"1...check: read crane plc status......"<<endl;
							CranePLCStatusBase cranePLCStatusBase;
							if(! (CraneMonitor::getInstance()->getPLCStatus(cranePLCStatusBase) )  )
							{
								log.Debug()<<"...can not read crane plc status......."<<endl;
#ifdef WIN32
								Sleep(intervel);
#else
								sleep(intervel);
#endif
								continue;
							}
							log.Info()<<"Y= "<<cranePLCStatusBase.getYAct()<<endl;
							log.Info()<<"OK......"<<endl;
							
//----------------------------------------2...check: crane CustomOffice_Is_Auto_Ready_AskPlan--------------------------------------------------------------------------
							log.Info()<<"2...check: crnae CustomOffice_Is_Auto_Ready_AskPlan ......"<<endl;
							if(ACTION_COMMON_FUNCTION::CustomOffice_Is_Auto_Ready_AskPlan(craneNO,cranePLCStatusBase)==false)
							{
								log.Debug()<<"....crane CustomOffice is not auto or not ready or not askplan......"<<endl;
#ifdef WIN32
								Sleep(intervel);
#else
								sleep(intervel);
#endif
								continue;
							}
							log.Info()<<"OK......"<<endl;

//----------------------------------------3...check: crane excute wms or evade----------------------------------------------------------------------------------------------
							log.Info()<<"3...check:  crane excute wms or evade......"<<endl;
							string choise=ToBe_Or_Not_ToBe::choose(craneNO, cranePLCStatusBase);
							if(choise==ToBe_Or_Not_ToBe::CHOISE_DO_EVADE)
							{
								log.Info()<<"3.1...check result: crane excute evade......"<<endl;
								//Test_Evade_Move::Test_EvadeMoving(craneNO);
							}
							else if(choise==ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER)
							{
								log.Info()<<"3.2...check result: crane excute wms......"<<endl;
								Crane_Testing_Main ::Test_AfterRolling (craneNO ,cranePLCStatusBase );
							}
							else if(choise==ToBe_Or_Not_ToBe::CHOISE_NOTHING_TODO)
							{
								log.Info()<<"3.3...check result: crane excute nothing......"<<endl;
							}


#ifdef WIN32
							Sleep(intervel);
#else
							sleep(intervel);
#endif	

			}
		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch(...)
		{
		}
	}
#pragma endregion


#pragma region 2-Cycle_YardMap_Track
	//2
	void Cycle_YardMap_Track(const float para)
	{
		//IceUtil::Mutex::Lock lock(m_mutex_YardMap);

		string functionName="APP_Crane :: Cycle_YardMap_Track()";

		LOG::doConfigure(logFileName_YardMap_Cycle , logConfgFileFullName , logFilePath ,THREAD_CONFIG);

		LOG log(functionName, AUTO_CATCH_PID);

#ifdef WIN32
		DWORD intervel=1000;
#else
		unsigned long intervel = 1;
#endif

		try
		{
			while(true)
			{
							log.Info()<<"*******************************************************************************************************************************************"<<endl; 
							log.Info()<<"                                                                                       Cycle_YardMap_Track                                                                                                                         " <<endl; 
							log.Info()<<"*******************************************************************************************************************************************"<<endl; 
							//event tracker for coil up and coil down
							yardMap_Tracker.EventTrack_CraneActions();
#ifdef WIN32
							Sleep(intervel);
#else
							sleep(intervel);
#endif

			}

		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch(...)
		{
		}
	}
#pragma endregion


#pragma region 4-Cycle_WmsCraneOrder_Selector
	//4
	void Cycle_WmsCraneOrder_Selector(const float para)
	{
		//IceUtil::Mutex::Lock lock(m_mutexValue);

		string functionName="APP_Crane :: Cycle_WmsCraneOrder_Selector()";
		LOG::doConfigure(logFileName_WmsCraneOrder_Selector , logConfgFileFullName , logFilePath ,THREAD_CONFIG);
		LOG log(functionName, AUTO_CATCH_PID);

#ifdef WIN32
		DWORD intervel=1000;
#else
		unsigned long intervel = 1;
#endif

		//循环次数统计
		int nWaitDuration = 0;		
		try
		{
			while(true)
			{

								log.Info()<<"*******************************************************************************************************************************************"<<endl; 
								log.Info()<<"                                                                                       Cycle_WmsCraneOrder_Selector Start                                                                                        " <<endl; 
								log.Info()<<"*******************************************************************************************************************************************"<<endl; 

								

								//-----------------------------------当前指令表检查--------------------------------------------------------------------------------------------------------------------------------

								OrderCurrentBase  orderCurrent;							     
								orderCurrent=Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

								//2019.4.24 zhangyuhong add
								//如果是有当前指令正在做（回登车位指令除外），则continue
								if(orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY )
								{
										if ( orderCurrent.getOrderType() != "X1")
										{											
												log.Info()<<"行车指令状态CMDStatus不为空闲STATUS_EMPTY，且不是回登车位指令，Sleep-->Continue......."<<endl;
#ifdef WIN32
												Sleep(intervel);
#else
												sleep(intervel);
#endif
												continue;
										}
								}

								//-----------------------------------行车海关检查三盏灯--------------------------------------------------------------------------------------------------------------------------------
								CranePLCStatusBase cranePLCStatusBase;
								CraneMonitor::getInstance()->getPLCStatus(cranePLCStatusBase);

								//2018.12.11 zhangyuhong add
								if( !ACTION_COMMON_FUNCTION::CustomOffice_Is_Auto_Ready_AskPlan(craneNO,cranePLCStatusBase) ) //2019.4.24 zhangyuhong add  如果海关没通过，且当前指令表里指令类型 不为 回登车位指令
								{
									if ( orderCurrent.getOrderType() != "X1" )
									{
										log.Info()<<"行车PLC海关检查不通过，且当前正在执行指令不是回登车位指令！Sleep-->Continue........ "<<endl;
#ifdef WIN32
										Sleep(intervel);
#else
										sleep(intervel);
#endif
										continue;
									}
								}

								//-----------------------------------指令锁定检查--------------------------------------------------------------------------------------------------------------------------------

								//2018.1.26 zhangyuhong add
								//指令锁定 tag点：tag值=1 指令锁定：执行完当前指令后，后续3-1的指令不发送，同时也不发给3-2
								//前提是hascoil=0
								if (cranePLCStatusBase.getHasCoil() == 0 && ACTION_COMMON_FUNCTION::GetTagValue(craneNO, "_HMI_A6_ORDER_LOCK") == "1")
								{
									log.Info() << "检测到有>>指令锁定<<，行车号CraneNO="<<craneNO<<"的后续指令不再接收！"<< endl;
									
									if (cranePLCStatusBase.getHasCoil() == 0 )//&& ACTION_COMMON_FUNCTION::GetTagValue(craneNO, "_ORDER_BOARDMOVING") == "1")
									{
										log.Info() << "行车指令锁定，不再接收后续指令，行车空钩无卷，行车准备返回登车位.......Test_Evade_Move::Test_BoardingMoving()......" << endl;
										//2019.4.24 zhangyuhong add
										//写指令表方式 回登车位指令
										WMSCraneOrder_Resolver::resolver_BoardingCraneOrder(craneNO, cranePLCStatusBase);
									}
#ifdef WIN32
									Sleep(intervel);
#else
									sleep(intervel);
#endif
									continue;
								}


								//20191225 zhangyuhohng add
								//如果行车重钩，且指令顺序表中关于此行车的所有指令的状态都是1，则认为此吊无法识别是哪条指令，行车不予取指令，报警提示出来需要手动操作
								if (cranePLCStatusBase.getHasCoil() != 0)
								{
									//获取当前指令顺序表里指令状态为非0的记录，如果有，继续，如果没有，返回
									if ( Adapter_UACS_CRANE_ORDER_CURRENT::getStautsNot1Order(craneNO) == false )
									{
										log.Info()<<"行车当前重钩，但是指令顺序表里无 正在执行 指令（状态非0的）"<<endl;
										string tagValue = ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8055;
										ACTION_COMMON_FUNCTION::SetTagValue(orderCurrent.getCraneNO(), 
																															ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS, 
																															tagValue);
#ifdef WIN32
										Sleep(intervel);
#else
										sleep(intervel);
#endif
										continue;
									}
								}

								
								if (true == OrderSelector::Selector(craneNO))
								{
									nWaitDuration = 0;
#ifdef WIN32
									Sleep(intervel);
#else
									sleep(intervel);
#endif
									continue;
									
								}


								//-----------------------------------行车回登车位检查--------------------------------------------------------------------------------------------------------------------------------

								//2019.3.18 zhangyuhong add
								//增加HMI的回登车位的tag点功能
								//string tagValueHMIReturn = ACTION_COMMON_FUNCTION::GetTagValue(craneNO, "GGGGG");
								log.Info() << "行车当前从指令表中获取不到指令！当前无指令！30秒后，回登车位！" << endl;
								log.Info() << "当前计数器 nWaitDuration = "<< nWaitDuration << endl;
								//统计无指令循环的次数
								nWaitDuration ++;
								//如果等待10秒后，行车一直无指令，则让行车回登车位，同时置nWaitDuration=0
								//2018.12.29 zhangyuhobng add
								//修改了指令获取周期，所以等待时间变更为5秒
								//if (nWaitDuration > 5 || tagValueHMIReturn == "1")
								if (nWaitDuration > 5 )
								{
									//如果没有指令，且行车当前空钩无卷，行车回登车位								
									if ( cranePLCStatusBase.getHasCoil() == 0 )
									{
										log.Info() << "行车指令顺序表(UACS_SCHEDULE_ORDER_QUEUE)中无当前行车的指令，行车空钩无卷，行车准备返回登车位.......Test_Evade_Move::Test_BoardingMoving()......" << endl;
										//2019.4.24 zhangyuhong add
										WMSCraneOrder_Resolver::resolver_BoardingCraneOrder(craneNO, cranePLCStatusBase);										
									}
								}
								
#ifdef WIN32
								Sleep(intervel);
#else
								sleep(intervel);
#endif
			}
		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch(...)
		{
		}
	}
#pragma endregion


#pragma region 5-Cycle_WatchDog_LiftCoil_Down_Phase
	//5
	void Cycle_WatchDog_LiftCoil_Down_Phase(const float para)
	{
		//IceUtil::Mutex::Lock lock(m_mutexValue);

		string functionName="APP_Crane :: Cycle_WatchDog_LiftCoil_Down_Phase()";

		LOG::doConfigure(logFileName_WatchDog_LiftCoil_Down_Phase , logConfgFileFullName , logFilePath ,THREAD_CONFIG);

		LOG log(functionName, AUTO_CATCH_PID);

#ifdef WIN32
		DWORD intervel=1000;
#else
		unsigned long intervel = 1;
#endif

		try
		{
			while(true)
			{
						log.Info()<<"*******************************************************************************************************************************************"<<endl; 
						log.Info()<<"                                                                                       Cycle_WatchDog_LiftCoil_Down_Phase                                                                                      " <<endl; 
						log.Info()<<"*******************************************************************************************************************************************"<<endl; 
						watchDogLiftCoilDownPhase.watch(craneNO);
#ifdef WIN32
						Sleep(intervel);
#else
						sleep(intervel);
#endif

			}
		
		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch(...)
		{
		}
	}
#pragma endregion


#pragma region 8-Cycle_CraneAutoManuSwitchTracker
	//8
	void Cycle_CraneAutoManuSwitchTracker(const float para)
	{
		//IceUtil::Mutex::Lock lock(m_mutexValue);

		string functionName="APP_Crane :: Cycle_CraneAutoManuSwitchTracker()";

		LOG::doConfigure( logFileName_CraneAutoManuSwitchTracker , logConfgFileFullName , logFilePath ,THREAD_CONFIG);

		LOG log(functionName, AUTO_CATCH_PID);

#ifdef WIN32
		DWORD intervel=1000;
#else
		float intervel = 1;
#endif

		try
		{
				while(true)
				{
									log.Info()<<"*******************************************************************************************************************************************"<<endl; 
									log.Info()<<"                                                                                       Cycle_CraneAutoManuSwitchTracker                                                                                                                                    " <<endl; 
									log.Info()<<"*******************************************************************************************************************************************"<<endl; 			
									craneAutoManuSwitch_Tracker.Track_AutoManuSwitch();
#ifdef WIN32
									Sleep(intervel);
#else
									sleep(intervel);
#endif
				}

		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch(...)
		{
		}
	}
#pragma endregion


#pragma region 9-Cycle_HeartBeatMsg
	//向行车发送sending heatbeat msg
	void Cycle_HeartBeatMsg(const float para)
	{
		//IceUtil::Mutex::Lock lock(m_mutex_YardMap);

		string functionName="APP_Crane :: Cycle_HeartBeatMsg()";

		LOG::doConfigure(logFileName_HeatBeatMsg_Cycle , logConfgFileFullName , logFilePath ,THREAD_CONFIG);

		LOG log(functionName, AUTO_CATCH_PID);

		CranePLCOrderBase cranePLCOrderbase;

		
		cranePLCOrderbase.setCraneNO(craneNO);
		cranePLCOrderbase.setShortCmd(900);//900--心跳电文标记 
		cranePLCOrderbase.setOrderID(0);//指令号为0--意即心跳电文
		//cranePLCOrderbase.setDownRotateAngleSet(999999);
		//cranePLCOrderbase.setUpRptateAngleSet(999999);

#ifdef WIN32
		DWORD intervel=4000;
#else
		unsigned long intervel = 4;
#endif

		try
		{
			while(true)
			{
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
				log.Info()<<"                                                                                       Cycle_HeartBeatMsg                                                                                                                         " <<endl; 
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 

				/*if (MsgEUCR01::getInstance()->SendOutMessage(cranePLCOrderbase))
					log.Debug()<<"..................... 心跳电文发送行车PLC  OK !"<<endl;
				else
					log.Error()<<"..................... 心跳电文发送行车PLC  ERROR !"<<endl;*/
				
#ifdef WIN32
				Sleep(intervel);
#else
				sleep(intervel);
#endif

			}

		}
		catch (std::exception& stdex)
		{
			string errorMessage=stdex.what();
			string msg=functionName+"   error:"+ errorMessage;
			log.Debug()<<msg<<endl;
		}
		catch(...)
		{
		}
	}
#pragma endregion


#pragma region 析构函数
	/** 
	* 析构
	*/
	virtual ~APP_Crane()
	{
		//1.5
		threadCycle_MainCycle_Clone->stopScheduling(0);
		//2
		threadCycle_YardMap_Track->stopScheduling(0);
		//4
		threadCycle_WmsCraneOrder_Selector->stopScheduling(0);
		//5
		threadCycle_WatchDog_LiftCoil_Down_Phase->stopScheduling(0);
		//8
		threadCycle_CraneAutoManuSwitchTracker->stopScheduling(0);
		//9
		threadCycle_HeartBeatMsg->stopScheduling(0);


		//1.5
		LOG::remove(logFileName_Main_Cycle_Clone);
		//2
		LOG::remove(logFileName_YardMap_Cycle);
		//4
		LOG::remove(logFileName_WmsCraneOrder_Selector);
		//5
		LOG::remove(logFileName_WatchDog_LiftCoil_Down_Phase);
		//8
		LOG::remove(logFileName_CraneAutoManuSwitchTracker);
		//9 
		LOG::remove(logFileName_HeatBeatMsg_Cycle);
	}
#pragma endregion


#pragma region 变量声明
protected:

	//cycle1.5
	CycSchedulePtr threadCycle_MainCycle_Clone;	

	//cycle2 Yard Map  Tracker
	CycSchedulePtr threadCycle_YardMap_Track;	

	//cycle4 WmsCraneOrder_Selector
	CycSchedulePtr threadCycle_WmsCraneOrder_Selector;

	//cycle5 WatchDog_LiftCoil_Down_Phase
	CycSchedulePtr threadCycle_WatchDog_LiftCoil_Down_Phase;

	//cycle8 Cycle CraneAlarmRecoder
	CycSchedulePtr threadCycle_CraneAutoManuSwitchTracker;

	//cycle9 cycle heatbeat msg
	CycSchedulePtr threadCycle_HeartBeatMsg;


private:

	//config file
	string bayNO;
	string craneNO;  //config item
	string strQueueOfCranesOrderByXIncrease;

	vector<string> vectorQueueOfCranesOrderByXIncrease;//行车的序列按照X从小到大的顺序

	string cranePLCStatusTopicName;

	string bayXMLFileName;

	map<string, SafteyAreaBase> mapSafeyArea;

	//end of config file


	// log file
	string logConfgFileFullName;
	string logFilePath;
	//
	string logFilePath_Alarm;
	//	
	string logFileName_Handle_Message;
	//
	string logFileName_Main_Cycle_Clone;
	//
	string logFileName_YardMap_Cycle;
	//
	string logFileName_WmsCraneOrder_Selector;
	//
	string logFileName_WatchDog_LiftCoil_Down_Phase;
	//
	string logFileName_CraneAutoManuSwitchTracker;
	//
	string logFileName_HeatBeatMsg_Cycle;


	YardMapTracker yardMap_Tracker;
	CraneAutoManuSwitch_Tracker   craneAutoManuSwitch_Tracker;

	WATCH_DOG_LIFT_COIL_DOWN_PHASE watchDogLiftCoilDownPhase;

	//2018.6.30 zhangyuhong add
	vector<long> vecOrderIDAlarmCodeLast;

	//2018.12.22 zhangyuhong add
	CranePLCStatusBase cranePLCStatus_Last;

#pragma endregion

	
};	

PACE_SERVER_INSTALL(APP_Crane);
