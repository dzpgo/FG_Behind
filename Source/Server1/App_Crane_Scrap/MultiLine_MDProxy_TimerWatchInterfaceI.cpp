
#include "MultiLine_MDProxy_TimerWatchInterfaceI.h"

#include "CranePLCStatusBase.h"
#include "CraneMonitor.h"

#include "CranePLCStatusStorm.h"


using namespace Monitor;
using namespace iPlature;
using namespace iMultiLink;

//1号行车Scheduler名称
const string MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_1="scheduler_1";
//2号行车Scheduler名称
const string MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_2="scheduler_2";
//3号行车Scheduler名称
const string MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_3="scheduler_3";
//4号行车Scheduler名称
const string MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_4="scheduler_4";

//PLC BadValue
const string MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE="?";


const  double MultiLine_MDProxy_TimerWatchInterfaceI:: motor_RPM_X=50;
const  double MultiLine_MDProxy_TimerWatchInterfaceI::motor_VPM_X=100;
const  double MultiLine_MDProxy_TimerWatchInterfaceI::motor_acc_X=0.208;

const  double MultiLine_MDProxy_TimerWatchInterfaceI:: motor_RPM_Y=50;
const  double MultiLine_MDProxy_TimerWatchInterfaceI::motor_VPM_Y=60;
const  double MultiLine_MDProxy_TimerWatchInterfaceI::motor_acc_Y=0.167;

MultiLine_MDProxy_TimerWatchInterfaceI::MultiLine_MDProxy_TimerWatchInterfaceI(string theCraneNO)
{
	myCraneNO=theCraneNO;
}


void MultiLine_MDProxy_TimerWatchInterfaceI::TimerWatch(const ::std::string& strScheduler,
														const ::iPlature::iMultiLink::MAPTAGVALUE& tagPairs,
														const Ice::Current& current)
{
	string functionName="MDProxy_TimerWatch";
	LOG log(functionName,"MDProxy");

	try
	{
		log.Debug()<<"SchedulerName:"<<strScheduler<<endl;
         string  cranePLCStatusTopicName = "";

		bool isCraneScheduler=false;
		string craneNO;

		if(strScheduler == MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_1) 
		{
			isCraneScheduler=true;
			craneNO="1";
			cranePLCStatusTopicName = "Crane/PLCStatusTopic_A";
		}
		if(strScheduler == MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_2) 
		{
			isCraneScheduler=true;
			craneNO="2";
			cranePLCStatusTopicName = "Crane/PLCStatusTopic_A";
		}
		if(strScheduler == MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_3) 
		{
			isCraneScheduler=true;
			craneNO="3";
			cranePLCStatusTopicName = "Crane/PLCStatusTopic_A";
		}
		if(strScheduler == MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_4) 
		{
			isCraneScheduler=true;
			craneNO="4";
			cranePLCStatusTopicName = "Crane/PLCStatusTopic_A";
		}
		

		if(isCraneScheduler==false)
		{
			return;
		}
		if(craneNO!=myCraneNO)
		{
			return;
		}

		log.Debug()<<"craneNO="<<craneNO<<endl;

		string adressHead=craneNO+"_";

		log.Debug()<<"adressHead="<<adressHead<<endl;

		

		CranePLCStatusBase  cranePLCStatus;

		cranePLCStatus.setCraneNO(craneNO);

		::iPlature::iMultiLink::MAPTAGVALUE::const_iterator iterMapTagValue;

		for (iterMapTagValue = tagPairs.begin(); iterMapTagValue != tagPairs.end(); iterMapTagValue++)
		{

			log.Debug()<<".............................................................................................................................................................................."<<endl;
			log.Debug()<<"Key:"<<iterMapTagValue->first<<" Value:"<<iterMapTagValue->second<<endl;

			string key=iterMapTagValue->first;
			string value=iterMapTagValue->second;
			

			//2控制模式
			if(key==adressHead + CranePLCStatusBase::ADRESS_CONTROL_MODE)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setControlMode( StringHelper::ToNumber<long>(value) );
				}
				else
				{
					cranePLCStatus.setControlMode(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus controlMode="<<cranePLCStatus.getControlMode()<<endl;
			}
			//2准备好
			if(key==adressHead + CranePLCStatusBase::ADRESS_READY)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setReady(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setReady(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus Ready="<<cranePLCStatus.getReady()<<endl;
			}

			//4急停状态
			if(key==adressHead+CranePLCStatusBase::ADRESS_EMG_STOP)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setEmgStop(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setEmgStop(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus emgStop="<<cranePLCStatus.getEmgStop()<<endl;
			}

			//5请求计划
			if(key==adressHead+CranePLCStatusBase::ADRESS_ASK_PLAN)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setAskPlan(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setAskPlan(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus askPlan="<<cranePLCStatus.getAskPlan()<<endl;
			}


			//6任务执行中
			if(key==adressHead+CranePLCStatusBase::ADRESS_TASK_EXCUTING)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setTaskExcuting(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setTaskExcuting(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus taskExcuting="<<cranePLCStatus.getTaskExcuting()<<endl;
			}

			//7大车正方向
			if(key==adressHead+CranePLCStatusBase::ADRESS_XDIR_P)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setXDirectPositive(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setXDirectPositive(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus xDirectPositive="<<cranePLCStatus.getXDirectPositive()<<endl;
			}

			//8大车负方向
			if(key==adressHead+CranePLCStatusBase::ADRESS_XDIR_N)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setXDirectNegative(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setXDirectNegative(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus xDirectNegative="<<cranePLCStatus.getXDirectNegative()<<endl;
			}


			//9小车正方向
			if(key==adressHead+CranePLCStatusBase::ADRESS_YDIR_P)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setYDirectPositive(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setYDirectPositive(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus yDirectPositive="<<cranePLCStatus.getYDirectPositive()<<endl;
			}


			//10小车负方向
			if(key==adressHead+CranePLCStatusBase::ADRESS_YDIR_N)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setYDirectNegative(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setYDirectNegative(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus yDirectNegative="<<cranePLCStatus.getYDirectNegative()<<endl;
			}


			//11升降正方向
			if(key==adressHead+CranePLCStatusBase::ADRESS_ZDIR_P)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setZDirectPositive(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setZDirectPositive(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus zDirectPositive="<<cranePLCStatus.getZDirectPositive()<<endl;
			}


			//12升降负方向
			if(key==adressHead+CranePLCStatusBase::ADRESS_ZDIR_N)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setZDirectNegative(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setZDirectNegative(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus zDirectNegative="<<cranePLCStatus.getZDirectNegative()<<endl;
			}


			//13有卷标志
			if(key==adressHead+CranePLCStatusBase::ADRESS_HAS_COIL)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setHasCoil(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setHasCoil(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus hasCoil="<<cranePLCStatus.getHasCoil()<<endl;
			}

			//14当前指令号
			if(key==adressHead+CranePLCStatusBase::ADRESS_ORDER_ID)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setOrderID(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setOrderID(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus orderID="<<cranePLCStatus.getOrderID()<<endl;
			}

			//15行车运行步骤
			if(key==adressHead+CranePLCStatusBase::ADRESS_RunStep)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setRunStep(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setRunStep(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus runStep="<<cranePLCStatus.getRunStep()<<endl;
			}

			//16大车方向实际速度
			if(key==adressHead+CranePLCStatusBase::ADRESS_XSPEED)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setXSpeed(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setXSpeed(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus xSpeed="<<cranePLCStatus.getXSpeed()<<endl;

				//if (abs(cranePLCStatus.getXSpeed()) > 0)
				//{
				//	cranePLCStatus.setXExcuting(1);
				//}
				//else
				//{
    //                cranePLCStatus.setXExcuting(0);
				//}
				//log.Debug()<<"cranePLCStatus xSpeed="<<cranePLCStatus.getXSpeed()<<endl;
			}

			//17小车方向实际速度
			if(key==adressHead+CranePLCStatusBase::ADRESS_YSPEED)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setYSpeed(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setYSpeed(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus ySpeed="<<cranePLCStatus.getYSpeed()<<endl;

				//if (abs(cranePLCStatus.getYSpeed()) > 0)
				//{
				//	cranePLCStatus.setYExcuting(1);
				//}
				//else
				//{
				//	cranePLCStatus.setYExcuting(0);
				//}
				//log.Debug()<<"cranePLCStatus xSpeed="<<cranePLCStatus.getYExcuting()<<endl;
			}

			//18升降实际速度
			if(key==adressHead+CranePLCStatusBase::ADRESS_ZSPEED)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setZSpeed(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setZSpeed(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus zSpeed="<<cranePLCStatus.getZSpeed()<<endl;

				//if (abs(cranePLCStatus.getZSpeed()) > 0)
				//{
				//	cranePLCStatus.setZExcuting(1);
				//}
				//else
				//{
				//	cranePLCStatus.setZExcuting(0);
				//}
				//log.Debug()<<"cranePLCStatus xSpeed="<<cranePLCStatus.getZExcuting()<<endl;

				//
				//cranePLCStatus.setRExcuting(0);
				//log.Debug()<<"cranePLCStatus xSpeed="<<cranePLCStatus.getZExcuting()<<endl;
			}

			//19大车位置
			if(key==adressHead+CranePLCStatusBase::ADRESS_XACT)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setXAct(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setXAct(CranePLCOrderBase::PLC_INT_NULL);
				}
				long tagValue=0;
				MultiLine_MDProxy_TimerWatchInterfaceI::readCraneStop(tagValue,craneNO);

				if(tagValue!=0 && tagValue!=999999)
				{
					cranePLCStatus.setXAct(tagValue);
				}
				log.Debug()<<"cranePLCStatus xAct="<<cranePLCStatus.getXAct()<<endl;
			}


			//20小车位置
			if(key==adressHead+CranePLCStatusBase::ADRESS_YACT)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setYAct(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setYAct(CranePLCOrderBase::PLC_INT_NULL);
				}

				long tagValue=0;
				MultiLine_MDProxy_TimerWatchInterfaceI::readCraneStop(tagValue,craneNO);

				if(tagValue!=0 && tagValue!=999999)
				{
					cranePLCStatus.setYAct(15000);
				}
				log.Debug()<<"cranePLCStatus yAct="<<cranePLCStatus.getYAct()<<endl;
			}

			//21夹钳高度
			if(key==adressHead+CranePLCStatusBase::ADRESS_ZACT)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setZAct(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setZAct(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus zAct="<<cranePLCStatus.getZAct()<<endl;
			}
			

			//22称重信号
			if(key==adressHead+CranePLCStatusBase::ADRESS_WEIGHT_LOADED)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setWeightLoaded(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setWeightLoaded(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus weightLoaded="<<cranePLCStatus.getWeightLoaded()<<endl;
			}


			//23夹钳旋转角度
			if(key==adressHead+CranePLCStatusBase::ADRESS_DIP_ANGLE_ACT)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setDipAngleAct(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setDipAngleAct(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus dipAngleAct="<<cranePLCStatus.getDipAngleAct()<<endl;
			}


			//24X轴当前目标位
			if(key==adressHead+CranePLCStatusBase::ADRESS_CurrTarg_X)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setCurrTargX(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setCurrTargX(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus currTargX="<<cranePLCStatus.getCurrTargX()<<endl;
			}

			//25Y轴当前目标位
			if(key==adressHead+CranePLCStatusBase::ADRESS_CurrTarg_Y)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setCurrTargY(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setCurrTargY(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus currTargY="<<cranePLCStatus.getCurrTargY()<<endl;
			}

			//26Z轴当前目标位
			if(key==adressHead+CranePLCStatusBase::ADRESS_CurrTarg_Z)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setCurrTargZ(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setCurrTargZ(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus currTargZ="<<cranePLCStatus.getCurrTargZ()<<endl;
			}
			
			//27计划起卷X
			if(key==adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_X)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setPlanUpX(StringHelper::ToNumber<long>(value) );
				}
				else
				{
					cranePLCStatus.setPlanUpX(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus planUpX="<<cranePLCStatus.getPlanUpX()<<endl;
			}


			//28计划起卷Y
			if(key==adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_Y)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setPlanUpY(StringHelper::ToNumber<long>(value) );
				}
				else
				{
					cranePLCStatus.setPlanUpY(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus planUpY="<<cranePLCStatus.getPlanUpY()<<endl;
			}


			//29计划起卷Z
			if(key==adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_Z)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setPlanUpZ(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setPlanUpZ(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus planUpZ="<<cranePLCStatus.getPlanUpZ()<<endl;
			}


			//30计划落卷X
			if(key==adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_X)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setPlanDownX(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setPlanDownX(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus planDownX="<<cranePLCStatus.getPlanDownX()<<endl;
			}


			//31计划落卷Y
			if(key==adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_Y)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setPlanDownY(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setPlanDownY(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus planDownY="<<cranePLCStatus.getPlanDownY()<<endl;
			}

			//32计划落卷Z
			if(key==adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_Z)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setPlanDownZ(StringHelper::ToNumber<long>(value) );
				}
				else
				{
					cranePLCStatus.setPlanDownZ(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus planDownZ="<<cranePLCStatus.getPlanDownZ()<<endl;
			}


			//33故障代码0
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_0)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode0(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode0(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode0="<<cranePLCStatus.getFaultCode0()<<endl;
			}

			//34故障代码1
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_1)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode1(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode1(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode1="<<cranePLCStatus.getFaultCode1()<<endl;
			}

			//35故障代码2
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_2)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode2(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode2(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode2="<<cranePLCStatus.getFaultCode2()<<endl;
			}

			//36故障代码3
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_3)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode3(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode3(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode3="<<cranePLCStatus.getFaultCode3()<<endl;
			}

			//37故障代码4
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_4)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode4(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode4(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode4="<<cranePLCStatus.getFaultCode4()<<endl;
			}

			//38故障代码5
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_5)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode5(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode5(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode5="<<cranePLCStatus.getFaultCode5()<<endl;
			}

			//39故障代码6
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_6)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode6(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode6(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode6="<<cranePLCStatus.getFaultCode6()<<endl;
			}

			//40故障代码7
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_7)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode7(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode7(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode7="<<cranePLCStatus.getFaultCode7()<<endl;
			}

			//41故障代码8
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_8)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode8(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode8(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode8="<<cranePLCStatus.getFaultCode8()<<endl;
			}

			//42故障代码9
			if(key==adressHead+CranePLCStatusBase::ADRESS_FaultCode_9)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setFaultCode9(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setFaultCode9(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus faultCode9="<<cranePLCStatus.getFaultCode9()<<endl;
			}

			//42Heart
			if(key==adressHead+CranePLCStatusBase::ADRESS_Heart)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setHeart(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setHeart(CranePLCOrderBase::PLC_INT_NULL);
				}
				log.Debug()<<"cranePLCStatus heart="<<cranePLCStatus.getHeart()<<endl;
			}

			////fangyao_alarm_list
			//if(key==adressHead+CranePLCStatusBase::ADRESS_ANTI_WAVE_ALARM_LIST)
			//{
			//	if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
			//	{

			//		Transform_AntiWave_AlarmList(StringHelper::ToNumber<unsigned int>(value), craneNO);
			//	}
			//	log.Debug()<<"cranePLCStatus setTimeReceive="<<cranePLCStatus.getTimeReceive()<<endl;
			//}

			////放水标志  2018-03-08
			//if(key==adressHead+CranePLCStatusBase::WATERLEVEL_FLAG)
			//{
			//	if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
			//	{
			//		cranePLCStatus.setwaterLevelFlag(StringHelper::ToNumber<long>(value));
			//	}
			//	else
			//	{
			//		cranePLCStatus.setwaterLevelFlag(CranePLCOrderBase::PLC_INT_NULL);
			//	}
			//	log.Debug()<<"cranePLCStatus waterLevel_Flag="<<cranePLCStatus.getwaterLevelFlag()<<endl;
			//}

			
			//damned_laser  20180420
			/*if(key==adressHead+CranePLCStatusBase::DAMMED_LASER)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setDamnedLaser(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setDamnedLaser(0);
				}
				log.Debug()<<"cranePLCStatus DAMMED_LASER="<<cranePLCStatus.getDamnedLaser()<<endl;
			}*/

			//Reduce_the_magnetic 20180521
			/*if(key==adressHead+CranePLCStatusBase::REDUCE_MAGNETIC)
			{
				if(value != MultiLine_MDProxy_TimerWatchInterfaceI::PLC_BAD_VALUE)
				{
					cranePLCStatus.setReduceMagnetic(StringHelper::ToNumber<long>(value));
				}
				else
				{
					cranePLCStatus.setReduceMagnetic(0);
				}
				log.Debug()<<"cranePLCStatus ReduceMagnetic="<<cranePLCStatus.getReduceMagnetic()<<endl;
			}*/

		

		}


		//当行车断电时，数据为0，不发布订阅
		if(cranePLCStatus.getXAct()==CranePLCOrderBase::PLC_INT_NULL || cranePLCStatus.getYAct()==CranePLCOrderBase::PLC_INT_NULL )
		{
			log.Debug()<<"XAct = "<<cranePLCStatus.getXAct()<<endl;
			log.Debug()<<"YAct = "<<cranePLCStatus.getYAct()<<endl;
			log.Debug()<<"ZAct = "<<cranePLCStatus.getZAct()<<endl;
			log.Debug()<<"do not dispatch the topic name,will return..............."<<endl;

			
			return ;
		}


		log.Debug()<<" now try to input the PLC Status to Crane Monitor Class................................................"<<endl;
		CraneMonitor::getInstance()->inputPLCStatus( cranePLCStatus );

		//发布Storm主题的信息给其他订阅者
		//log.Debug()<<" now try to dispatch the topic name="<<cranePLCStatusTopicName<<"................................................"<<endl;
		//CLTS::CranePLCStatusDesc desc=CranePLCStatusBase::TransFromClass(cranePLCStatus);

		//CLTS::CranePublisher cranePublisher;
		//cranePublisher = getPublishProxy<CLTS::CranePublisher>(cranePLCStatusTopicName); 
		//cranePublisher->CWatchEventHandlerI(desc);

		if(craneNO==myCraneNO)
		{
			log.Debug()<<"write cranePLCStatus to Tag System............................................................. "<<endl;
			log.Debug() << "the craneNO = " << craneNO  << "=======" << myCraneNO << "======"<<endl;
			TAGVALUEMAP Tags;
			cranePLCStatus.wirteValues2TagSystem(Tags);
			//tag点写入系统
			TAGVALUEMAP TagTimeStamp;
		  Tag::GetInst().MDPut(TagTimeStamp,Tags);	

			log.Debug()<<"Crane tags written to tag system .........OK"<<endl;
			log.Debug()<<"write cranePLCStatus to Tag System end ............................................................. "<<endl;

		}
		//if(craneNO == "8")
		//{
		//	log.Debug()<<"write 8# cranePLCStatus to Tag System............................................................. "<<endl;
		//	cranePLCStatus.wirteValues2TagSystem();
		//	log.Debug()<<"write 8# cranePLCStatus to Tag System end ............................................................. "<<endl;
		//}

	}
	catch(iDA::Exception &x)
	{
		try
		{
			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
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

}





string MultiLine_MDProxy_TimerWatchInterfaceI :: getSchedulerName(string craneNO)
{
	if(craneNO=="1")
	{
		return MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_1;
	}
	else if(craneNO=="2")
	{
		return MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_2;
	}
	else if(craneNO=="3")
	{
		return MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_3;
	}
	else if (craneNO=="4")
	{
		return MultiLine_MDProxy_TimerWatchInterfaceI::SCHEDULER_NAME_CRANE_4;
	}
	
	return DB_STR_NULL;

}





void MultiLine_MDProxy_TimerWatchInterfaceI::Transform_AntiWave_AlarmList(unsigned int theVal, string craneNO)//2018-03-06 周立民 增加行车号参数
{
	string functionName="MultiLine_MDProxy_TimerWatchInterfaceI :: Transform_AntiWave_AlarmList()";

	CranePLCStatusBase cranePLCStatusBase;

	LOG log(functionName, "MDProxy");

	try
	{
		log.Debug()<<"..........................................................................................................................................................................................................."<<endl;
		log.Debug()<<"theVal="<<theVal<<endl;


		unsigned int one=1;

		bool l_stBoardWeitch[32];


		//拆分编码为二进制
		int i=0;

		for(int i=0;i<32;i++)
		{
			if( (theVal & one)==one)
			{
				l_stBoardWeitch[i]=1;
				log.Debug()<<"1"<<endl;
			}
			else
			{
				l_stBoardWeitch[i]=0;
				log.Debug()<<"0"<<endl;
			}
			theVal=theVal>>1;
		}

		//写拆分结果进入tag

		if(craneNO==myCraneNO)   //2018-03-06 周立民 增加行车号判断，是自己行车的报警才写入tag
		{

			TAGVALUEMAP Tags;

			string addressHead=myCraneNO+"_";
			string tagName=addressHead+"fangyao_alarm_list";
			log.Debug()<<"tagName="<<tagName<<endl;
			string tagValue;

			for(i=0;i<32;i++)
			{
				log.Debug()<<i<<"="<<l_stBoardWeitch[i]<<endl;
				if(l_stBoardWeitch[i]==true)
				{
					tagValue+="1";
				}
				else
				{
					tagValue+="0";
				}
				if(i<31)
				{
					tagValue+=",";
				}

			}

			Tags.insert(map<string,string>::value_type( tagName , tagValue ) );

			//tag点写入系统
			TAGVALUEMAP TagTimeStamp;
			Tag::GetInst().MDPut(TagTimeStamp,Tags);	
		}

		log.Debug()<<"..........................................................................................................................................................................................................."<<endl;
	}
	catch(iDA::Exception &x)
	{
		try
		{
			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
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

}


void  MultiLine_MDProxy_TimerWatchInterfaceI::readCraneStop(long &tagValue, string craneNO)
{

	
	string functionName="MultiLine_MDProxy_TimerWatchInterfaceI :: readCraneStop()";
	LOG log(functionName, "MDProxy");

	tagValue= CranePLCOrderBase::PLC_INT_NULL;

	try
	{
		

		::iPlature::TAGNAMEARRAY vectorTagNames;
		::iPlature::TAGVALUEMAP mapTagValues;

		string tagName=craneNO+"_CraneStop";
		vectorTagNames.push_back(tagName );
		//log.Debug()<<"readWaterTagFromHMI  "<<endl;
		log.Debug()<<"tagName="<<tagName<<endl;
		Tag::GetInst().GetActual(vectorTagNames, mapTagValues);

		if(mapTagValues.find(tagName)!=mapTagValues.end())
		{
			tagValue=StringHelper::ToNumber<long>((mapTagValues.find(tagName))->second);
		}
		log.Debug()<<"tagValue="<<tagValue<<endl;


	}
	catch(iDA::Exception &x)
	{
		try
		{
			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}

		string msg = functionName +"   error:"+ x.ErrMsg();
		log.Debug()<<msg<<endl;
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

}