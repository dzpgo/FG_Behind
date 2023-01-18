#include "OrderDataBase.h"

using namespace Monitor;

//指令类型定义
const  string OrderDataBase::ORDER_TYPE_L3_CAR_TO_YARD_11 = "11";//L3计划物料入库
const  string OrderDataBase::ORDER_TYPE_L3_YARD_TO_CAR_21 = "21";//L3计划物料装车
const  string OrderDataBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 = "22";//电炉计划物料装车
const  string OrderDataBase::ORDER_TYPE_BOF_YARD_TO_RGV_23 = "23";//转炉计划物料装RGV
const  string OrderDataBase::ORDER_TYPE_BOF_YARD_TO_CAR_24 = "24";//转炉计划物料装运槽车

//指令状态定义
const  string OrderDataBase::ORDER_STATUS_NOT_START_1 = "1";//指令未开始
const  string OrderDataBase::ORDER_STATUS_START_2 = "2";//指令开始
const  string OrderDataBase::ORDER_STATUS_END_3 = "3";//指令结束

//指令删除标识定义
const  string OrderDataBase::ORDER_DEL_FLAG_NOT_DEL_1 = "1";//指令未删除
const  string OrderDataBase::ORDER_DEL_FLAG_DEL_2 = "2";//指令删除

//质检标识
const  string OrderDataBase::ORDER_QC_FLAG_1 = "1";//需要质检
const  string OrderDataBase::ORDER_QC_FLAG_0 = "0";//不需要质检

OrderDataBase :: OrderDataBase(void)
{
	initValues();
}


OrderDataBase :: ~OrderDataBase(void)
{

}

void OrderDataBase :: initValues()
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

	//6 orderStatus
	orderStatus=DF_STR_NULL;

	//7 orderDelFlag
	orderDelFlag=DF_STR_NULL;

	//8 planSrc
	planSrc=DF_STR_NULL;

	//9 planNO
	planNO=DF_STR_NULL;

	//10 planDetailID
	planDetailID=DF_INT_NULL;

	//11 scrapCode
	scrapCode=DF_STR_NULL;

	//12 weight
	reqWeight=DF_INT_NULL;

	//13 carNO
	carNO=DF_STR_NULL;

	//14 carType
	carType=DF_STR_NULL;

	//15 bayNO
	bayNO=DF_STR_NULL;

	//16 matCode
	matCode=DF_STR_NULL;	

	//17 compCode
	compCode=DF_STR_NULL;	

	//18 calWeight
	calWeight=DF_INT_NULL;

	//19 actWeight
	actWeight=DF_INT_NULL;

	//20 fromStockNO
	fromStockNO=DF_STR_NULL;

	//21 toStockNO
	toStockNO=DF_STR_NULL;

	//22 downPosSeq
	downPosSeq=DF_INT_NULL;	

	//23 qcFlag
	qcFlag=DF_STR_NULL;

}


//1 ORDER_NO
long OrderDataBase :: getOrderNO()
{
	return orderNO;
}
void OrderDataBase :: setOrderNO(long theVal)
{
	orderNO=theVal;
}

//2 ORDER_GROUP_NO
long OrderDataBase :: getOrderGroupNO()
{
	return orderGroupNO;
}
void OrderDataBase :: setOrderGroupNO(long theVal)
{
	orderGroupNO=theVal;
}

//3 EXE_SEQ
long OrderDataBase :: getExeSeq()
{
	return exeSeq;
}
void OrderDataBase :: setExeSeq(long theVal)
{
	exeSeq=theVal;
}

//4 ORDER_TYPE
string OrderDataBase :: getOrderType()
{
	return orderType;
}
void OrderDataBase :: setOrderType(string theVal)
{
	orderType=theVal;
}

//5 ORDER_PRIORITY
long OrderDataBase :: getOrderPriority()
{
	return orderPriority;
}
void OrderDataBase :: setOrderPriority(long theVal)
{
	orderPriority=theVal;
}

//6 ORDER_STATUS
string OrderDataBase :: getOrderStatus()
{
	return orderStatus;
}
void OrderDataBase :: setOrderStatus(string theVal)
{
	orderStatus=theVal;
}

//7 ORDER_DEL_FLAG
string OrderDataBase :: getOrderDelFlag()
{
	return orderDelFlag;
}
void OrderDataBase :: setOrderDelFlag(string theVal)
{
	orderDelFlag = theVal;
}

//8 PLAN_SRC
string OrderDataBase :: getPlanSrc()
{
	return planSrc;
}
void OrderDataBase :: setPlanSrc(string theVal)
{
	planSrc=theVal;
}

//9 PLAN_NO
string OrderDataBase :: getPlanNO()
{
	return planNO;
}
void OrderDataBase :: setPlanNO(string theVal)
{
	planNO = theVal;
}

//10 PLAN_DETAIL_ID
long OrderDataBase :: getPlanDetailID()
{
	return planDetailID;
}
void OrderDataBase :: setPlanDetailID(long theVal)
{
	planDetailID=theVal;
}

//11 SCRAP_CODE
string OrderDataBase :: getScrapCode()
{
	return scrapCode;
}
void OrderDataBase :: setScrapCode(string theVal)
{
	scrapCode=theVal;
}

//12 REQ_WEIGHT
long OrderDataBase :: getReqWeight()
{
	return reqWeight;
}
void OrderDataBase :: setReqWeight(long theVal)
{
	reqWeight=theVal;
}

//13 CAR_NO
string OrderDataBase :: getCarNO()
{
	return carNO;
}
void OrderDataBase :: setCarNO(string theVal)
{
	carNO=theVal;
}

//14 CAR_TYPE
string OrderDataBase :: getCarType()
{
	return carType;
}
void OrderDataBase :: setCarType(string theVal)
{
	carType=theVal;
}

//15 BAY_NO
string OrderDataBase :: getBayNO()
{
	return bayNO;
}
void OrderDataBase :: setBayNO(string theVal)
{
	bayNO=theVal;
}

//16 MAT_CODE
string OrderDataBase :: getMatCode()
{
	return matCode;
}
void OrderDataBase :: setMatCode(string theVal)
{
	matCode=theVal;
}

//17 COMP_CODE
string OrderDataBase :: getCompCode()
{
	return compCode;
}
void OrderDataBase :: setCompCode(string theVal)
{
	compCode=theVal;
}

//18 CAL_WEIGHT
long OrderDataBase :: getCalWeight()
{
	return calWeight;
}
void OrderDataBase :: setCalWeight(long theVal)
{
	calWeight=theVal;
}

//19 ACT_WEIGHT
long OrderDataBase :: getActWeight()
{
	return actWeight;
}
void OrderDataBase :: setActWeight(long theVal)
{
	actWeight=theVal;
}


//20 FROM_STOCK_NO
string OrderDataBase :: getFromStockNO()
{
	return fromStockNO;
}
void OrderDataBase :: setFromStockNO(string theVal)
{
	fromStockNO=theVal;
}

//21 TO_STOCK_NO
string OrderDataBase :: getToStockNO()
{
	return toStockNO;
}
void OrderDataBase :: setToStockNO(string theVal)
{
	toStockNO=theVal;
}

//22 DOWN_POS_SEQ
long OrderDataBase :: getDownPosSeq()
{
	return downPosSeq;
}
void OrderDataBase :: setDownPosSeq(long theVal)
{
	downPosSeq=theVal;
}

//23 QC_FLAG
string OrderDataBase :: getQCFlag()
{
	return qcFlag;
}
void OrderDataBase :: setQCFlag(string theVal)
{
	qcFlag=theVal;
}




void OrderDataBase :: logOutValues()
{
	string functionName="OrderDataBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class OrderDataBase--------------------------------------"<<endl;

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
	log.Debug()<<"\t orderStatus="<<orderStatus<<endl;
	//7
	log.Debug()<<"\t orderDelFlag="<<orderDelFlag<<endl;
	//8
	log.Debug()<<"\t planSrc="<<planSrc<<endl;
	//9
	log.Debug()<<"\t planNO="<<planNO<<endl;
	//10
	log.Debug()<<"\t planDetailID="<<planDetailID<<endl;
	//11
	log.Debug()<<"\t scrapCode="<<scrapCode<<endl;
	//12
	log.Debug()<<"\t reqWeight="<<reqWeight<<endl;
	//13
	log.Debug()<<"\t carNO="<<carNO<<endl;
	//14
	log.Debug()<<"\t carType="<<carType<<endl;
	//15
	log.Debug()<<"\t bayNO="<<bayNO<<endl;
	//16
	log.Debug()<<"\t matCode="<<matCode<<endl;
	//17
	log.Debug()<<"\t compCode="<<compCode<<endl;	
	//18
	log.Debug()<<"\t calWeight="<<calWeight<<endl;
	//19
	log.Debug()<<"\t actWeight="<<actWeight<<endl;
	//20
	log.Debug()<<"\t fromStockNO="<<fromStockNO<<endl;
	//21
	log.Debug()<<"\t toStockNO="<<toStockNO<<endl;
	//22
	log.Debug()<<"\t downPosSeq="<<downPosSeq<<endl;
	//23
	log.Debug()<<"\t qcFlag="<<qcFlag<<endl;

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}

