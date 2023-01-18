#include "CarPlanBandInfo.h"

using namespace Monitor;

//作业类型定义
const  string CarPlanBandInfo::WORK_TYPE_XL = "XL";//卸料
const  string CarPlanBandInfo::WORK_TYPE_ZC = "ZC";//装车

//指令标记定义
const  string CarPlanBandInfo::ORDER_FLAG_1_NO_ORDER = "1";//无对应指令
const  string CarPlanBandInfo::ORDER_FLAG_2_HAVE_ORDER = "2";//有对应指令

//计划来源
const  string CarPlanBandInfo::PLAN_SRC_L3 = "L3";//L3计划
const  string CarPlanBandInfo::PLAN_SRC_EAF = "EAF";//电炉L2计划
const  string CarPlanBandInfo::PLAN_SRC_BOF = "BOF";//转炉L2计划

//车辆类型
const  string CarPlanBandInfo::CAR_TYPE_TRUCK = "1";//一般卡车 ：L3、EAF用
const  string CarPlanBandInfo::CAR_TYPE_TANK_TRUCK = "2";//料槽车 转炉用
const  string CarPlanBandInfo::CAR_TYPE_RGV = "3";//RGV 转炉用

//是否进入库区
const  string CarPlanBandInfo::ENTER_YARD_1_NO = "1";//未进入库区
const  string CarPlanBandInfo::ENTER_YARD_2_YES = "2";//已进入库区
const  string CarPlanBandInfo::ENTER_YARD_3_XLLK = "3";//卸料离开

CarPlanBandInfo :: CarPlanBandInfo(void)
{
	initValues();
}


CarPlanBandInfo :: ~CarPlanBandInfo(void)
{

}

void CarPlanBandInfo :: initValues()
{

	//1 carNO
	carNO=DF_STR_NULL;

	//2 carType
	carType=DF_STR_NULL;

	//3 workType
	workType=DF_STR_NULL;

	//4 planNO
	planNO=DF_STR_NULL;

	//5 planSrc
	planSrc=DF_STR_NULL;

	//6 planDetailID
	planDetailID=DF_INT_NULL;

	//7 gateNO
	gateNO = DF_STR_NULL;

	//8 targetGridNO
	targetGridNO = DF_STR_NULL;

	//9 targetParkingNO
	targetParkingNO = DF_STR_NULL;

	//10 enterFlag
	enterFlag = DF_STR_NULL;

	//11 orderFlag
	orderFlag=DF_STR_NULL;

	//12 bandTime
	bandTime=DB_TIME_NULL;



}


//1 CAR_NO
string CarPlanBandInfo :: getCarNO()
{
	return carNO;
}
void CarPlanBandInfo :: setCarNO(string theVal)
{
	carNO=theVal;
}

//2 CAR_TYPE
string CarPlanBandInfo :: getCarType()
{
	return carType;
}
void CarPlanBandInfo :: setCarType(string theVal)
{
	carType=theVal;
}

//3 WORK_TYPE
string CarPlanBandInfo :: getWorkType()
{
	return workType;
}
void CarPlanBandInfo :: setWorkType(string theVal)
{
	workType=theVal;
}

//4 PLAN_NO
string CarPlanBandInfo :: getPlanNO()
{
	return planNO;
}
void CarPlanBandInfo :: setPlanNO(string theVal)
{
	planNO=theVal;
}

//5 PLAN_SRC
string CarPlanBandInfo :: getPlanSrc()
{
	return planSrc;
}
void CarPlanBandInfo :: setPlanSrc(string theVal)
{
	planSrc=theVal;
}

//6 PLAN_DETAIL_ID
long CarPlanBandInfo :: getPlanDetailID()
{
	return planDetailID;
}
void CarPlanBandInfo :: setPlanDetailID(long theVal)
{
	planDetailID=theVal;
}

//7 GATE_NO
string CarPlanBandInfo :: getGateNO()
{
	return gateNO;
}
void CarPlanBandInfo :: setGateNO(string theVal)
{
	gateNO = theVal;
}


//8 TARGET_GRID_NO
string CarPlanBandInfo :: getTargetGridNO()
{
	return targetGridNO;
}
void CarPlanBandInfo :: setTargetGridNO(string theVal)
{
	targetGridNO = theVal;
}

//9 TARGET_PARKING_NO
string CarPlanBandInfo :: getTargetParkingNO()
{
	return targetParkingNO;
}
void CarPlanBandInfo :: setTargetParkingNO(string theVal)
{
	targetParkingNO = theVal;
}

//10 ENTER_FLAG
string CarPlanBandInfo :: getEnterFlag()
{
	return enterFlag;
}
void CarPlanBandInfo :: setEnterFlag(string theVal)
{
	enterFlag = theVal;
}

//11 ORDER_FLAG
string CarPlanBandInfo :: getOrderFlag()
{
	return orderFlag;
}
void CarPlanBandInfo :: setOrderFlag(string theVal)
{
	orderFlag = theVal;
}

//12 BAND_TIME
iDA::DateTime CarPlanBandInfo :: getBandTime()
{
	return bandTime;
}
void CarPlanBandInfo :: setBandTime(iDA::DateTime theVal)
{
	bandTime=theVal;
}




void CarPlanBandInfo :: logOutValues()
{
	string functionName="CarPlanBandInfo :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class CarPlanBandInfo--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t carNO="<<carNO<<endl;
	//2
	log.Debug()<<"\t carType="<<carType<<endl;
	//3
	log.Debug()<<"\t workType="<<workType<<endl;
	//4
	log.Debug()<<"\t planNO="<<planNO<<endl;
	//5
	log.Debug()<<"\t planSrc="<<planSrc<<endl;
	//6
	log.Debug()<<"\t planDetailID="<<planDetailID<<endl;
	//7
	log.Debug()<<"\t gateNO="<<gateNO<<endl;
	//8
	log.Debug()<<"\t targetGridNO="<<targetGridNO<<endl;
	//9
	log.Debug()<<"\t targetParkingNO="<<targetParkingNO<<endl;
	//10
	log.Debug()<<"\t enterFlag="<<enterFlag<<endl;
	//11
	log.Debug()<<"\t orderFlag="<<orderFlag<<endl;
	//12
	log.Debug()<<"\t bandTime="<<bandTime<<endl;


	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}

