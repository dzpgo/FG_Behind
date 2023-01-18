
#pragma region ͷ�ļ�

//==================ƽ̨ͷ�ļ�==============================
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

//==================Ӧ��ͷ�ļ�==============================
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

#pragma region PostInitCall-ģ���ʼ��
	void PostInitCall()
    {
		LOG log("PostInitCall");


		//���ݿ�����
		CDataAccess::GetInstance()->Initialize();

		try
		{
		    log.Info()<<"APP_Crane in PostInitCall"<<endl;
			
			iPlature::MsgTubePtr heatServicePtr = new iPlature::MsgTubeI(this);

			Ice::PropertiesPtr ptrProp = Component::instance()->properties();
 

			log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                            ��ȡ�����ļ�           read from config file                                                                                                    "<<endl;
			log.Info()<<endl<<"****************************************************************************************************************************."<<endl; 

			
			//�����ļ��ж� �г���
			craneNO = ptrProp->getPropertyWithDefault("CraneNO", "");
			StringHelper::Trim(craneNO);
			log.Debug()<<"craneNO="<<craneNO<<endl;

			//�����ļ��ж� ���
			bayNO=ptrProp->getPropertyWithDefault("bayNO", "");
			StringHelper::Trim(bayNO);
			log.Debug()<<"bayNO="<<bayNO<<endl;			

			//�����ļ��ж� �ÿ������е��г��ţ��г������а���X��С�����˳��
			strQueueOfCranesOrderByXIncrease=ptrProp->getPropertyWithDefault("queueOfCranesOrderByXIncrease", "");
			log.Debug()<<"strQueueOfCranesOrderByXIncrease="<<strQueueOfCranesOrderByXIncrease<<endl;

			vectorQueueOfCranesOrderByXIncrease= StringHelper::ToVector<string>(strQueueOfCranesOrderByXIncrease, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA)));

			//��ȡ�����ļ���StormTop����
			cranePLCStatusTopicName=ptrProp->getPropertyWithDefault("cranePLCStatusTopicName", "");
			log.Debug()<<"cranePLCStatusTopicName="<<cranePLCStatusTopicName<<endl;

			//��ȡ�����ļ���Bay��XML�����ļ�����
			bayXMLFileName=ptrProp->getPropertyWithDefault("bayXMLName", "");
			log.Debug()<<"bayXMLFileName="<<bayXMLFileName<<endl;

			//2018.6.30 zhangyuhong add
			vecOrderIDAlarmCodeLast.clear();
			vecOrderIDAlarmCodeLast.push_back(DB_INT_NULL);
			vecOrderIDAlarmCodeLast.push_back(DB_INT_NULL);
			
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                  ����iPlature������         create service name for iplature                                                                                     "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 

			// ��֯ICEGrid�й�����ServiceName
		    string strServiceNameAll = "iPlature/APP_Crane_" + craneNO;
		    this->add(strServiceNameAll, heatServicePtr);
			log.Debug()<<"strServiceNameAll="<<strServiceNameAll<<endl;


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                 ����Log�ļ�·�����ļ���           define log files                                                                                                      "<<endl;
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

			//��ʼ������
			InitPowertranserData();

			LOG::doConfigure("MDProxy" ,  logConfgFileFullName , logFilePath ,BRANCH_CONFIG);
			LOG::doConfigure("EvadeRequestReceiver",logConfgFileFullName,logFilePath, BRANCH_CONFIG);

			//SRS���ⷴ������tag���յ�������־
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
			log.Info()<<"                                                                      ����MDProxy���tag�ָ�����ģʽ����Ҫȡ������                      "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//*iMultiLink::TimerWatchInterfacePtr mdProxy = new iMultiLink::MultiLine_MDProxy_TimerWatchInterfaceI(craneNO);
			//this->subscribe("iMultiLink/TimerWatchTopic", mdProxy);*/
			iPlature::iMultiLink::TimerWatchInterfacePtr  mdProxy = new  iMultiLink::MultiLine_MDProxy_TimerWatchInterfaceI(craneNO);
			//this->subscribe("iMultiLink/TimerWatchTopic", mdProxy);
		    this->subscribe("iMultiLink/TimerWatchTopic", mdProxy);


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      Start MainCycle_Clone                                                                                                           "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//�����߳�
			threadCycle_MainCycle_Clone = CycSchedule::GetObject("MainCycle_Clone");
			threadCycle_MainCycle_Clone->registerMethod(this,(CycSchedule::Method)&APP_Crane::MainCycle_Clone, 1);//
			//�����߳�
			threadCycle_MainCycle_Clone->startScheduling(CycSchedule::ORDERED);
			
			

			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      Start Yard Map Tracker  Cycle                                                                                                               "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			InitTrackTagValue();
			//�����߳�
			threadCycle_YardMap_Track= CycSchedule::GetObject("YardMapCycle");
			threadCycle_YardMap_Track->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_YardMap_Track, 1);
		    //�����߳�
			threadCycle_YardMap_Track->startScheduling(CycSchedule::ORDERED);
			

			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      WmsCraneOrderSelector  Cycle                                                                                                                                  "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//�����߳�
			threadCycle_WmsCraneOrder_Selector= CycSchedule::GetObject("Cycle_WmsCraneOrder_Selector");
			threadCycle_WmsCraneOrder_Selector->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_WmsCraneOrder_Selector, 2);
		    //�����߳�
			threadCycle_WmsCraneOrder_Selector->startScheduling(CycSchedule::ORDERED);

					
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      WATCH_DOG_LIFT_COIL_DOWN_PHASE                                                                                                       "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//�����߳�
			threadCycle_WatchDog_LiftCoil_Down_Phase= CycSchedule::GetObject("Cycle_WatchDog_LiftCoil_Down_Phase");
			threadCycle_WatchDog_LiftCoil_Down_Phase->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_WatchDog_LiftCoil_Down_Phase, 1);
		    //�����߳�
			threadCycle_WatchDog_LiftCoil_Down_Phase->startScheduling(CycSchedule::ORDERED);		


			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                      Start CraneAutoManuSwitchTracker  CYCLE                                                                                     "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//�����߳�
			threadCycle_CraneAutoManuSwitchTracker= CycSchedule::GetObject("Cycle_CraneAutoManuSwitchTracker");
			threadCycle_CraneAutoManuSwitchTracker->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_CraneAutoManuSwitchTracker, 1);
		    //�����߳�
			threadCycle_CraneAutoManuSwitchTracker->startScheduling(CycSchedule::ORDERED);

			//2017.12.11 zhangyuhong add ���г�������������
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			log.Info()<<"                                                                      Start Sending to CranePLC HeartBeat Msg                                                                       "<<endl;
			log.Info()<<"****************************************************************************************************************************."<<endl; 
			//�����߳�
			threadCycle_HeartBeatMsg = CycSchedule::GetObject("Cycle_HeartBeatMsg");
			threadCycle_HeartBeatMsg->registerMethod(this,(CycSchedule::Method)&APP_Crane::Cycle_HeartBeatMsg, 1);//
			//�����߳�
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
		//��ʼ��tracktag�㣺CRANE_NO+_ACTIONS_TRACKER
		TAGVALUEMAP mapTagValue;
		string tagName = craneNO + "_ACTIONS_TRACKER";
		mapTagValue.insert(map<string,string>::value_type(tagName , "INIT"));
		TAGVALUEMAP TagTimeStamp;
		Tag::GetInst().MDPut(TagTimeStamp,mapTagValue);
	}
#pragma endregion


#pragma region InitPowertranserData
	//��ʼ��poerTranser
	void InitPowertranserData()
	{
		MsgNameArray_t arry;

		//��ȫPLC����
		arry.push_back("SU01");
		arry.push_back("SU02");	
		
		//�г�PLC����
		arry.push_back("CU01");
		arry.push_back("CU02");	

		MsgSmartDataManager::InsRef().InitMsgSmartData(arry);
	}
#pragma endregion


#pragma region 0-HandleMessage 
	//���Ľ������  ֱ�ӽ��հ汾
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
		log.InfoHex(stRecvMsg.textbuf,(ParamBuffer.size()-16));//�������ݳ���=�����ܳ���-����ͷ-������
		ByteSeq teleBuffer;
		teleBuffer<<stRecvMsg.textbuf;

		try
		{		
			//CREU01 �г�״̬��Ϣ
			if( msgID == "CU01")
			{
				//MsgCREU01::getInstance()->HandleMessage(craneNO, cranePLCStatusTopicName,teleBuffer, vecOrderIDAlarmCodeLast, cranePLCStatus_Last);
			}
			//CREU02 �г�������Ϣ
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
		//�ӳ�100ms ��ȡ��֮���ı���tag��
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

		//ѭ������ͳ��
		int nWaitDuration = 0;		
		try
		{
			while(true)
			{

								log.Info()<<"*******************************************************************************************************************************************"<<endl; 
								log.Info()<<"                                                                                       Cycle_WmsCraneOrder_Selector Start                                                                                        " <<endl; 
								log.Info()<<"*******************************************************************************************************************************************"<<endl; 

								

								//-----------------------------------��ǰָ�����--------------------------------------------------------------------------------------------------------------------------------

								OrderCurrentBase  orderCurrent;							     
								orderCurrent=Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

								//2019.4.24 zhangyuhong add
								//������е�ǰָ�����������صǳ�λָ����⣩����continue
								if(orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY )
								{
										if ( orderCurrent.getOrderType() != "X1")
										{											
												log.Info()<<"�г�ָ��״̬CMDStatus��Ϊ����STATUS_EMPTY���Ҳ��ǻصǳ�λָ�Sleep-->Continue......."<<endl;
#ifdef WIN32
												Sleep(intervel);
#else
												sleep(intervel);
#endif
												continue;
										}
								}

								//-----------------------------------�г����ؼ����յ��--------------------------------------------------------------------------------------------------------------------------------
								CranePLCStatusBase cranePLCStatusBase;
								CraneMonitor::getInstance()->getPLCStatus(cranePLCStatusBase);

								//2018.12.11 zhangyuhong add
								if( !ACTION_COMMON_FUNCTION::CustomOffice_Is_Auto_Ready_AskPlan(craneNO,cranePLCStatusBase) ) //2019.4.24 zhangyuhong add  �������ûͨ�����ҵ�ǰָ�����ָ������ ��Ϊ �صǳ�λָ��
								{
									if ( orderCurrent.getOrderType() != "X1" )
									{
										log.Info()<<"�г�PLC���ؼ�鲻ͨ�����ҵ�ǰ����ִ��ָ��ǻصǳ�λָ�Sleep-->Continue........ "<<endl;
#ifdef WIN32
										Sleep(intervel);
#else
										sleep(intervel);
#endif
										continue;
									}
								}

								//-----------------------------------ָ���������--------------------------------------------------------------------------------------------------------------------------------

								//2018.1.26 zhangyuhong add
								//ָ������ tag�㣺tagֵ=1 ָ��������ִ���굱ǰָ��󣬺���3-1��ָ����ͣ�ͬʱҲ������3-2
								//ǰ����hascoil=0
								if (cranePLCStatusBase.getHasCoil() == 0 && ACTION_COMMON_FUNCTION::GetTagValue(craneNO, "_HMI_A6_ORDER_LOCK") == "1")
								{
									log.Info() << "��⵽��>>ָ������<<���г���CraneNO="<<craneNO<<"�ĺ���ָ��ٽ��գ�"<< endl;
									
									if (cranePLCStatusBase.getHasCoil() == 0 )//&& ACTION_COMMON_FUNCTION::GetTagValue(craneNO, "_ORDER_BOARDMOVING") == "1")
									{
										log.Info() << "�г�ָ�����������ٽ��պ���ָ��г��չ��޾��г�׼�����صǳ�λ.......Test_Evade_Move::Test_BoardingMoving()......" << endl;
										//2019.4.24 zhangyuhong add
										//дָ���ʽ �صǳ�λָ��
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
								//����г��ع�����ָ��˳����й��ڴ��г�������ָ���״̬����1������Ϊ�˵��޷�ʶ��������ָ��г�����ȡָ�������ʾ������Ҫ�ֶ�����
								if (cranePLCStatusBase.getHasCoil() != 0)
								{
									//��ȡ��ǰָ��˳�����ָ��״̬Ϊ��0�ļ�¼������У����������û�У�����
									if ( Adapter_UACS_CRANE_ORDER_CURRENT::getStautsNot1Order(craneNO) == false )
									{
										log.Info()<<"�г���ǰ�ع�������ָ��˳������� ����ִ�� ָ�״̬��0�ģ�"<<endl;
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


								//-----------------------------------�г��صǳ�λ���--------------------------------------------------------------------------------------------------------------------------------

								//2019.3.18 zhangyuhong add
								//����HMI�Ļصǳ�λ��tag�㹦��
								//string tagValueHMIReturn = ACTION_COMMON_FUNCTION::GetTagValue(craneNO, "GGGGG");
								log.Info() << "�г���ǰ��ָ����л�ȡ����ָ���ǰ��ָ�30��󣬻صǳ�λ��" << endl;
								log.Info() << "��ǰ������ nWaitDuration = "<< nWaitDuration << endl;
								//ͳ����ָ��ѭ���Ĵ���
								nWaitDuration ++;
								//����ȴ�10����г�һֱ��ָ������г��صǳ�λ��ͬʱ��nWaitDuration=0
								//2018.12.29 zhangyuhobng add
								//�޸���ָ���ȡ���ڣ����Եȴ�ʱ����Ϊ5��
								//if (nWaitDuration > 5 || tagValueHMIReturn == "1")
								if (nWaitDuration > 5 )
								{
									//���û��ָ����г���ǰ�չ��޾��г��صǳ�λ								
									if ( cranePLCStatusBase.getHasCoil() == 0 )
									{
										log.Info() << "�г�ָ��˳���(UACS_SCHEDULE_ORDER_QUEUE)���޵�ǰ�г���ָ��г��չ��޾��г�׼�����صǳ�λ.......Test_Evade_Move::Test_BoardingMoving()......" << endl;
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
	//���г�����sending heatbeat msg
	void Cycle_HeartBeatMsg(const float para)
	{
		//IceUtil::Mutex::Lock lock(m_mutex_YardMap);

		string functionName="APP_Crane :: Cycle_HeartBeatMsg()";

		LOG::doConfigure(logFileName_HeatBeatMsg_Cycle , logConfgFileFullName , logFilePath ,THREAD_CONFIG);

		LOG log(functionName, AUTO_CATCH_PID);

		CranePLCOrderBase cranePLCOrderbase;

		
		cranePLCOrderbase.setCraneNO(craneNO);
		cranePLCOrderbase.setShortCmd(900);//900--�������ı�� 
		cranePLCOrderbase.setOrderID(0);//ָ���Ϊ0--�⼴��������
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
					log.Debug()<<"..................... �������ķ����г�PLC  OK !"<<endl;
				else
					log.Error()<<"..................... �������ķ����г�PLC  ERROR !"<<endl;*/
				
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


#pragma region ��������
	/** 
	* ����
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


#pragma region ��������
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

	vector<string> vectorQueueOfCranesOrderByXIncrease;//�г������а���X��С�����˳��

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
