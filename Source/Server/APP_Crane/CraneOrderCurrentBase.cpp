#include "CraneOrderCurrentBase.h"

using namespace Monitor;
//using namespace InterfaceMessage;

const string CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY="EMPTY";

const string CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_ORDER_INIT="ORDER_INIT";

const string CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS="COIL_UP_PROCESS";

const string CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS="COIL_DOWN_PROCESS";

CraneOrderCurrentBase :: CraneOrderCurrentBase(void)
{
	initValues();
}


CraneOrderCurrentBase :: ~CraneOrderCurrentBase(void)
{

}

void CraneOrderCurrentBase :: initValues()
{

	//1 orderNO
	orderNO=DB_INT_NULL;

	//2 bayNO
	bayNO=DB_STR_NULL;

	//3 matNO
	matNO=DB_STR_NULL;

	//4 orderType
	orderType=DB_STR_NULL;

	//5 orderPriority
	orderPriority=DB_INT_NULL;

	//6 fromStockNO
	fromStockNO=DB_STR_NULL;

	//6.5 fromStockType
	fromStockType = DB_STR_NULL;

	//7 toStockNO
	toStockNO=DB_STR_NULL;

	//7.5 toStockType
	toStockType = DB_STR_NULL;

	//8 cmdStatus
	cmdStatus=DB_STR_NULL;

	//9 craneNO
	craneNO=DB_STR_NULL;

	//10 planUpX
	planUpX=DB_INT_NULL;

	//11 planUpY
	planUpY=DB_INT_NULL;

	//12 planUpZ
	planUpZ=DB_INT_NULL;

	//13 upRotateAngleSet
	upRotateAngleSet=DB_INT_NULL;

	//13 upRotateAngleSet
	upRotateAngleSet=DB_INT_NULL;

	//14 clampWidthSet
	clampWidthSet=DB_INT_NULL;

	//15 planDownX
	planDownX=DB_INT_NULL;

	//16 planDownY
	planDownY=DB_INT_NULL;

	//17 planDownZ
	planDownZ=DB_INT_NULL;



	//18 downRotateAngleSet
	downRotateAngleSet=DB_INT_NULL;

	//19 coilWidth
	coilWidth=DB_INT_NULL;

	//20 coilWeight
	coilWeight=DB_INT_NULL;

	//21 coilWeight
	coilOutDia=DB_INT_NULL;

	//22 COIL_IN_DIA
	coilInDia=DB_INT_NULL;

	//23 FLOOR_UP_Z
	floor_Up_Z=DB_INT_NULL;

	//24 FLAG_SMALL_COIL
	flag_Small_Coil=DB_INT_NULL;

	//25 FLOOR_DOWN_Z
	floor_Down_Z=DB_INT_NULL;

}


//1 ORDER_NO
long CraneOrderCurrentBase :: getOrderNO()
{
	return orderNO;
}
void CraneOrderCurrentBase :: setOrderNO(long theVal)
{
	orderNO=theVal;
}

//2 BAY_NO
string CraneOrderCurrentBase :: getBayNO()
{
	return bayNO;
}
void CraneOrderCurrentBase :: setBayNO(string theVal)
{
	bayNO=theVal;
}

//3 MAT_NO
string CraneOrderCurrentBase :: getMatNO()
{
	return matNO;
}
void CraneOrderCurrentBase :: setMatNO(string theVal)
{
	matNO=theVal;
}

//4 ORDER_TYPE
string CraneOrderCurrentBase :: getOrderType()
{
	return orderType;
}
void CraneOrderCurrentBase :: setOrderType(string theVal)
{
	orderType=theVal;
}

//5 ORDER_PRIORITY
long CraneOrderCurrentBase :: getOrderPriority()
{
	return orderPriority;
}
void CraneOrderCurrentBase :: setOrderPriority(long theVal)
{
	orderPriority=theVal;
}

//6 FROM_STOCK_NO
string CraneOrderCurrentBase :: getFromStockNO()
{
	return fromStockNO;
}
void CraneOrderCurrentBase :: setFromStockNO(string theVal)
{
	fromStockNO=theVal;
}

//6.5 FROM_STOCK_TYPE
string CraneOrderCurrentBase :: getFromStockType()
{
	return fromStockType;
}
void CraneOrderCurrentBase :: setFromStockType(string theVal)
{
	fromStockType = theVal;
}

//7 TO_STOCK_NO
string CraneOrderCurrentBase :: getToStockNO()
{
	return toStockNO;
}
void CraneOrderCurrentBase :: setToStockNO(string theVal)
{
	toStockNO=theVal;
}

//7.5 TO_STOCK_TYPE
string CraneOrderCurrentBase :: getToStockType()
{
	return toStockType;
}
void CraneOrderCurrentBase :: setToStockType(string theVal)
{
	toStockType = theVal;
}

//8 CMD_STATUS
string CraneOrderCurrentBase :: getCMDStatus()
{
	return cmdStatus;
}
void CraneOrderCurrentBase :: setCMDStatus(string theVal)
{
	cmdStatus=theVal;
}

//9 CRANE_NO
string CraneOrderCurrentBase :: getCraneNO()
{
	return craneNO;
}
void CraneOrderCurrentBase :: setCraneNO(string theVal)
{
	craneNO=theVal;
}

//10 PLAN_UP_X
long CraneOrderCurrentBase :: getPlanUpX()
{
	return planUpX;
}
void CraneOrderCurrentBase :: setPlanUpX(long theVal)
{
	planUpX=theVal;
}

//11 PLAN_UP_Y
long CraneOrderCurrentBase :: getPlanUpY()
{
	return planUpY;
}
void CraneOrderCurrentBase :: setPlanUpY(long theVal)
{
	planUpY=theVal;
}

//12 PLAN_UP_Z
long CraneOrderCurrentBase :: getPlanUpZ()
{
	return planUpZ;
}
void CraneOrderCurrentBase :: setPlanUpZ(long theVal)
{
	planUpZ=theVal;
}

//13 UP_ROTATE_ANGLE_SET
long CraneOrderCurrentBase :: getUpRotateAngleSet()
{
	return upRotateAngleSet;
}
void CraneOrderCurrentBase :: setUpRotateAngleSet(long theVal)
{
	upRotateAngleSet=theVal;
}

//14 CLAMP_WIDTH_SET
long CraneOrderCurrentBase :: getClampWidthSet()
{
	return clampWidthSet;
}
void CraneOrderCurrentBase :: setClampWidthSet(long theVal)
{
	clampWidthSet=theVal;
}

//15 PLAN_DOWN_X
long CraneOrderCurrentBase :: getPlanDownX()
{
	return planDownX;
}
void CraneOrderCurrentBase :: setPlanDownX(long theVal)
{
	planDownX=theVal;
}

//16 PLAN_DOWN_Y
long CraneOrderCurrentBase :: getPlanDownY()
{
	return planDownY;
}
void CraneOrderCurrentBase :: setPlanDownY(long theVal)
{
	planDownY=theVal;
}


//17 PLAN_DOWN_Z
long CraneOrderCurrentBase :: getPlanDownZ()
{
	return planDownZ;
}
void CraneOrderCurrentBase :: setPlanDownZ(long theVal)
{
	planDownZ=theVal;
}

//18 Down_Rotate_AngleSet
long CraneOrderCurrentBase :: getDownRotateAngleSet()
{
	return downRotateAngleSet;
}
void CraneOrderCurrentBase :: setDownRotateAngleSet(long theVal)
{
	downRotateAngleSet=theVal;
}

//19 COIL_WIDTH
long CraneOrderCurrentBase :: getCoilWidth()
{
	return coilWidth;
}
void CraneOrderCurrentBase :: setCoilWidth(long theVal)
{
	coilWidth=theVal;
}

//20 COIL_WEIGHT
long CraneOrderCurrentBase :: getCoilWeight()
{
	return coilWeight;
}
void CraneOrderCurrentBase :: setCoilWeight(long theVal)
{
	coilWeight=theVal;
}

//21 COIL_OUT_DIA
long CraneOrderCurrentBase :: getCoilOutDia()
{
	return coilOutDia;
}
void CraneOrderCurrentBase :: setCoilOutDia(long theVal)
{
	coilOutDia=theVal;
}

//22 COIL_IN_DIA
long CraneOrderCurrentBase :: getCoilInDia()
{
	return coilInDia;
}
void CraneOrderCurrentBase :: setCoilInDia(long theVal)
{
	coilInDia=theVal;
}




void CraneOrderCurrentBase :: logOutValues()
{
	string functionName="CraneUACSOrderBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class CraneUACSOrderBase--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t orderNO="<<orderNO<<endl;
	//2
	log.Debug()<<"\t bayNO="<<bayNO<<endl;
	//3
	log.Debug()<<"\t matNO="<<matNO<<endl;
	//4
	log.Debug()<<"\t orderType="<<orderType<<endl;
	//5
	log.Debug()<<"\t orderPriority="<<orderPriority<<endl;
	//6
	log.Debug()<<"\t fromStockNO="<<fromStockNO<<endl;
	//7
	log.Debug()<<"\t toStockNO="<<toStockNO<<endl;
	//8
	log.Debug()<<"\t cmdStatus="<<cmdStatus<<endl;
	//9
	log.Debug()<<"\t craneNO="<<craneNO<<endl;
	//10
	log.Debug()<<"\t planUpX="<<planUpX<<endl;
	//11
	log.Debug()<<"\t planUpY="<<planUpY<<endl;
	//12
	log.Debug()<<"\t planUpZ="<<planUpZ<<endl;
	//13
	log.Debug()<<"\t upRotateAngleSet="<<upRotateAngleSet<<endl;
	//14
	log.Debug()<<"\t clampWidthSet="<<clampWidthSet<<endl;
	//15
	log.Debug()<<"\t planDownX="<<planDownX<<endl;
	//16
	log.Debug()<<"\t planDownY="<<planDownY<<endl;
	//17
	log.Debug()<<"\t planDownZ="<<planDownZ<<endl;
	//18
	log.Debug()<<"\t downRotateAngleSet="<<downRotateAngleSet<<endl;
	//19
	log.Debug()<<"\t coilWidth="<<coilWidth<<endl;
	//20
	log.Debug()<<"\t coilWeight="<<coilWeight<<endl;
	//21
	log.Debug()<<"\t coilOutDia="<<coilOutDia<<endl;
	//22
	log.Debug()<<"\t coilInDia="<<coilInDia<<endl;
	//23
	log.Debug()<<"\t floor_Up_Z="<<floor_Up_Z<<endl;
	//24
	log.Debug()<<"\t flag_Small_Coil="<<flag_Small_Coil<<endl;
	//25
	log.Debug()<<"\t floor_Down_Z="<<floor_Down_Z<<endl;



	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}

long CraneOrderCurrentBase::getFloor_Up_Z()
{
	return floor_Up_Z;
}

void CraneOrderCurrentBase::setFloor_Up_Z(long theVal)
{
	floor_Up_Z = theVal;
}

long CraneOrderCurrentBase::getFlag_Small_Coil()
{
	return flag_Small_Coil;
}

void CraneOrderCurrentBase::setFlag_Small_Coil(long theVal)
{
	flag_Small_Coil = theVal;
}

long CraneOrderCurrentBase::getFloor_Down_Z()
{
	return floor_Down_Z;
}

void CraneOrderCurrentBase::setFloor_Down_Z(long theVal)
{
	floor_Down_Z = theVal;
}


