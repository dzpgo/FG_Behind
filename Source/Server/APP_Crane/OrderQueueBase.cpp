#include "OrderQueueBase.h"

using namespace Monitor;

//指令类型定义
const  string OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11 = "11";//L3计划物料入库
const  string OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 = "21";//L3计划物料装车
const  string OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 = "22";//电炉计划物料装车
const  string OrderQueueBase::ORDER_TYPE_BOF_YARD_TO_RGV_23 = "23";//转炉计划物料装RGV
const  string OrderQueueBase::ORDER_TYPE_BOF_YARD_TO_CAR_24 = "24";//转炉计划物料装运槽车

//指令状态定义
const string OrderQueueBase::CMD_STATUS_INIT_0 = "0";//指令初始化
const string OrderQueueBase::CMD_STATUS_START_1 = "1";//指令获取
const string OrderQueueBase::CMD_STATUS_SRS_S = "S";//激光扫描
const string OrderQueueBase::CMD_STATUS_PLAN_UP_POS_ARRIVE_2 = "2";//取料点上方
const string OrderQueueBase::CMD_STATUS_EMPTY_CLAMP_DOWN_3 = "3";//吸盘空载下降到位
const string OrderQueueBase::CMD_STATUS_CLAMP_EMPTY_TO_FULL_4 = "4";//吸盘空载变有载
const string OrderQueueBase::CMD_STATUS_FULL_CLAMP_UP_5 = "5";//吸盘重载上升到位
const string OrderQueueBase::CMD_STATUS_PLAN_DOWN_POS_ARRIVE_6 = "6";//放料点上方
const string OrderQueueBase::CMD_STATUS_FULL_CLAMP_DOWN_7 = "7";//吸盘重载下降到位
const string OrderQueueBase::CMD_STATUS_CLAMP_FULL_TO_EMPTY_8 = "8";//吸盘重载变空载
const string OrderQueueBase::CMD_STATUS_EMPTY_CLAMP_UP_9 = "9";//吸盘空载上升到位


//指令是否可执行标记
const string OrderQueueBase::EXE_ENABLE_YES_1 = "1";//指令可执行
const string OrderQueueBase::EXE_ENABLE_NO_2 ="2"; //指令不可执行

OrderQueueBase :: OrderQueueBase(void)
{
	initValues();
}


OrderQueueBase :: ~OrderQueueBase(void)
{

}

void OrderQueueBase :: initValues()
{

	//1 orderNO
	orderNO=DF_INT_NULL;

	//2 orderGroupNO
	orderGroupNO=DF_INT_NULL;

	//3 exeSeq
	exeSeq=DF_INT_NULL;

	//4 orderType
	orderType=DF_STR_NULL;

	//5 orderPriority
	orderPriority=DF_INT_NULL;

	//6 exeEnable
	exeEnable=DF_STR_NULL;

	//7 craneNO
	craneNO=DF_STR_NULL;

	//8 cmdStatus
	cmdStatus=DF_STR_NULL;

	//9 cmdSeq
	cmdSeq=DF_INT_NULL;

	//10 planSrc
	planSrc=DF_STR_NULL;

	//11 planNO
	planNO=DF_STR_NULL;

	//12 planDetailID
	planDetailID=DF_INT_NULL;

	//13 scrapCode
	scrapCode=DF_STR_NULL;

	//14 reqWeight
	reqWeight=DF_INT_NULL;

	//15 carNO
	carNO=DF_STR_NULL;

	//16 carType
	carType=DF_STR_NULL;

	//17 bayNO
	bayNO=DF_STR_NULL;

	//18 matCode
	matCode=DF_STR_NULL;	

	//19 compCode
	compCode=DF_STR_NULL;	

	//20 calWeight
	calWeight=DF_INT_NULL;

	//21 actWeight
	actWeight=DF_INT_NULL;

	//22 fromStockNO
	fromStockNO=DF_STR_NULL;

	//23 toStockNO
	toStockNO=DF_STR_NULL;

	//24 downPosSeq
	downPosSeq=DF_INT_NULL;	

	//25 curWeight
	curWeight = DF_INT_NULL;

}


//1 ORDER_NO
long OrderQueueBase :: getOrderNO()
{
	return orderNO;
}
void OrderQueueBase :: setOrderNO(long theVal)
{
	orderNO=theVal;
}

//2 ORDER_GROUP_NO
long OrderQueueBase :: getOrderGroupNO()
{
	return orderGroupNO;
}
void OrderQueueBase :: setOrderGroupNO(long theVal)
{
	orderGroupNO=theVal;
}

//3 EXE_SEQ
long OrderQueueBase :: getExeSeq()
{
	return exeSeq;
}
void OrderQueueBase :: setExeSeq(long theVal)
{
	exeSeq=theVal;
}

//4 ORDER_TYPE
string OrderQueueBase :: getOrderType()
{
	return orderType;
}
void OrderQueueBase :: setOrderType(string theVal)
{
	orderType=theVal;
}

//5 ORDER_PRIORITY
long OrderQueueBase :: getOrderPriority()
{
	return orderPriority;
}
void OrderQueueBase :: setOrderPriority(long theVal)
{
	orderPriority=theVal;
}

//6 EXE_ENABLE
string OrderQueueBase :: getExeEnable()
{
	return exeEnable;
}
void OrderQueueBase :: setExeEnable(string theVal)
{
	exeEnable=theVal;
}

//7 CRANE_NO
string OrderQueueBase :: getCraneNO()
{
	return craneNO;
}
void OrderQueueBase :: setCraneNO(string theVal)
{
	craneNO = theVal;
}

//8 CMD_STATUS
string OrderQueueBase :: getCmdStatus()
{
	return cmdStatus;
}
void OrderQueueBase :: setCmdStatus(string theVal)
{
	cmdStatus = theVal;
}

//9 CMD_SEQ
long OrderQueueBase :: getCmdSeq()
{
	return cmdSeq;
}
void OrderQueueBase :: setCmdSeq(long theVal)
{
	cmdSeq = theVal;
}

//10 PLAN_SRC
string OrderQueueBase :: getPlanSrc()
{
	return planSrc;
}
void OrderQueueBase :: setPlanSrc(string theVal)
{
	planSrc=theVal;
}

//11 PLAN_NO
string OrderQueueBase :: getPlanNO()
{
	return planNO;
}
void OrderQueueBase :: setPlanNO(string theVal)
{
	planNO = theVal;
}

//12 PLAN_DETAIL_ID
long OrderQueueBase :: getPlanDetailID()
{
	return planDetailID;
}
void OrderQueueBase :: setPlanDetailID(long theVal)
{
	planDetailID=theVal;
}

//13 SCRAP_CODE
string OrderQueueBase :: getScrapCode()
{
	return scrapCode;
}
void OrderQueueBase :: setScrapCode(string theVal)
{
	scrapCode=theVal;
}

//14 REQ_WEIGHT
long OrderQueueBase :: getReqWeight()
{
	return reqWeight;
}
void OrderQueueBase :: setReqWeight(long theVal)
{
	reqWeight=theVal;
}

//15 CAR_NO
string OrderQueueBase :: getCarNO()
{
	return carNO;
}
void OrderQueueBase :: setCarNO(string theVal)
{
	carNO=theVal;
}

//16 CAR_TYPE
string OrderQueueBase :: getCarType()
{
	return carType;
}
void OrderQueueBase :: setCarType(string theVal)
{
	carType=theVal;
}

//17 BAY_NO
string OrderQueueBase :: getBayNO()
{
	return bayNO;
}
void OrderQueueBase :: setBayNO(string theVal)
{
	bayNO=theVal;
}

//18 MAT_CODE
string OrderQueueBase :: getMatCode()
{
	return matCode;
}
void OrderQueueBase :: setMatCode(string theVal)
{
	matCode=theVal;
}

//19 COMP_CODE
string OrderQueueBase :: getCompCode()
{
	return compCode;
}
void OrderQueueBase :: setCompCode(string theVal)
{
	compCode=theVal;
}

//20 CAL_WEIGHT
long OrderQueueBase :: getCalWeight()
{
	return calWeight;
}
void OrderQueueBase :: setCalWeight(long theVal)
{
	calWeight=theVal;
}

//21 ACT_WEIGHT
long OrderQueueBase :: getActWeight()
{
	return actWeight;
}
void OrderQueueBase :: setActWeight(long theVal)
{
	actWeight=theVal;
}


//22 FROM_STOCK_NO
string OrderQueueBase :: getFromStockNO()
{
	return fromStockNO;
}
void OrderQueueBase :: setFromStockNO(string theVal)
{
	fromStockNO=theVal;
}

//23 TO_STOCK_NO
string OrderQueueBase :: getToStockNO()
{
	return toStockNO;
}
void OrderQueueBase :: setToStockNO(string theVal)
{
	toStockNO=theVal;
}

//24 DOWN_POS_SEQ
long OrderQueueBase :: getDownPosSeq()
{
	return downPosSeq;
}
void OrderQueueBase :: setDownPosSeq(long theVal)
{
	downPosSeq=theVal;
}

//25 CUR_WEIGHT
long OrderQueueBase :: getCurWeight()
{
	return curWeight;
}
void OrderQueueBase :: setCurWeight(long theVal)
{
	curWeight=theVal;
}




void OrderQueueBase :: logOutValues()
{
	string functionName="OrderQueueBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class OrderQueueBase--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t orderNO="<<orderNO<<endl;
	//2
	log.Debug()<<"\t orderGroupNO="<<orderGroupNO<<endl;
	//3
	log.Debug()<<"\t exeSeq="<<exeSeq<<endl;
	//4
	log.Debug()<<"\t orderType="<<orderType<<endl;
	//5
	log.Debug()<<"\t orderPriority="<<orderPriority<<endl;
	//6
	log.Debug()<<"\t exeEnable="<<exeEnable<<endl;
	//7
	log.Debug()<<"\t craneNO="<<craneNO<<endl;
	//8
	log.Debug()<<"\t cmdStatus="<<cmdStatus<<endl;
	//9
	log.Debug()<<"\t cmdSeq="<<cmdSeq<<endl;
	//10
	log.Debug()<<"\t planSrc="<<planSrc<<endl;
	//11
	log.Debug()<<"\t planNO="<<planNO<<endl;
	//12
	log.Debug()<<"\t planDetailID="<<planDetailID<<endl;
	//13
	log.Debug()<<"\t scrapCode="<<scrapCode<<endl;
	//14
	log.Debug()<<"\t reqWeight="<<reqWeight<<endl;
	//15
	log.Debug()<<"\t carNO="<<carNO<<endl;
	//16
	log.Debug()<<"\t carType="<<carType<<endl;
	//17
	log.Debug()<<"\t bayNO="<<bayNO<<endl;
	//18
	log.Debug()<<"\t matCode="<<matCode<<endl;
	//19
	log.Debug()<<"\t compCode="<<compCode<<endl;	
	//20
	log.Debug()<<"\t calWeight="<<calWeight<<endl;
	//21
	log.Debug()<<"\t actWeight="<<actWeight<<endl;
	//22
	log.Debug()<<"\t fromStockNO="<<fromStockNO<<endl;
	//23
	log.Debug()<<"\t toStockNO="<<toStockNO<<endl;
	//24
	log.Debug()<<"\t downPosSeq="<<downPosSeq<<endl;
	//25
	log.Debug()<<"\t curWeight="<<curWeight<<endl;

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}

