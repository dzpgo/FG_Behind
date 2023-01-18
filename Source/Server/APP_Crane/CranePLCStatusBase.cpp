#include "CranePLCStatusBase.h"

using namespace Monitor;
using namespace CLTS;

//--------------------------------------------------�г��豸״̬����----------------------------------------------------------------
//�չ���������= 000;
const long CranePLCStatusBase::STATUS_NEED_TO_READY=0;
//�չ��ȴ�״̬= 010
const long CranePLCStatusBase::STATUS_WAITING_ORDER_WITH_OUT_COIL=10;
//�չ�����״̬= 020
const long CranePLCStatusBase::STATUS_MOVING_WITH_OUT_COIL=20;
//�չ����е�λ״̬= 030
const long CranePLCStatusBase::STATUS_ARRIVED_POS_WITH_OUT_COIL=30;
//�չ��½�ȥȡ��= 040
const long CranePLCStatusBase::STATUS_LIFT_COIL_DOWN_PHASE=40;
//�־����= 050
const long CranePLCStatusBase::STATUS_COIL_LIFTED=50;
//�ع���������= 060
const long CranePLCStatusBase::STATUS_LIFT_COIL_UP_PHASE=60;
//�ع��ȴ�״̬= 070
const long CranePLCStatusBase::STATUS_WAITING_ORDER_WITH_COIL=70;
//�ع�����״̬= 080
const long CranePLCStatusBase::STATUS_MOVING_WITH_COIL=80;
//�ع����е�λ= 090
const long CranePLCStatusBase::STATUS_ARRIVED_POS_WITH_COIL=90;
//�ع��½�ȥ���= 100
const long CranePLCStatusBase::STATUS_DOWN_COIL_DOWN_PHASE=100;
//�־����= 110
const long CranePLCStatusBase::STATUS_COIL_DOWN=110;


 //--------------------------------------------------�г�����ģʽ����----------------------------------------------------------------
 //ң��ģʽ
 const long CranePLCStatusBase::CONTROL_MODE_REMOTE_CONTROL=1;
 //˾��ģʽ
 const long CranePLCStatusBase::CONTROL_MODE_DRIVER_CONTROL=2;
 //���Զ�ģʽ
 const long CranePLCStatusBase::CONTROL_MODE_HALF_AUTO=3;
 //ȫ�Զ�ģʽ
 const long CranePLCStatusBase::CONTROL_MODE_AUTO=4;


//---------------------------------------------------------------------------------------------------------------------------------------------------
 //2׼����
 const  string CranePLCStatusBase::ADRESS_READY="ready";
 //3����ģʽ
 const  string  CranePLCStatusBase::ADRESS_CONTROL_MODE="autoMode";
 //4����ƻ�
 const  string CranePLCStatusBase::ADRESS_ASK_PLAN="askPlan";
 //5����ִ����
 const  string CranePLCStatusBase::ADRESS_TASK_EXCUTING="taskExcuting";
 //6��λ��
 const  string CranePLCStatusBase::ADRESS_XACT="xAct";
 //7С��λ��
 const  string CranePLCStatusBase::ADRESS_YACT="yAct";
 //8��ǯ�߶�
 const  string CranePLCStatusBase::ADRESS_ZACT="zAct";
 //9�󳵷���ʵ���ٶ�<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_XSPEED="xSpeed";
 //10С������ʵ���ٶ�<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_YSPEED="ySpeed";
 //11����ʵ���ٶ�<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_ZSPEED="zSpeed";
 //12��������<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_XDIR_P="xDir_P";
 //13�󳵸�����<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_XDIR_N="xDir_N";
 //14С��������<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_YDIR_P="yDir_P";
 //15С��������<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_YDIR_N="yDir_N";
 //16����������<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_ZDIR_P="zDir_P";
 //17����������<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_ZDIR_N="zDir_N";
 //18�о��־
 const  string CranePLCStatusBase::ADRESS_HAS_COIL="hasCoil";
 //19�����ź�<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_WEIGHT_LOADED="weightLoaded";
 //20��ǯ��ת�Ƕ�<--------------------------------------------new tag
 const  string CranePLCStatusBase::ADRESS_ROTATE_ANGLE_ACT="rotateAngleAct";
 //21��ͣ״̬
 const  string CranePLCStatusBase::ADRESS_EMG_STOP="emergencyStop";
 //22��ǰָ���
 const  string CranePLCStatusBase::ADRESS_ORDER_ID="craneOrderNo";
 //23�ƻ����X
 const  string CranePLCStatusBase::ADRESS_PLAN_UP_X="planUpX";
 //24�ƻ����Y
 const  string CranePLCStatusBase::ADRESS_PLAN_UP_Y="planUpY";
 //25�ƻ����Z
 const  string CranePLCStatusBase::ADRESS_PLAN_UP_Z="planUpZ";
 //26�ƻ����X
 const  string CranePLCStatusBase::ADRESS_PLAN_DOWN_X="planDownX";
 //27�ƻ����Y
 const  string CranePLCStatusBase::ADRESS_PLAN_DOWN_Y="planDownY";
 //28�ƻ����Z
 const  string CranePLCStatusBase::ADRESS_PLAN_DOWN_Z="planDownZ";
 //29�г�״̬
 const  string CranePLCStatusBase::ADRESS_CRANE_STATUS="status";
 //30 �г�����
 const string CranePLCStatusBase::ADRESS_CRANE_ALARM="craneAlarm";

 //31
 const string CranePLCStatusBase::ADRESS_CRANE_PLC_HEART_BEAT="heartBeat";

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

	//2 ready
	ready=DB_INT_NULL;

	//3 controlMode
	controlMode=DB_INT_NULL;

	//4 askPlan
	askPlan=DB_INT_NULL;

	//5 taskExcuting
	taskExcuting=DB_INT_NULL;

	//6 xAct
	xAct=DB_INT_NULL;

	//7 yAct
	yAct=DB_INT_NULL;

	//8 zAct
	zAct=DB_INT_NULL;

	//9 xSpeed
	xSpeed=DB_INT_NULL;

	//10 ySpeed
	ySpeed=DB_INT_NULL;

	//11 zSpeed
	zSpeed=DB_INT_NULL;

	//12 xDirectPositive
	xDirectPositive=DB_INT_NULL;

	//13 xDirectNegative
	xDirectNegative=DB_INT_NULL;

	//14 yDirectPositive
	yDirectPositive=DB_INT_NULL;

	//15 yDirectNegative
	yDirectNegative=DB_INT_NULL;

	//16 zDirectPositive
	zDirectPositive=DB_INT_NULL;

	//17 zDirectNegative
	zDirectNegative=DB_INT_NULL;

	//18 hasCoil
	hasCoil=DB_INT_NULL;

	//19 weightLoaded
	weightLoaded=DB_INT_NULL;

	//20 rotateAngleAct
	rotateAngleAct=DB_INT_NULL;

	//21 emgStop
	emgStop=DB_INT_NULL;

	//22 orderID
	orderID=DB_INT_NULL;

	//23 planUpX
	planUpX=DB_INT_NULL;

	//24 planUpY
	planUpY=DB_INT_NULL;

	//25 planUpZ
	planUpZ=DB_INT_NULL;

	//26 planDownX
	planDownX=DB_INT_NULL;

	//27 planDownY
	planDownY=DB_INT_NULL;

	//28 planDownZ
	planDownZ=DB_INT_NULL;

	//29 craneStatus
	craneStatus=DB_INT_NULL;

	//30 craneAlarm
	craneAlarm=DB_INT_NULL;

	//31timeReceive
	timeReceive=DB_STR_NULL;
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

//2 ready
long CranePLCStatusBase :: getReady()
{
	return ready;
}
void CranePLCStatusBase :: setReady(long theVal)
{
	ready=theVal;
}

//3 controlMode
long CranePLCStatusBase :: getControlMode()
{
	return controlMode;
}
void CranePLCStatusBase :: setControlMode(long theVal)
{
	controlMode=theVal;
}

//4 askPlan
long CranePLCStatusBase :: getAskPlan()
{
	return askPlan;
}
void CranePLCStatusBase :: setAskPlan(long theVal)
{
	askPlan=theVal;
}

//5 taskExcuting
long CranePLCStatusBase :: getTaskExcuting()
{
	return taskExcuting;
}
void CranePLCStatusBase :: setTaskExcuting(long theVal)
{
	taskExcuting=theVal;
}


//6 xAct
long CranePLCStatusBase :: getXAct()
{
	return xAct;
}
void CranePLCStatusBase :: setXAct(long theVal)
{
	xAct=theVal;
}


//7 yAct
long CranePLCStatusBase :: getYAct()
{
	return yAct;
}
void CranePLCStatusBase :: setYAct(long theVal)
{
	yAct=theVal;
}


//8  zAct
long CranePLCStatusBase :: getZAct()
{
	return zAct;
}
void CranePLCStatusBase :: setZAct(long theVal)
{
	zAct=theVal;
}

//9 xSpeed
long CranePLCStatusBase :: getXSpeed()
{
	return xSpeed;
}
void CranePLCStatusBase :: setXSpeed(long theVal)
{
	xSpeed=theVal;
}

//10 ySpeed
long CranePLCStatusBase :: getYSpeed()
{
	return ySpeed;
}
void CranePLCStatusBase :: setYSpeed(long theVal)
{
	ySpeed=theVal;
}


//11 zSpeed
long CranePLCStatusBase :: getZSpeed()
{
	return zSpeed;
}
void CranePLCStatusBase :: setZSpeed(long theVal)
{
	zSpeed=theVal;
}


//12 xDirectPositive
long CranePLCStatusBase :: getXDirectPositive()
{
	return xDirectPositive;
}
void CranePLCStatusBase :: setXDirectPositive(long theVal)
{
	xDirectPositive=theVal;
}


//13 xDirectNegative
long CranePLCStatusBase :: getXDirectNegative()
{
	return xDirectNegative;
}
void CranePLCStatusBase :: setXDirectNegative(long theVal)
{
	xDirectNegative=theVal;
}


//14 yDirectPositive
long CranePLCStatusBase :: getYDirectPositive()
{
	return yDirectPositive;
}
void CranePLCStatusBase :: setYDirectPositive(long theVal)
{
	yDirectPositive=theVal;
}

//15 yDirectNegative
long CranePLCStatusBase :: getYDirectNegative()
{
	return yDirectNegative;
}
void CranePLCStatusBase :: setYDirectNegative(long theVal)
{
	yDirectNegative=theVal;
}


//16 zDirectPositive
long CranePLCStatusBase :: getZDirectPositive()
{
	return zDirectPositive;
}
void CranePLCStatusBase :: setZDirectPositive(long theVal)
{
	zDirectPositive=theVal;
}

//17 zDirectNegative
long CranePLCStatusBase :: getZDirectNegative()
{
	return zDirectNegative;
}
void CranePLCStatusBase :: setZDirectNegative(long theVal)
{
	zDirectNegative=theVal;
}

//18 hasCoil
long CranePLCStatusBase :: getHasCoil()
{
	return hasCoil;
}
void CranePLCStatusBase :: setHasCoil(long theVal)
{
	hasCoil=theVal;
}

//19 weightLoaded
long CranePLCStatusBase :: getWeightLoaded()
{
	return weightLoaded;
}
void CranePLCStatusBase :: setWeightLoaded(long theVal)
{
	weightLoaded=theVal;
}

//20 rotateAngleAct
long CranePLCStatusBase :: getRotateAngleAct()
{
	return rotateAngleAct;
}
void CranePLCStatusBase :: setRotateAngleAct(long theVal)
{
	rotateAngleAct=theVal;
}

//21 emgStop
long CranePLCStatusBase :: getEmgStop()
{
	return emgStop;
}
void CranePLCStatusBase :: setEmgStop(long theVal)
{
	emgStop=theVal;
}

//22 orderID
long CranePLCStatusBase :: getOrderID()
{
	return orderID;
}
void CranePLCStatusBase :: setOrderID(long theVal)
{
	orderID=theVal;
}

//23 planUpX
long CranePLCStatusBase :: getPlanUpX()
{
	return planUpX;
}
void CranePLCStatusBase :: setPlanUpX(long theVal)
{
	planUpX=theVal;
}

//24 planUpY
long CranePLCStatusBase :: getPlanUpY()
{
	return planUpY;
}
void CranePLCStatusBase :: setPlanUpY(long theVal)
{
	planUpY=theVal;
}

//25 planUpZ
long CranePLCStatusBase :: getPlanUpZ()
{
	return planUpZ;
}
void CranePLCStatusBase :: setPlanUpZ(long theVal)
{
	planUpZ=theVal;
}

//26 planDownX
long CranePLCStatusBase :: getPlanDownX()
{
	return planDownX;
}
void CranePLCStatusBase :: setPlanDownX(long theVal)
{
	planDownX=theVal;
}

//27 planDownY
long CranePLCStatusBase :: getPlanDownY()
{
	return planDownY;
}
void CranePLCStatusBase :: setPlanDownY(long theVal)
{
	planDownY=theVal;
}

//28 planDownZ
long CranePLCStatusBase :: getPlanDownZ()
{
	return planDownZ;
}
void CranePLCStatusBase :: setPlanDownZ(long theVal)
{
	planDownZ=theVal;
}

//29 craneStatus
long CranePLCStatusBase :: getCraneStatus()
{
	return craneStatus;
}
void CranePLCStatusBase :: setCraneStatus(long theVal)
{
	craneStatus=theVal;
}

//30 CRANE_ALARM
long CranePLCStatusBase :: getCraneAlarm()
{
	return craneAlarm;
}
void CranePLCStatusBase :: setCraneAlarm(long theVal)
{
	craneAlarm=theVal;
}

//31 timeReceive
string CranePLCStatusBase::getTimeReceive()
{
	return timeReceive;
}
void CranePLCStatusBase::setTimeReceive(string theVal)
{
	timeReceive=theVal;
}


void CranePLCStatusBase :: logOutValues()
{
	string functionName="CranePLCStatusBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class CranePLCStatusBase--------------------------------------"<<endl;
	//1
	log.Debug()<<"\t craneNO="<<craneNO;
	//2
	log.Debug()<<"\t ready="<<ready;
	//3
	log.Debug()<<"\t controlMode="<<controlMode;
	//4
	log.Debug()<<"\t askPlan="<<askPlan;
	//5
	log.Debug()<<"\t taskExcuting="<<taskExcuting<<endl;
	//6
	log.Debug()<<"\t  xAct="<<xAct;
	//7
	log.Debug()<<"\t yAct="<<yAct;
	//8
	log.Debug()<<"\t zAct="<<zAct;
	//9
	log.Debug()<<"\t xSpeed="<<xSpeed;
	//10
	log.Debug()<<"\t ySpeed="<<ySpeed<<endl;
	//11
	log.Debug()<<"\t zSpeed="<<zSpeed;
	//12
	log.Debug()<<"\t xDirectPositive="<<xDirectPositive;
	//13
	log.Debug()<<"\t xDirectNegative="<<xDirectNegative;
	//14
	log.Debug()<<"\t yDirectPositive="<<yDirectPositive;
	//15
	log.Debug()<<"\t yDirectNegative="<<yDirectNegative<<endl;
	//16
	log.Debug()<<"\t zDirectPositive="<<zDirectPositive;
	//17
	log.Debug()<<"\t zDirectNegative="<<zDirectNegative;
	//18
	log.Debug()<<"\t hasCoil="<<hasCoil;
	//19
	log.Debug()<<"\t weightLoaded="<<weightLoaded;
	//20
	log.Debug()<<"\t rotateAngleAct="<<rotateAngleAct<<endl;
	//21
	log.Debug()<<"\t emgStop="<<emgStop;
	//22
	log.Debug()<<"\t orderID="<<orderID;
	//23
	log.Debug()<<"\t planUpX="<<planUpX;
	//24
	log.Debug()<<"\t planUpY="<<planUpY<<endl;
	//25
	log.Debug()<<"\t planUpZ="<<planUpZ;
	//26
	log.Debug()<<"\t planDownX="<<planDownX;
	//27
	log.Debug()<<"\t planDownY="<<planDownY;
	//28
	log.Debug()<<"\t planDownZ="<<planDownZ;
	//29
	log.Debug()<<"\t craneStatus="<<craneStatus<<endl;
	//30
	log.Debug()<<"\t craneAlarm="<<craneAlarm;
	//31
	log.Debug()<<"\t timeReceive="<<timeReceive<<endl;

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

	
}

void CranePLCStatusBase :: wirteValues2TagSystem()
{
	string functionName="CranePLCStatusBase :: wirteValues2TagSystem()";

	string adressHead=craneNO+"_";

	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

				TAGVALUEMAP Tags;
				string TagName="";
				string TagValue="";
				

				//2׼����
				TagName=adressHead+CranePLCStatusBase::ADRESS_READY;
				TagValue=StringHelper::ToString(ready);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 1...";

				//3����ģʽ
				TagName=adressHead+CranePLCStatusBase::ADRESS_CONTROL_MODE;
				TagValue=StringHelper::ToString(controlMode);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 2...";

				//4����ƻ�
				TagName=adressHead+CranePLCStatusBase::ADRESS_ASK_PLAN;
				TagValue=StringHelper::ToString(askPlan);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 3...";

				//5����ִ����
				TagName=adressHead+CranePLCStatusBase::ADRESS_TASK_EXCUTING;
				TagValue=StringHelper::ToString(taskExcuting);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 4...";

				//6��λ��
				TagName=adressHead+CranePLCStatusBase::ADRESS_XACT;
				TagValue=StringHelper::ToString(xAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 5...";

				//7С��λ��
				TagName=adressHead+CranePLCStatusBase::ADRESS_YACT;
				TagValue=StringHelper::ToString(yAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 6...";

				//8��ǯ�߶�
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZACT;
				TagValue=StringHelper::ToString(zAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 7...";

				//9�󳵷���ʵ���ٶ�
				TagName=adressHead+CranePLCStatusBase::ADRESS_XSPEED;
				TagValue=StringHelper::ToString(xSpeed);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 8...";

				//10С������ʵ���ٶ�
				TagName=adressHead+CranePLCStatusBase::ADRESS_YSPEED;
				TagValue=StringHelper::ToString(ySpeed);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 9...";

				//11����ʵ���ٶ�
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZSPEED;
				TagValue=StringHelper::ToString(zSpeed);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 10...";

				//12��������
				TagName=adressHead+CranePLCStatusBase::ADRESS_XDIR_P;
				TagValue=StringHelper::ToString(xDirectPositive);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 11...";

				//13�󳵸�����
				TagName=adressHead+CranePLCStatusBase::ADRESS_XDIR_N;
				TagValue=StringHelper::ToString(xDirectNegative);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 12...";

				//14С��������
				TagName=adressHead+CranePLCStatusBase::ADRESS_YDIR_P;
				TagValue=StringHelper::ToString(yDirectPositive);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 13...";

				//15С��������
				TagName=adressHead+CranePLCStatusBase::ADRESS_YDIR_N;
				TagValue=StringHelper::ToString(yDirectNegative);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 14...";

				//16����������
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZDIR_P;
				TagValue=StringHelper::ToString(zDirectPositive);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 15...";

				//17����������
				TagName=adressHead+CranePLCStatusBase::ADRESS_ZDIR_N;
				TagValue=StringHelper::ToString(zDirectNegative);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 16...";

				//18�о��־
				TagName=adressHead+CranePLCStatusBase::ADRESS_HAS_COIL;
				TagValue=StringHelper::ToString(hasCoil);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 17...";

				//19�����ź�
				TagName=adressHead+CranePLCStatusBase::ADRESS_WEIGHT_LOADED;
				TagValue=StringHelper::ToString(weightLoaded);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 18...";

				//20��ǯ��ת�Ƕ�
				TagName=adressHead+CranePLCStatusBase::ADRESS_ROTATE_ANGLE_ACT;
				TagValue=StringHelper::ToString(rotateAngleAct);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 19...";

				//21��ͣ״̬
				TagName=adressHead+CranePLCStatusBase::ADRESS_EMG_STOP;
				TagValue=StringHelper::ToString(emgStop);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 21...";

				

				//���� orderID   planUpX  planUpY  planUpZ  ��  planDownX  planDownY  planDownZ
				//���OrderID=0������ζ�����������ģ���7�����ݲ�д��tagϵͳ��
				//���OrderID��=0 ������ζ���Ƿ��������ģ���7�����ݿ���д��tagϵͳ
				if (orderID != 0)
				{
					//22��ǰָ���
					TagName=adressHead+CranePLCStatusBase::ADRESS_ORDER_ID;
					TagValue=StringHelper::ToString(orderID);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 22@...";

					//23�ƻ����X
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_X;
					TagValue=StringHelper::ToString(planUpX);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 23@...";

					//24�ƻ����Y
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_Y;
					TagValue=StringHelper::ToString(planUpY);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 24@...";

					//25�ƻ����Z
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_UP_Z;
					TagValue=StringHelper::ToString(planUpZ);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 25@...";

					//26�ƻ����X
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_X;
					TagValue=StringHelper::ToString(planDownX);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 26@...";

					//27�ƻ����Y
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_Y;
					TagValue=StringHelper::ToString(planDownY);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 27@...";

					//28�ƻ����Z
					TagName=adressHead+CranePLCStatusBase::ADRESS_PLAN_DOWN_Z;
					TagValue=StringHelper::ToString(planDownZ);
					Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
					log.Info()<<"tag 28@...";
				}				

				//29�г�״̬ �������
				TagName=adressHead+CranePLCStatusBase::ADRESS_CRANE_STATUS;
				TagValue=StringHelper::ToString(craneStatus);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 29...";				

				//30 �г���������
				TagName=adressHead+CranePLCStatusBase::ADRESS_CRANE_ALARM;
				TagValue=StringHelper::ToString(craneAlarm);
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 30...";

				//31HEAT_BEAT
				TagName=adressHead+CranePLCStatusBase::ADRESS_CRANE_PLC_HEART_BEAT;
				TagValue=timeReceive;
				Tags.insert(map<string,string>::value_type( TagName , TagValue ) );
				log.Info()<<"tag 31...";

				//tag��д��ϵͳ
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
		log.Debug()<<"24......���Զ����Զ�����9";
		planUpX  = DB_INT_NULL;
		log.Debug()<<"25......���Զ����Զ�����9";
		planUpY = DB_INT_NULL;
		log.Debug()<<"26......���Զ����Զ�����9";
		planUpZ  = DB_INT_NULL;

		log.Debug()<<"27......���Զ����Զ�����9";
		planDownX  = DB_INT_NULL;
		log.Debug()<<"28......���Զ����Զ�����9";
		planDownY  = DB_INT_NULL;
		log.Debug()<<"29......���Զ����Զ�����9";
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





CLTS::CranePLCStatusDesc CranePLCStatusBase :: TransFromClass(CranePLCStatusBase cranePLCStatusBase)
{
	string functionName="CranePLCStatusBase :: TransFromStruct()";

	CLTS::CranePLCStatusDesc desc;

	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
	
		//1		CRANE_NO
		desc.craneNO=cranePLCStatusBase.getCraneNO();
		//2		READY
		desc.ready=cranePLCStatusBase.getReady();
		//3		CONTROL_MODE
		desc.controlMode=cranePLCStatusBase.getControlMode();
		//4		ASK_PLAN
		desc.askPlan=cranePLCStatusBase.getAskPlan();
		//5		TASK_EXCUTING
		desc.taskExcuting=cranePLCStatusBase.getTaskExcuting();
		//6		XACT
		desc.xAct=cranePLCStatusBase.getXAct();
		//7		YACT
		desc.yAct=cranePLCStatusBase.getYAct();
		//8		ZACT
		desc.zAct=cranePLCStatusBase.getZAct();
		//9		XSPEED
		desc.xSpeed=cranePLCStatusBase.getXSpeed();
		//10	YSPEED
		desc.ySpeed=cranePLCStatusBase.getYSpeed();
		//11	ZSPEED
		desc.zSpeed=cranePLCStatusBase.getZSpeed();
		//12	XDIR_P
		desc.xDirectPositive=cranePLCStatusBase.getXDirectPositive();
		//13	XDIR_N
		desc.xDirectNegative=cranePLCStatusBase.getXDirectNegative();
		//14	YDIR_P
		desc.yDirectPositive=cranePLCStatusBase.getYDirectPositive();
		//15	YDIR_N
		desc.yDirectNegative=cranePLCStatusBase.getYDirectNegative();
		//16	zDirectPositive
		desc.zDirectPositive=cranePLCStatusBase.getZDirectPositive();
		//17	zDirectNegative
		desc.zDirectNegative=cranePLCStatusBase.getZDirectNegative();
		//18	hasCoil
		desc.hasCoil=cranePLCStatusBase.getHasCoil();
		//19	weightLoaded
		desc.weightLoaded=cranePLCStatusBase.getWeightLoaded();
		//20	rotateAngleAct
		desc.rotateAngleAct=cranePLCStatusBase.getRotateAngleAct();
		//21	emgStop
		desc.emgStop=cranePLCStatusBase.getEmgStop();
		//22	orderID
		desc.orderID=cranePLCStatusBase.getOrderID();
		//23	planUpX
		desc.planUpX=cranePLCStatusBase.getPlanUpX();
		//24	planUpY
		desc.planUpY=cranePLCStatusBase.getPlanUpY();
		//25	planUpZ
		desc.planUpZ=cranePLCStatusBase.getPlanUpZ();
		//26	planDownX
		desc.planDownX=cranePLCStatusBase.getPlanDownX();
		//27	planDownY
		desc.planDownY=cranePLCStatusBase.getPlanDownY();
		//28	planDownZ
		desc.planDownZ=cranePLCStatusBase.getPlanDownZ();
		//29	craneStatus
		desc.craneStatus=cranePLCStatusBase.getCraneStatus();	
		//30 craneAlarm
		desc.craneAlarm=cranePLCStatusBase.getCraneAlarm();
		//31 timeReceive
		desc.timeReceive=cranePLCStatusBase.getTimeReceive();

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

	return desc;
}



CranePLCStatusBase CranePLCStatusBase :: TransFromStruct(CLTS::CranePLCStatusDesc desc)
{
	string functionName="CranePLCStatusBase :: TransFromStruct()";
	CranePLCStatusBase cranePLCStatusBase;
	LOG log(functionName, AUTO_CATCH_PID);
	
	try
	{
	
		//1		CRANE_NO
		cranePLCStatusBase.setCraneNO( desc.craneNO );
		//2		READY
		cranePLCStatusBase.setReady( desc.ready );
		//3		CONTROL_MODE
		cranePLCStatusBase.setControlMode( desc.controlMode );
		//4		ASK_PLAN
		cranePLCStatusBase.setAskPlan( desc.askPlan );
		//5		TASK_EXCUTING
		cranePLCStatusBase.setTaskExcuting( desc.taskExcuting );
		//6		XACT
		cranePLCStatusBase.setXAct( desc.xAct );
		//7		YACT
		cranePLCStatusBase.setYAct( desc.yAct );
		//8		ZACT
		cranePLCStatusBase.setZAct( desc.zAct );
		//9		XSPEED
		cranePLCStatusBase.setXSpeed( desc.xSpeed );
		//10	YSPEED
		cranePLCStatusBase.setYSpeed( desc.ySpeed );
		//11	ZSPEED
		cranePLCStatusBase.setZSpeed( desc.zSpeed );
		//12	XDIR_P
		cranePLCStatusBase.setXDirectPositive( desc.xDirectPositive );
		//13	XDIR_N
		cranePLCStatusBase.setXDirectNegative( desc.xDirectNegative );
		//14	YDIR_P
		cranePLCStatusBase.setYDirectPositive( desc.yDirectPositive );
		//15	YDIR_N
		cranePLCStatusBase.setYDirectNegative( desc.yDirectNegative );
		//16	zDirectPositive
		cranePLCStatusBase.setZDirectPositive( desc.zDirectPositive );
		//17	zDirectNegative
		cranePLCStatusBase.setZDirectNegative( desc.zDirectNegative );
		//18	hasCoil
		cranePLCStatusBase.setHasCoil( desc.hasCoil );
		//19	weightLoaded
		cranePLCStatusBase.setWeightLoaded( desc.weightLoaded );
		//20	rotateAngleAct
		cranePLCStatusBase.setRotateAngleAct( desc.rotateAngleAct );
		//21	emgStop
		cranePLCStatusBase.setEmgStop( desc.emgStop );
		//22	orderID
		cranePLCStatusBase.setOrderID( desc.orderID );
		//23	planUpX
		cranePLCStatusBase.setPlanUpX( desc.planUpX );
		//24	planUpY
		cranePLCStatusBase.setPlanUpY( desc.planUpY );
		//25	planUpZ
		cranePLCStatusBase.setPlanUpZ( desc.planUpZ );
		//26	planDownX
		cranePLCStatusBase.setPlanDownX( desc.planDownX );
		//27	planDownY
		cranePLCStatusBase.setPlanDownY( desc.planDownY );
		//28	planDownZ
		cranePLCStatusBase.setPlanDownZ( desc.planDownZ );
		//29	craneStatus
		cranePLCStatusBase.setCraneStatus( desc.craneStatus );
		//30	craneAlarm
		cranePLCStatusBase.setCraneAlarm( desc.craneAlarm );		
		//31 timeReceive
		cranePLCStatusBase.setTimeReceive(desc.timeReceive);

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


