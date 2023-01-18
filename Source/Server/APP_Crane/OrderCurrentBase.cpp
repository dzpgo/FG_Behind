#include "OrderCurrentBase.h"

using namespace Monitor;
//using namespace InterfaceMessage;

const string OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY="EMPTY";

const string OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_ORDER_INIT="ORDER_INIT";

const string OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS="COIL_UP_PROCESS";

const string OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS="COIL_DOWN_PROCESS";

OrderCurrentBase :: OrderCurrentBase(void)
{
	initValues();
}


OrderCurrentBase :: ~OrderCurrentBase(void)
{

}

void OrderCurrentBase :: initValues()
{

	//1 orderNO
	orderNO=DB_INT_NULL;

	//2 bayNO
	bayNO=DB_STR_NULL;

	//3 matCode
	matCode=DB_STR_NULL;

	//4 compCode
	compCode=DB_STR_NULL;

	//5 matType
	matType=DB_STR_NULL;

	//6 matReqWgt
	matReqWgt=DB_INT_NULL;

	//7 matActWgt
	matActWgt=DB_INT_NULL;

	//8 matCurWgt
	matCurWgt=DB_INT_NULL;

	//9 orderType
	orderType=DB_STR_NULL;

	//10 orderPriority
	orderPriority=DB_INT_NULL;

	//11 fromStockNO
	fromStockNO=DB_STR_NULL;

	//12 toStockNO
	toStockNO=DB_STR_NULL;

	//13 cmdStatus
	cmdStatus=DB_STR_NULL;

	//14 cmdSeq
	cmdSeq=DB_INT_NULL;

	//15 craneNO
	craneNO=DB_STR_NULL;

	//16 carScanNO
	carScanNO=DB_STR_NULL;	

	//17 matDownScanNO
	matDownScanNO=DB_STR_NULL;	

	//18 planUpX
	planUpX=DB_INT_NULL;

	//19 planUpY
	planUpY=DB_INT_NULL;

	//20 planUpZ
	planUpZ=DB_INT_NULL;

	//21 upRotateAngle
	upRotateAngle=DB_INT_NULL;

	//22 matDownScanNO
	matDownScanNO = DB_STR_NULL;
	
	//23 planDownX
	planDownX=DB_INT_NULL;

	//24 planDownY
	planDownY=DB_INT_NULL;

	//25 planDownZ
	planDownZ=DB_INT_NULL;

	//26 downRotateAngle
	downRotateAngle=DB_INT_NULL;

}


//1 ORDER_NO
long OrderCurrentBase :: getOrderNO()
{
	return orderNO;
}
void OrderCurrentBase :: setOrderNO(long theVal)
{
	orderNO=theVal;
}

//2 BAY_NO
string OrderCurrentBase :: getBayNO()
{
	return bayNO;
}
void OrderCurrentBase :: setBayNO(string theVal)
{
	bayNO=theVal;
}

//3 MAT_CODE
string OrderCurrentBase :: getMatCode()
{
	return matCode;
}
void OrderCurrentBase :: setMatCode(string theVal)
{
	matCode=theVal;
}

//4 COMP_CODE
string OrderCurrentBase :: getCompCode()
{
	return compCode;
}
void OrderCurrentBase :: setCompCode(string theVal)
{
	compCode=theVal;
}

//5 MAT_TYPE
string OrderCurrentBase :: getMatType()
{
	return matType;
}
void OrderCurrentBase :: setMatType(string theVal)
{
	matType=theVal;
}

//6 MAT_REQ_WGT
long OrderCurrentBase :: getMatReqWgt()
{
	return matReqWgt;
}
void OrderCurrentBase :: setMatReqWgt(long theVal)
{
	matReqWgt=theVal;
}

//7 MAT_ACT_WGT
long OrderCurrentBase :: getMatActWgt()
{
	return matActWgt;
}
void OrderCurrentBase :: setMatActWgt(long theVal)
{
	matActWgt=theVal;
}

//8 MAT_CUR_WGT
long OrderCurrentBase :: getMatCurWgt()
{
	return matCurWgt;
}
void OrderCurrentBase :: setMatCurWgt(long theVal)
{
	matCurWgt=theVal;
}

//9 ORDER_TYPE
string OrderCurrentBase :: getOrderType()
{
	return orderType;
}
void OrderCurrentBase :: setOrderType(string theVal)
{
	orderType=theVal;
}

//10 ORDER_PRIORITY
long OrderCurrentBase :: getOrderPriority()
{
	return orderPriority;
}
void OrderCurrentBase :: setOrderPriority(long theVal)
{
	orderPriority=theVal;
}

//11 FROM_STOCK_NO
string OrderCurrentBase :: getFromStockNO()
{
	return fromStockNO;
}
void OrderCurrentBase :: setFromStockNO(string theVal)
{
	fromStockNO=theVal;
}

//12 TO_STOCK_NO
string OrderCurrentBase :: getToStockNO()
{
	return toStockNO;
}
void OrderCurrentBase :: setToStockNO(string theVal)
{
	toStockNO=theVal;
}

//13 CMD_STATUS
string OrderCurrentBase :: getCmdStatus()
{
	return cmdStatus;
}
void OrderCurrentBase :: setCmdStatus(string theVal)
{
	cmdStatus=theVal;
}

//14 CMD_SEQ
long OrderCurrentBase :: getCmdSeq()
{
	return cmdSeq;
}
void OrderCurrentBase :: setCmdSeq(long theVal)
{
	cmdSeq=theVal;
}

//15 CRANE_NO
string OrderCurrentBase :: getCraneNO()
{
	return craneNO;
}
void OrderCurrentBase :: setCraneNO(string theVal)
{
	craneNO=theVal;
}

//16 CAR_SCAN_NO
string OrderCurrentBase :: getCarScanNO()
{
	return carScanNO;
}
void OrderCurrentBase :: setCarScanNO(string theVal)
{
	carScanNO=theVal;
}

//17 MAT_UP_SCAN_NO
string OrderCurrentBase :: getMatUpScanNO()
{
	return matUpScanNO;
}
void OrderCurrentBase :: setMatUpScanNO(string theVal)
{
	matUpScanNO=theVal;
}

//18 PLAN_UP_X
long OrderCurrentBase :: getPlanUpX()
{
	return planUpX;
}
void OrderCurrentBase :: setPlanUpX(long theVal)
{
	planUpX=theVal;
}

//19 PLAN_UP_Y
long OrderCurrentBase :: getPlanUpY()
{
	return planUpY;
}
void OrderCurrentBase :: setPlanUpY(long theVal)
{
	planUpY=theVal;
}

//20 PLAN_UP_Z
long OrderCurrentBase :: getPlanUpZ()
{
	return planUpZ;
}
void OrderCurrentBase :: setPlanUpZ(long theVal)
{
	planUpZ=theVal;
}

//21 UP_ROTATE_ANGLE
long OrderCurrentBase :: getUpRotateAngle()
{
	return upRotateAngle;
}
void OrderCurrentBase :: setUpRotateAngle(long theVal)
{
	upRotateAngle=theVal;
}

//22 MAT_DOWN_SCAN_NO
string OrderCurrentBase :: getMatDownScanNO()
{
	return matDownScanNO;
}
void OrderCurrentBase :: setMatDownScanNO(string theVal)
{
	matDownScanNO=theVal;
}

//23 PLAN_DOWN_X
long OrderCurrentBase :: getPlanDownX()
{
	return planDownX;
}
void OrderCurrentBase :: setPlanDownX(long theVal)
{
	planDownX=theVal;
}

//24 PLAN_DOWN_Y
long OrderCurrentBase :: getPlanDownY()
{
	return planDownY;
}
void OrderCurrentBase :: setPlanDownY(long theVal)
{
	planDownY=theVal;
}

//25 PLAN_DOWN_Z
long OrderCurrentBase :: getPlanDownZ()
{
	return planDownZ;
}
void OrderCurrentBase :: setPlanDownZ(long theVal)
{
	planDownZ=theVal;
}

//26 Down_Rotate_Angle
long OrderCurrentBase :: getDownRotateAngle()
{
	return downRotateAngle;
}
void OrderCurrentBase :: setDownRotateAngle(long theVal)
{
	downRotateAngle=theVal;
}


void OrderCurrentBase :: logOutValues()
{
	string functionName="OrderCurrentBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class OrderCurrentBase--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t orderNO="<<orderNO<<endl;
	//2
	log.Debug()<<"\t bayNO="<<bayNO<<endl;
	//3
	log.Debug()<<"\t matCode="<<matCode<<endl;
	//4
	log.Debug()<<"\t compCode="<<compCode<<endl;
	//5
	log.Debug()<<"\t matType="<<matType<<endl;
	//6
	log.Debug()<<"\t matReqWgt="<<matReqWgt<<endl;
	//7
	log.Debug()<<"\t matActWgt="<<matActWgt<<endl;
	//8
	log.Debug()<<"\t matCurWgt="<<matCurWgt<<endl;
	//9
	log.Debug()<<"\t orderType="<<orderType<<endl;
	//10
	log.Debug()<<"\t orderPriority="<<orderPriority<<endl;
	//11
	log.Debug()<<"\t fromStockNO="<<fromStockNO<<endl;
	//12
	log.Debug()<<"\t toStockNO="<<toStockNO<<endl;
	//13
	log.Debug()<<"\t cmdStatus="<<cmdStatus<<endl;
	//14
	log.Debug()<<"\t cmdSeq="<<cmdSeq<<endl;
	//15
	log.Debug()<<"\t craneNO="<<craneNO<<endl;
	//16
	log.Debug()<<"\t carScanNO="<<carScanNO<<endl;
	//17
	log.Debug()<<"\t matUpScanNO="<<matUpScanNO<<endl;
	//18
	log.Debug()<<"\t planUpX="<<planUpX<<endl;
	//19
	log.Debug()<<"\t planUpY="<<planUpY<<endl;
	//20
	log.Debug()<<"\t planUpZ="<<planUpZ<<endl;
	//21
	log.Debug()<<"\t upRotateAngle="<<upRotateAngle<<endl;
	//22
	log.Debug()<<"\t matDownScanNO="<<matDownScanNO<<endl;
	//23
	log.Debug()<<"\t planDownX="<<planDownX<<endl;
	//24
	log.Debug()<<"\t planDownY="<<planDownY<<endl;
	//25
	log.Debug()<<"\t planDownZ="<<planDownZ<<endl;
	//26
	log.Debug()<<"\t downRotateAngle="<<downRotateAngle<<endl;
	

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}




