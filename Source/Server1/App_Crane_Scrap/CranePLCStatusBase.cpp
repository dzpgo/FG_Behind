#include "CranePLCStatusBase.h"

using namespace Monitor;
using namespace CLTS;

//--------------------------------------------------行车设备状态定义----------------------------------------------------------------
//空钩起升过程= 000;
const long CranePLCStatusBase::STATUS_NEED_TO_READY=0;
//空钩等待状态= 010
const long CranePLCStatusBase::STATUS_WAITING_ORDER_WITH_OUT_COIL=10;
//空钩走行状态= 020
const long CranePLCStatusBase::STATUS_MOVING_WITH_OUT_COIL=20;
//空钩走行到位状态= 030
const long CranePLCStatusBase::STATUS_ARRIVED_POS_WITH_OUT_COIL=30;
//空钩下降去取卷= 040
const long CranePLCStatusBase::STATUS_LIFT_COIL_DOWN_PHASE=40;
//钢卷起吊= 050
const long CranePLCStatusBase::STATUS_COIL_LIFTED=50;
//重钩起升过程= 060
const long CranePLCStatusBase::STATUS_LIFT_COIL_UP_PHASE=60;
//重钩等待状态= 070
const long CranePLCStatusBase::STATUS_WAITING_ORDER_WITH_COIL=70;
//重钩走行状态= 080
const long CranePLCStatusBase::STATUS_MOVING_WITH_COIL=80;
//重钩走行到位= 090
const long CranePLCStatusBase::STATUS_ARRIVED_POS_WITH_COIL=90;
//重钩下降去落卷= 100
const long CranePLCStatusBase::STATUS_DOWN_COIL_DOWN_PHASE=100;
//钢卷落关= 110
const long CranePLCStatusBase::STATUS_COIL_DOWN=110;


 //--------------------------------------------------行车控制模式定义----------------------------------------------------------------
 //遥控模式
 const long CranePLCStatusBase::CONTROL_MODE_REMOTE_CONTROL=1;
 //司机模式
 const long CranePLCStatusBase::CONTROL_MODE_DRIVER_CONTROL=2;
 //半自动模式
 const long CranePLCStatusBase::CONTROL_MODE_HALF_AUTO=3;
 //全自动模式
 const long CranePLCStatusBase::CONTROL_MODE_AUTO=4;


//---------------------------------------------------------------------------------------------------------------------------------------------------
 //2控制模式
 const  string  CranePLCStatusBase::ADRESS_CONTROL_MODE="CONTROL_MODE";
 //3准备好
 const  string CranePLCStatusBase::ADRESS_READY="READY";
 //4急停状态
 const  string CranePLCStatusBase::ADRESS_EMG_STOP="EMG_STOP";
 //5请求计划
 const  string CranePLCStatusBase::ADRESS_ASK_PLAN="ASK_PLAN";
 //6任务执行中
 const  string CranePLCStatusBase::ADRESS_TASK_EXCUTING="TASK_EXCUTING";
 //7大车正方向<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_XDIR_P="XDIR_P";
 //8大车负方向<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_XDIR_N="XDIR_N";
 //9小车正方向<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_YDIR_P="YDIR_P";
 //10小车负方向<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_YDIR_N="YDIR_N";
 //11升降正方向<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_ZDIR_P="ZDIR_P";
 //12升降负方向<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_ZDIR_N="ZDIR_N";
 //13有卷标志
 const  string CranePLCStatusBase::ADRESS_HAS_COIL="HAS_COIL";
 //14当前指令号
 const  string CranePLCStatusBase::ADRESS_ORDER_ID="ORDER_ID";
 //15行车运行步骤
 const  string CranePLCStatusBase::ADRESS_RunStep="RunStep";
 //16大车方向实际速度<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_XSPEED="XSPEED";
 //17小车方向实际速度<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_YSPEED="YSPEED";
 //18升降实际速度<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_ZSPEED="ZSPEED";
 //19大车位置
 const  string CranePLCStatusBase::ADRESS_XACT="XACT";
 //20小车位置
 const  string CranePLCStatusBase::ADRESS_YACT="YACT";
 //21吸盘高度
 const  string CranePLCStatusBase::ADRESS_ZACT="ZACT";
 //22称重信号<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_WEIGHT_LOADED="WEIGHT_LOADED";
 //23倾斜角度<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_DIP_ANGLE_ACT="DIP_ANGLE_ACT";
 //24X轴当前目标位
 const  string CranePLCStatusBase::ADRESS_CurrTarg_X="CurrTarg_X";
 //25Y轴当前目标位
 const  string CranePLCStatusBase::ADRESS_CurrTarg_Y="CurrTarg_Y";
 //26Z轴当前目标位
 const  string CranePLCStatusBase::ADRESS_CurrTarg_Z="CurrTarg_Z";
 //27计划起卷X
 const  string CranePLCStatusBase::ADRESS_PLAN_UP_X="PLAN_UP_X";
 //28计划起卷Y
 const  string CranePLCStatusBase::ADRESS_PLAN_UP_Y="PLAN_UP_Y";
 //29计划起卷Z
 const  string CranePLCStatusBase::ADRESS_PLAN_UP_Z="PLAN_UP_Z";
 //30计划落卷X
 const  string CranePLCStatusBase::ADRESS_PLAN_DOWN_X="PLAN_DOWN_X";
 //31计划落卷Y
 const  string CranePLCStatusBase::ADRESS_PLAN_DOWN_Y="PLAN_DOWN_Y";
 //32计划落卷Z
 const  string CranePLCStatusBase::ADRESS_PLAN_DOWN_Z="PLAN_DOWN_Z";
 //33故障代码0
 const  string CranePLCStatusBase::ADRESS_FaultCode_0="FaultCode_0";
 //34故障代码1
 const  string CranePLCStatusBase::ADRESS_FaultCode_1="FaultCode_1";
 //35故障代码2
 const  string CranePLCStatusBase::ADRESS_FaultCode_2="FaultCode_2";
 //36故障代码3
 const  string CranePLCStatusBase::ADRESS_FaultCode_3="FaultCode_3";
 //37故障代码4
 const  string CranePLCStatusBase::ADRESS_FaultCode_4="FaultCode_4";
 //38故障代码5
 const  string CranePLCStatusBase::ADRESS_FaultCode_5="FaultCode_5";
 //39故障代码6
 const  string CranePLCStatusBase::ADRESS_FaultCode_6="FaultCode_6";
 //40故障代码7
 const  string CranePLCStatusBase::ADRESS_FaultCode_7="FaultCode_7";
 //41故障代码8
 const  string CranePLCStatusBase::ADRESS_FaultCode_8="FaultCode_8";
 //42故障代码9
 const  string CranePLCStatusBase::ADRESS_FaultCode_9="FaultCode_9";
 //43心跳
 const string CranePLCStatusBase::ADRESS_Heart="Heart";

CranePLCStatusBase :: CranePLCStatusBase(void)
{

	initValues();
}



CranePLCStatusBase :: ~CranePLCStatusBase(void)
{
	


}

void CranePLCStatusBase :: initValues()
{
	//1 craneNO
	craneNO=DB_STR_NULL;

	//2 controlMode
	controlMode=DB_INT_NULL;

	//3 ready
	ready=DB_INT_NULL;

	//4 emgStop
	emgStop=DB_INT_NULL;
	
	//5 askPlan
	askPlan=DB_INT_NULL;

	//6 taskExcuting
	taskExcuting=DB_INT_NULL;

	//7 xDirectPositive
	xDirectPositive=DB_INT_NULL;

	//8 xDirectNegative
	xDirectNegative=DB_INT_NULL;

	//9 yDirectPositive
	yDirectPositive=DB_INT_NULL;

	//10 yDirectNegative
	yDirectNegative=DB_INT_NULL;

	//11 zDirectPositive
	zDirectPositive=DB_INT_NULL;

	//12 zDirectNegative
	zDirectNegative=DB_INT_NULL;

	//13 hasCoil
	hasCoil=DB_INT_NULL;

	//14 orderID
	orderID=DB_INT_NULL;

	//15 runStep
	runStep=DB_INT_NULL;

	//16 xSpeed
	xSpeed=DB_INT_NULL;

	//17 ySpeed
	ySpeed=DB_INT_NULL;

	//18 zSpeed
	zSpeed=DB_INT_NULL;

	//19 xAct
	xAct=DB_INT_NULL;

	//20 yAct
	yAct=DB_INT_NULL;

	//21 zAct
	zAct=DB_INT_NULL;

	//22 weightLoaded
	weightLoaded=DB_INT_NULL;

	//23 dipAngleAct
	dipAngleAct=DB_INT_NULL;

	//24 currTargX
	currTargX=DB_INT_NULL;

	//25 currTargY
	currTargY=DB_INT_NULL;

	//26 currTargZ
	currTargZ=DB_INT_NULL;

	//27 planUpX
	planUpX=DB_INT_NULL;

	//28 planUpY
	planUpY=DB_INT_NULL;

	//29 planUpZ
	planUpZ=DB_INT_NULL;

	//30 planDownX
	planDownX=DB_INT_NULL;

	//31 planDownY
	planDownY=DB_INT_NULL;

	//32 planDownZ
	planDownZ=DB_INT_NULL;

	//33 faultCode0
	faultCode0=DB_INT_NULL;

	//34 faultCode1
	faultCode1=DB_INT_NULL;

	//35 faultCode2
	faultCode2=DB_INT_NULL;

	//36 faultCode3
	faultCode3=DB_INT_NULL;

	//37 faultCode4
	faultCode4=DB_INT_NULL;

	//38 faultCode5
	faultCode5=DB_INT_NULL;

	//39 faultCode6
	faultCode6=DB_INT_NULL;

	//40 faultCode7
	faultCode7=DB_INT_NULL;

	//41 faultCode8
	faultCode8=DB_INT_NULL;

	//42 faultCode9
	faultCode9=DB_INT_NULL;

	//43 heart
	heart=DB_INT_NULL;

}

//1 craneNO
string CranePLCStatusBase :: getCraneNO()
{
	return craneNO;
}
void CranePLCStatusBase :: setCraneNO(string theVal)
{
	craneNO=theVal;
}

//2 controlMode
long CranePLCStatusBase :: getControlMode()
{
	return controlMode;
}
void CranePLCStatusBase :: setControlMode(long theVal)
{
	controlMode=theVal;
}
//3 ready
long CranePLCStatusBase :: getReady()
{
	return ready;
}
void CranePLCStatusBase :: setReady(long theVal)
{
	ready=theVal;
}

//4 emgStop
long CranePLCStatusBase :: getEmgStop()
{
	return emgStop;
}
void CranePLCStatusBase :: setEmgStop(long theVal)
{
	emgStop=theVal;
}


//5 askPlan
long CranePLCStatusBase :: getAskPlan()
{
	return askPlan;
}
void CranePLCStatusBase :: setAskPlan(long theVal)
{
	askPlan=theVal;
}

//6 taskExcuting
long CranePLCStatusBase :: getTaskExcuting()
{
	return taskExcuting;
}
void CranePLCStatusBase :: setTaskExcuting(long theVal)
{
	taskExcuting=theVal;
}

//7 xDirectPositive
long CranePLCStatusBase :: getXDirectPositive()
{
	return xDirectPositive;
}
void CranePLCStatusBase :: setXDirectPositive(long theVal)
{
	xDirectPositive=theVal;
}


//8 xDirectNegative
long CranePLCStatusBase :: getXDirectNegative()
{
	return xDirectNegative;
}
void CranePLCStatusBase :: setXDirectNegative(long theVal)
{
	xDirectNegative=theVal;
}


//9 yDirectPositive
long CranePLCStatusBase :: getYDirectPositive()
{
	return yDirectPositive;
}
void CranePLCStatusBase :: setYDirectPositive(long theVal)
{
	yDirectPositive=theVal;
}

//10 yDirectNegative
long CranePLCStatusBase :: getYDirectNegative()
{
	return yDirectNegative;
}
void CranePLCStatusBase :: setYDirectNegative(long theVal)
{
	yDirectNegative=theVal;
}


//11 zDirectPositive
long CranePLCStatusBase :: getZDirectPositive()
{
	return zDirectPositive;
}
void CranePLCStatusBase :: setZDirectPositive(long theVal)
{
	zDirectPositive=theVal;
}

//12 zDirectNegative
long CranePLCStatusBase :: getZDirectNegative()
{
	return zDirectNegative;
}
void CranePLCStatusBase :: setZDirectNegative(long theVal)
{
	zDirectNegative=theVal;
}

//13 hasCoil
long CranePLCStatusBase :: getHasCoil()
{
	return hasCoil;
}
void CranePLCStatusBase :: setHasCoil(long theVal)
{
	hasCoil=theVal;
}

//14 orderID
long CranePLCStatusBase :: getOrderID()
{
	return orderID;
}
void CranePLCStatusBase :: setOrderID(long theVal)
{
	orderID=theVal;
}

//15 runStep
long CranePLCStatusBase :: getRunStep()
{
	return runStep;
}
void CranePLCStatusBase :: setRunStep(long theVal)
{
	runStep=theVal;
}

//16 xSpeed
long CranePLCStatusBase :: getXSpeed()
{
	return xSpeed;
}
void CranePLCStatusBase :: setXSpeed(long theVal)
{
	xSpeed=theVal;
}

//17 ySpeed
long CranePLCStatusBase :: getYSpeed()
{
	return ySpeed;
}
void CranePLCStatusBase :: setYSpeed(long theVal)
{
	ySpeed=theVal;
}


//18 zSpeed
long CranePLCStatusBase :: getZSpeed()
{
	return zSpeed;
}
void CranePLCStatusBase :: setZSpeed(long theVal)
{
	zSpeed=theVal;
}

//19 xAct
long CranePLCStatusBase :: getXAct()
{
	return xAct;
}
void CranePLCStatusBase :: setXAct(long theVal)
{
	xAct=theVal;
}

//20 yAct
long CranePLCStatusBase :: getYAct()
{
	return yAct;
}
void CranePLCStatusBase :: setYAct(long theVal)
{
	yAct=theVal;
}

//21  zAct
long CranePLCStatusBase :: getZAct()
{
	return zAct;
}
void CranePLCStatusBase :: setZAct(long theVal)
{
	zAct=theVal;
}

//22 weightLoaded
long CranePLCStatusBase :: getWeightLoaded()
{
	return weightLoaded;
}
void CranePLCStatusBase :: setWeightLoaded(long theVal)
{
	weightLoaded=theVal;
}

//23 dipAngleAct
long CranePLCStatusBase :: getDipAngleAct()
{
	return dipAngleAct;
}
void CranePLCStatusBase :: setDipAngleAct(long theVal)
{
	dipAngleAct=theVal;
}

//24 currTargX
long CranePLCStatusBase :: getCurrTargX()
{
	return currTargX;
}
void CranePLCStatusBase :: setCurrTargX(long theVal)
{
	currTargX=theVal;
}

//25 currTargY
long CranePLCStatusBase :: getCurrTargY()
{
	return currTargY;
}
void CranePLCStatusBase :: setCurrTargY(long theVal)
{
	currTargY=theVal;
}

//26 currTargZ
long CranePLCStatusBase :: getCurrTargZ()
{
	return currTargZ;
}
void CranePLCStatusBase :: setCurrTargZ(long theVal)
{
	currTargZ=theVal;
}

//27 planUpX
long CranePLCStatusBase :: getPlanUpX()
{
	return planUpX;
}
void CranePLCStatusBase :: setPlanUpX(long theVal)
{
	planUpX=theVal;
}

//28 planUpY
long CranePLCStatusBase :: getPlanUpY()
{
	return planUpY;
}
void CranePLCStatusBase :: setPlanUpY(long theVal)
{
	planUpY=theVal;
}

//29 planUpZ
long CranePLCStatusBase :: getPlanUpZ()
{
	return planUpZ;
}
void CranePLCStatusBase :: setPlanUpZ(long theVal)
{
	planUpZ=theVal;
}

//30 planDownX
long CranePLCStatusBase :: getPlanDownX()
{
	return planDownX;
}
void CranePLCStatusBase :: setPlanDownX(long theVal)
{
	planDownX=theVal;
}

//31 planDownY
long CranePLCStatusBase :: getPlanDownY()
{
	return planDownY;
}
void CranePLCStatusBase :: setPlanDownY(long theVal)
{
	planDownY=theVal;
}

//32 planDownZ
long CranePLCStatusBase :: getPlanDownZ()
{
	return planDownZ;
}
void CranePLCStatusBase :: setPlanDownZ(long theVal)
{
	planDownZ=theVal;
}

//33 faultCode0
long CranePLCStatusBase :: getFaultCode0()
{
	return faultCode0;
}
void CranePLCStatusBase :: setFaultCode0(long theVal)
{
	faultCode0=theVal;
}

//34 faultCode1
long CranePLCStatusBase :: getFaultCode1()
{
	return faultCode1;
}
void CranePLCStatusBase :: setFaultCode1(long theVal)
{
	faultCode1=theVal;
}

//35 faultCode2
long CranePLCStatusBase :: getFaultCode2()
{
	return faultCode2;
}
void CranePLCStatusBase :: setFaultCode2(long theVal)
{
	faultCode2=theVal;
}

//36 faultCode3
long CranePLCStatusBase :: getFaultCode3()
{
	return faultCode3;
}
void CranePLCStatusBase :: setFaultCode3(long theVal)
{
	faultCode3=theVal;
}

//37 faultCode4
long CranePLCStatusBase :: getFaultCode4()
{
	return faultCode4;
}
void CranePLCStatusBase :: setFaultCode4(long theVal)
{
	faultCode4=theVal;
}

//38 faultCode5
long CranePLCStatusBase :: getFaultCode5()
{
	return faultCode5;
}
void CranePLCStatusBase :: setFaultCode5(long theVal)
{
	faultCode5=theVal;
}

//39 faultCode6
long CranePLCStatusBase :: getFaultCode6()
{
	return faultCode6;
}
void CranePLCStatusBase :: setFaultCode6(long theVal)
{
	faultCode6=theVal;
}

//40 faultCode7
long CranePLCStatusBase :: getFaultCode7()
{
	return faultCode7;
}
void CranePLCStatusBase :: setFaultCode7(long theVal)
{
	faultCode7=theVal;
}

//41 faultCode8
long CranePLCStatusBase :: getFaultCode8()
{
	return faultCode8;
}
void CranePLCStatusBase :: setFaultCode8(long theVal)
{
	faultCode8=theVal;
}

//42 faultCode9
long CranePLCStatusBase :: getFaultCode9()
{
	return faultCode9;
}
void CranePLCStatusBase :: setFaultCode9(long theVal)
{
	faultCode9=theVal;
}

//43 heart
long CranePLCStatusBase :: getHeart()
{
	return heart;
}
void CranePLCStatusBase :: setHeart(long theVal)
{
	heart=theVal;
}




void CranePLCStatusBase :: logOutValues()
{
	string functionName="CranePLCStatusBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class CranePLCStatusBase--------------------------------------"<<endl;
	//1
	log.Debug()<<"\t craneNO="<<craneNO;
	//2
	log.Debug()<<"\t controlMode="<<controlMode;
	//3
	log.Debug()<<"\t ready="<<ready;
	//4
	log.Debug()<<"\t emgStop="<<emgStop;
	//5
	log.Debug()<<"\t askPlan="<<askPlan;
	//6
	log.Debug()<<"\t taskExcuting="<<taskExcuting<<endl;
	//7
	log.Debug()<<"\t xDirectPositive="<<xDirectPositive;
	//8
	log.Debug()<<"\t xDirectNegative="<<xDirectNegative;
	//9
	log.Debug()<<"\t yDirectPositive="<<yDirectPositive;
	//10
	log.Debug()<<"\t yDirectNegative="<<yDirectNegative<<endl;
	//11
	log.Debug()<<"\t zDirectPositive="<<zDirectPositive;
	//12
	log.Debug()<<"\t zDirectNegative="<<zDirectNegative;
	//13
	log.Debug()<<"\t hasCoil="<<hasCoil;
	//14
	log.Debug()<<"\t orderID="<<orderID;
	//15
	log.Debug()<<"\t runStep="<<runStep;
	//16
	log.Debug()<<"\t xSpeed="<<xSpeed;
	//17
	log.Debug()<<"\t ySpeed="<<ySpeed<<endl;
	//18
	log.Debug()<<"\t zSpeed="<<zSpeed;
	//19
	log.Debug()<<"\t  xAct="<<xAct;
	//20
	log.Debug()<<"\t yAct="<<yAct;
	//21
	log.Debug()<<"\t zAct="<<zAct;
	//22
	log.Debug()<<"\t weightLoaded="<<weightLoaded;
	//23
	log.Debug()<<"\t dipAngleAct="<<dipAngleAct<<endl;
	//24
	log.Debug()<<"\t currTargX="<<currTargX;
	//24
	log.Debug()<<"\t currTargY="<<currTargY<<endl;
	//25
	log.Debug()<<"\t currTargZ="<<currTargZ;
	//26
	log.Debug()<<"\t planDownX="<<planDownX;
	//27
	log.Debug()<<"\t planUpX="<<planUpX;
	//28
	log.Debug()<<"\t planUpY="<<planUpY<<endl;
	//29
	log.Debug()<<"\t planUpZ="<<planUpZ;
	//30
	log.Debug()<<"\t planDownX="<<planDownX;
	//31
	log.Debug()<<"\t planDownY="<<planDownY;
	//32
	log.Debug()<<"\t planDownZ="<<planDownZ;
	//33
	log.Debug()<<"\t faultCode0="<<faultCode0<<endl;
	//34
	log.Debug()<<"\t faultCode1="<<faultCode1;
	//35
	log.Debug()<<"\t faultCode2="<<faultCode2;
	//36
	log.Debug()<<"\t faultCode3="<<faultCode3;
	//37
	log.Debug()<<"\t faultCode4="<<faultCode4;
	//38
	log.Debug()<<"\t faultCode5="<<faultCode5;
	//39
	log.Debug()<<"\t faultCode6="<<faultCode6;
	//40
	log.Debug()<<"\t faultCode7="<<faultCode7;
	//41
	log.Debug()<<"\t faultCode8="<<faultCode8;
	//42
	log.Debug()<<"\t faultCode9="<<faultCode9;
	//43
	log.Debug()<<"\t heart="<<heart<<endl;

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

	
}

void CranePLCStatusBase :: wirteValues2TagSystem(TAGVALUEMAP& Tags)
{
	string functionName="CranePLCStatusBase :: wirteValues2TagSystem()";

	string adressHead=craneNO+"_";

	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

				TAGVALUEMAP Tags;
				string TagName="";
				string TagValue="";
				

				//2控制模式
				TagName=adressHead+CranePLCStatusBase::ADRESS_CONTROL_MODE;
				TagValue=StringHelper::ToString(controlMode);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 1...";

				//3准备好
				TagName=adressHead+CranePLCStatusBase::ADRESS_READY;
				TagValue=StringHelper::ToString(ready);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 2...";

				//4急停状态
				TagName=adressHead+CranePLCStatusBase::ADRESS_EMG_STOP;
				TagValue=StringHelper::ToString(emgStop);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 3...";

				//5请求计划
				TagName=adressHead+CranePLCStatusBase::ADRESS_ASK_PLAN;
				TagValue=StringHelper::ToString(askPlan);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 4...";

				//6任务执行中
				TagName=adressHead+CranePLCStatusBase::ADRESS_TASK_EXCUTING;
				TagValue=StringHelper::ToString(taskExcuting);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 5...";

				//7大车正方向
				TagName=adressHead+CranePLCStatusBase::ADRESS_XDIR_P;
				TagValue=StringHelper::ToString(xDirectPositive);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 6...";

				//8大车负方向
				TagName=adressHead+CranePLCStatusBase::ADRESS_XDIR_N;
				TagValue=StringHelper::ToString(xDirectNegative);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 7...";

				//9小车正方向
				TagName=adressHead+CranePLCStatusBase::ADRESS_YDIR_P;
				TagValue=StringHelper::ToString(yDirectPositive);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 8...";

				//10小车负方向
				TagName=adressHead+CranePLCStatusBase::ADRESS_YDIR_N;
				TagValue=StringHelper::ToString(yDirectNegative);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 9...";

				//11升降正方向
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZDIR_P;
				TagValue=StringHelper::ToString(zDirectPositive);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 10...";

				//12升降负方向
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZDIR_N;
				TagValue=StringHelper::ToString(zDirectNegative);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 11...";

				//13有卷标志
				TagName=adressHead+CranePLCStatusBase::ADRESS_HAS_COIL;
				TagValue=StringHelper::ToString(hasCoil);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 12...";

				//16大车方向实际速度
				TagName=adressHead+CranePLCStatusBase::ADRESS_XSPEED;
				TagValue=StringHelper::ToString(xSpeed);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 15...";

				//17小车方向实际速度
				TagName=adressHead+CranePLCStatusBase::ADRESS_YSPEED;
				TagValue=StringHelper::ToString(ySpeed);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 16...";

				//18升降实际速度
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZSPEED;
				TagValue=StringHelper::ToString(zSpeed);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 17...";

				//19大车位置
				TagName=adressHead+CranePLCStatusBase::ADRESS_XACT;
				TagValue=StringHelper::ToString(xAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 18...";

				//20小车位置
				TagName=adressHead+CranePLCStatusBase::ADRESS_YACT;
				TagValue=StringHelper::ToString(yAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 19...";

				//21夹钳高度
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZACT;
				TagValue=StringHelper::ToString(zAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 20...";


				//22称重信号
				TagName=adressHead+CranePLCStatusBase::ADRESS_WEIGHT_LOADED;
				TagValue=StringHelper::ToString(weightLoaded);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 21...";

				//23倾斜角度
				TagName=adressHead+CranePLCStatusBase::ADRESS_DIP_ANGLE_ACT;
				TagValue=StringHelper::ToString(dipAngleAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 22...";


				//对于 orderID   planUpX  planUpY  planUpZ  和  planDownX  planDownY  planDownZ
				//如果OrderID=0，则意味着是心跳电文，这7个数据不写入tag系统；
				//如果OrderID！=0 ，则意味着是非心跳电文，这7个数据可以写入tag系统
				if (orderID != 0)
				{
					//14当前指令号
					TagName=adressHead+CranePLCStatusBase::ADRESS_ORDER_ID;
					TagValue=StringHelper::ToString(orderID);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 13@...";

					//15行车运行步骤
					TagName=adressHead+CranePLCStatusBase::ADRESS_RunStep;
					TagValue=StringHelper::ToString(runStep);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 14@...";

					//24X轴当前目标位
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_X;
					TagValue=StringHelper::ToString(planUpX);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 23@...";

					//25Y轴当前目标位
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_Y;
					TagValue=StringHelper::ToString(planUpY);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 24@...";

					//26Z轴当前目标位
					TagName=adressHead+CranePLCStatusBase::ADRESS_ORDER_ID;
					TagValue=StringHelper::ToString(orderID);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 25@...";

					//27计划起卷X
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_X;
					TagValue=StringHelper::ToString(planUpX);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 26@...";

					//28计划起卷Y
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_Y;
					TagValue=StringHelper::ToString(planUpY);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 27@...";

					//29计划起卷Z
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_Z;
					TagValue=StringHelper::ToString(planUpZ);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 28@...";

					//30计划落卷X
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_X;
					TagValue=StringHelper::ToString(planDownX);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 29@...";

					//31计划落卷Y
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_Y;
					TagValue=StringHelper::ToString(planDownY);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 30@...";

					//32计划落卷Z
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_Z;
					TagValue=StringHelper::ToString(planDownZ);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 31@...";
				}				

				//33 故障代码0
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_0;
				TagValue=StringHelper::ToString(faultCode0);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 32...";

				//34 故障代码1
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_1;
				TagValue=StringHelper::ToString(faultCode1);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 33...";

				//35 故障代码2
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_2;
				TagValue=StringHelper::ToString(faultCode2);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 34...";

				//36 故障代码3
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_3;
				TagValue=StringHelper::ToString(faultCode3);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 35...";

				//37 故障代码4
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_4;
				TagValue=StringHelper::ToString(faultCode4);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 36...";

				//38 故障代码5
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_5;
				TagValue=StringHelper::ToString(faultCode5);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 37...";

				//39 故障代码6
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_6;
				TagValue=StringHelper::ToString(faultCode6);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 38...";

				//40 故障代码7
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_7;
				TagValue=StringHelper::ToString(faultCode7);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 39...";

				//41 故障代码8
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_8;
				TagValue=StringHelper::ToString(faultCode8);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 40...";

				//41 故障代码9
				TagName=adressHead+CranePLCStatusBase::ADRESS_FaultCode_9;
				TagValue=StringHelper::ToString(faultCode9);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 41...";

				//43heart
				TagName=adressHead+CranePLCStatusBase::ADRESS_Heart;
				TagValue=StringHelper::ToString(heart);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 42...";

				//tag点写入系统
				TAGVALUEMAP TagTimeStamp;
				Tag::GetInst().MDPut(TagTimeStamp,Tags);	

				log.Debug()<<"Crane tags written to tag system .........OK"<<endl;


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


void CranePLCStatusBase :: setPlanUpDownXYZIs9()
{
	string functionName="CranePLCStatusBase :: setPlanUpDownXYZIs9()";

	string adressHead=craneNO+"_";

	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"24......非自动切自动，封9";
		planUpX  = DB_INT_NULL;
		log.Debug()<<"25......非自动切自动，封9";
		planUpY = DB_INT_NULL;
		log.Debug()<<"26......非自动切自动，封9";
		planUpZ  = DB_INT_NULL;

		log.Debug()<<"27......非自动切自动，封9";
		planDownX  = DB_INT_NULL;
		log.Debug()<<"28......非自动切自动，封9";
		planDownY  = DB_INT_NULL;
		log.Debug()<<"29......非自动切自动，封9";
		planDownZ  = DB_INT_NULL;


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





//CLTS::CranePLCStatusDesc CranePLCStatusBase :: TransFromClass(CranePLCStatusBase cranePLCStatusBase)
//{
//	string functionName="CranePLCStatusBase :: TransFromStruct()";
//
//	CLTS::CranePLCStatusDesc desc;
//
//	LOG log(functionName, AUTO_CATCH_PID);
//
//	try
//	{
//	
//		//1		CRANE_NO
//		desc.craneNO=cranePLCStatusBase.getCraneNO();
//		//2		READY
//		desc.ready=cranePLCStatusBase.getReady();
//		//3		CONTROL_MODE
//		desc.controlMode=cranePLCStatusBase.getControlMode();
//		//4		ASK_PLAN
//		desc.askPlan=cranePLCStatusBase.getAskPlan();
//		//5		TASK_EXCUTING
//		desc.taskExcuting=cranePLCStatusBase.getTaskExcuting();
//		//6		XACT
//		desc.xAct=cranePLCStatusBase.getXAct();
//		//7		YACT
//		desc.yAct=cranePLCStatusBase.getYAct();
//		//8		ZACT
//		desc.zAct=cranePLCStatusBase.getZAct();
//		//9		XSPEED
//		desc.xSpeed=cranePLCStatusBase.getXSpeed();
//		//10	YSPEED
//		desc.ySpeed=cranePLCStatusBase.getYSpeed();
//		//11	ZSPEED
//		desc.zSpeed=cranePLCStatusBase.getZSpeed();
//		//12	XDIR_P
//		desc.xDirectPositive=cranePLCStatusBase.getXDirectPositive();
//		//13	XDIR_N
//		desc.xDirectNegative=cranePLCStatusBase.getXDirectNegative();
//		//14	YDIR_P
//		desc.yDirectPositive=cranePLCStatusBase.getYDirectPositive();
//		//15	YDIR_N
//		desc.yDirectNegative=cranePLCStatusBase.getYDirectNegative();
//		//16	zDirectPositive
//		desc.zDirectPositive=cranePLCStatusBase.getZDirectPositive();
//		//17	zDirectNegative
//		desc.zDirectNegative=cranePLCStatusBase.getZDirectNegative();
//		//18	hasCoil
//		desc.hasCoil=cranePLCStatusBase.getHasCoil();
//		//19	weightLoaded
//		desc.weightLoaded=cranePLCStatusBase.getWeightLoaded();
//		//20	rotateAngleAct
//		desc.rotateAngleAct=cranePLCStatusBase.getRotateAngleAct();
//		//21	emgStop
//		desc.emgStop=cranePLCStatusBase.getEmgStop();
//		//22	orderID
//		desc.orderID=cranePLCStatusBase.getOrderID();
//		//23	planUpX
//		desc.planUpX=cranePLCStatusBase.getPlanUpX();
//		//24	planUpY
//		desc.planUpY=cranePLCStatusBase.getPlanUpY();
//		//25	planUpZ
//		desc.planUpZ=cranePLCStatusBase.getPlanUpZ();
//		//26	planDownX
//		desc.planDownX=cranePLCStatusBase.getPlanDownX();
//		//27	planDownY
//		desc.planDownY=cranePLCStatusBase.getPlanDownY();
//		//28	planDownZ
//		desc.planDownZ=cranePLCStatusBase.getPlanDownZ();
//		//29	craneStatus
//		desc.craneStatus=cranePLCStatusBase.getCraneStatus();	
//		//30 craneAlarm
//		desc.craneAlarm=cranePLCStatusBase.getCraneAlarm();
//		//31 timeReceive
//		desc.timeReceive=cranePLCStatusBase.getTimeReceive();
//
//	}
//	catch(iDA::Exception &x)
//	{
//		try
//		{
//			CDataAccess::GetInstance()->m_DBCon.Rollback();
//		}
//		catch(iDA::Exception &)
//		{
//		}
//
//		string msg = functionName +"   error:"+ x.ErrMsg();
//		log.Debug()<<msg<<endl;
//	}
//	catch (std::exception& stdex)
//	{
//		string errorMessage=stdex.what();
//		string msg=functionName +"   error:"+ errorMessage;
//		log.Debug()<<msg<<endl;
//	}
//	catch (...)
//	{
//		string msg = functionName +"   error:";
//		log.Debug()<<msg<<endl;
//	}
//
//	return desc;
//}



CranePLCStatusBase CranePLCStatusBase :: TransFromStruct(CLTS::CranePLCStatusDesc desc)
{
	string functionName="CranePLCStatusBase :: TransFromStruct()";
	CranePLCStatusBase cranePLCStatusBase;
	LOG log(functionName, AUTO_CATCH_PID);
	
	try
	{
	
		//1		CRANE_NO
		cranePLCStatusBase.setCraneNO( desc.craneNO );
		//2		CONTROL_MODE
		cranePLCStatusBase.setControlMode( desc.controlMode );
		//3		READY
		cranePLCStatusBase.setReady( desc.ready );
		//4	emgStop
		cranePLCStatusBase.setEmgStop( desc.emgStop );
		//5		ASK_PLAN
		cranePLCStatusBase.setAskPlan( desc.askPlan );
		//6		TASK_EXCUTING
		cranePLCStatusBase.setTaskExcuting( desc.taskExcuting );
		//7	XDIR_P
		cranePLCStatusBase.setXDirectPositive( desc.xDirectPositive );
		//8	XDIR_N
		cranePLCStatusBase.setXDirectNegative( desc.xDirectNegative );
		//9	YDIR_P
		cranePLCStatusBase.setYDirectPositive( desc.yDirectPositive );
		//10 YDIR_N
		cranePLCStatusBase.setYDirectNegative( desc.yDirectNegative );
		//11 zDirectPositive
		cranePLCStatusBase.setZDirectPositive( desc.zDirectPositive );
		//12 zDirectNegative
		cranePLCStatusBase.setZDirectNegative( desc.zDirectNegative );
		//13 hasCoil
		cranePLCStatusBase.setHasCoil( desc.hasCoil );
		//14	orderID
		cranePLCStatusBase.setOrderID( desc.orderID );
		//15	runStep
		cranePLCStatusBase.setRunStep( desc.runStep );
		//16		XSPEED
		cranePLCStatusBase.setXSpeed( desc.xSpeed );
		//17	YSPEED
		cranePLCStatusBase.setYSpeed( desc.ySpeed );
		//18	ZSPEED
		cranePLCStatusBase.setZSpeed( desc.zSpeed );
		//19		XACT
		cranePLCStatusBase.setXAct( desc.xAct );
		//20		YACT
		cranePLCStatusBase.setYAct( desc.yAct );
		//21		ZACT
		cranePLCStatusBase.setZAct( desc.zAct );
		//22	weightLoaded
		cranePLCStatusBase.setWeightLoaded( desc.weightLoaded );
		//23	dipAngleAct
		cranePLCStatusBase.setDipAngleAct( desc.dipAngleAct );
		//24	CurrTargX
		cranePLCStatusBase.setCurrTargX( desc.currTargX );
		//25	CurrTargY
		cranePLCStatusBase.setCurrTargY( desc.currTargY );
		//26	CurrTargZ
		cranePLCStatusBase.setCurrTargZ( desc.currTargZ );
		//27	planUpX
		cranePLCStatusBase.setPlanUpX( desc.planUpX );
		//28	planUpY
		cranePLCStatusBase.setPlanUpY( desc.planUpY );
		//29	planUpZ
		cranePLCStatusBase.setPlanUpZ( desc.planUpZ );
		//30	planDownX
		cranePLCStatusBase.setPlanDownX( desc.planDownX );
		//31	planDownY
		cranePLCStatusBase.setPlanDownY( desc.planDownY );
		//32	planDownZ
		cranePLCStatusBase.setPlanDownZ( desc.planDownZ );
		//33	FaultCode0
		cranePLCStatusBase.setFaultCode0( desc.faultCode0 );
		//34	FaultCode1
		cranePLCStatusBase.setFaultCode1( desc.faultCode1 );
		//35	FaultCode2
		cranePLCStatusBase.setFaultCode2( desc.faultCode2 );
		//36	FaultCode3
		cranePLCStatusBase.setFaultCode3( desc.faultCode3 );
		//37	FaultCode4
		cranePLCStatusBase.setFaultCode4( desc.faultCode4 );
		//38	FaultCode5
		cranePLCStatusBase.setFaultCode5( desc.faultCode5 );
		//39	FaultCode6
		cranePLCStatusBase.setFaultCode6( desc.faultCode6 );
		//40	FaultCode7
		cranePLCStatusBase.setFaultCode7( desc.faultCode7 );
		//41	FaultCode8
		cranePLCStatusBase.setFaultCode8( desc.faultCode8 );
		//42	FaultCode9
		cranePLCStatusBase.setFaultCode9( desc.faultCode9 );
		//43	heart
		cranePLCStatusBase.setHeart( desc.heart );		
		//31 timeReceive
		//cranePLCStatusBase.setTimeReceive(desc.timeReceive);

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

	return cranePLCStatusBase;
}


