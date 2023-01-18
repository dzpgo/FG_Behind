#include "CranePLCOrderBase.h"

using namespace Monitor;


//--------------------------------------------------下达PLC系统的初始值设定----------------------------------------------------------------
//PLC开关量初始值
const long CranePLCOrderBase::PLC_X_NULL=0;
//PLC模拟量初始值
const long CranePLCOrderBase::PLC_INT_NULL=999999;

//---------------------------------------------------------------------------------------------------------------------------------------------------
//1 CRANE_NO
const string CranePLCOrderBase::ADRESS_CRANE_NO_SET="CRANE_NO_SET";
//2 SHORT_CMD
const string CranePLCOrderBase::ADRESS_SHORT_CMD_SET="SHORT_CMD_SET";
 //3 ORDER_Id
const string CranePLCOrderBase::ADRESS_ORDER_Id_SET="ORDER_Id_SET";
 //4 MAT_TYPE
const string CranePLCOrderBase::ADRESS_MAT_TYPE_SET="MAT_TYPE_SET";
 //5 MAT_YARD
const string CranePLCOrderBase::ADRESS_MAT_YARD_SET="MAT_YARD_SET";
 //6 MAT_WEIGHT
const string CranePLCOrderBase::ADRESS_MAT_WEIGHT_SET="MAT_WEIGHT_SET";
 //7 PLAN_UP_X
const string CranePLCOrderBase::ADRESS_PLAN_UP_X_SET="PLAN_UP_X_SET";
 //8 PLAN_UP_Y
const string CranePLCOrderBase::ADRESS_PLAN_UP_Y_SET="PLAN_UP_Y_SET";
 //9 PLAN_UP_Z
const string CranePLCOrderBase::ADRESS_PLAN_UP_Z_SET="PLAN_UP_Z_SET";
 //10 PLAN_DOWN_X
const string CranePLCOrderBase::ADRESS_PLAN_DOWN_X_SET="PLAN_DOWN_X_SET";
 //11 PLAN_DOWN_Y
const string CranePLCOrderBase::ADRESS_PLAN_DOWN_Y_SET="PLAN_DOWN_Y_SET";
 //12 PLAN_DOWN_Z
const string CranePLCOrderBase::ADRESS_PLAN_DOWN_Z_SET="PLAN_DOWN_Z_SET";
 //13 SPACE
const string CranePLCOrderBase::ADRESS_SPACE_SET="SPACE_SET";
 //14 CRC
const string CranePLCOrderBase::ADRESS_CRC_SET="CRC_SET";


 //99 DownLoadOrder
const string CranePLCOrderBase::ADRESS_DOWN_LOAD_ORDER="DOWN_LOAD_ORDER_SET";

CranePLCOrderBase :: CranePLCOrderBase(void)
{
	initValues();
}

CranePLCOrderBase :: ~CranePLCOrderBase(void)
{	
}


void CranePLCOrderBase :: initValues()
{
	//1 CRANE_NO
	craneNO=DB_STR_NULL;

	//2 ShortCmd
	shortCmd = CranePLCOrderBase::PLC_INT_NULL;

	//3 ORDER_Id
	orderID=CranePLCOrderBase::PLC_INT_NULL;

	//4 MAT_TYPE
	matType=CranePLCOrderBase::PLC_INT_NULL;
	
	//5 MAT_YARD
	matYard=DB_STR_NULL;

	//6 MAT_WEIGHT
	matWeight=CranePLCOrderBase::PLC_INT_NULL;

	//7 PLAN_UP_X
	planUpX=CranePLCOrderBase::PLC_INT_NULL;

	//8 PLAN_UP_Y
	planUpY=CranePLCOrderBase::PLC_INT_NULL;

	//9 PLAN_UP_Z
	planUpZ=CranePLCOrderBase::PLC_INT_NULL;

	////8 UP_ROTATE_ANGLE_SET
	//upRotateAngleSet = CranePLCOrderBase::PLC_INT_NULL;

	//10 PLAN_DOWN_X
	planDownX=CranePLCOrderBase::PLC_INT_NULL;

	//11 PLAN_DOWN_Y
	planDownY=CranePLCOrderBase::PLC_INT_NULL;

	//12 PLAN_DOWN_Z
	planDownZ=CranePLCOrderBase::PLC_INT_NULL;

	////12 downRotateAngleSet
	//downRotateAngleSet = CranePLCOrderBase::PLC_INT_NULL;

	//13 预留
	space = CranePLCOrderBase::PLC_INT_NULL;

	//14 校验值
	crc = CranePLCOrderBase::PLC_INT_NULL;


	////14 中间点map
	//map<string, long> mapPoint;
	//mapPoint.insert( make_pair<string, long>("X", CranePLCOrderBase::PLC_INT_NULL));
	//mapPoint.insert( make_pair<string, long>("Y", CranePLCOrderBase::PLC_INT_NULL));
	//for (int i=1; i <=20; i++)
	//{
	//	mapMidPointList.insert( make_pair<long, map<string, long> >(i, mapPoint)); 
	//}
}

//1 craneNO
string CranePLCOrderBase :: getCraneNO()
{
	return craneNO;
}
void CranePLCOrderBase :: setCraneNO(string theVal)
{
	craneNO=theVal;
}

//2 SHORT_CMD
long CranePLCOrderBase :: getShortCmd()
{
	return shortCmd;
}
void CranePLCOrderBase :: setShortCmd(long theVal)
{
	shortCmd=theVal;
}

//3 orderID
long CranePLCOrderBase :: getOrderID()
{
	return orderID;
}
void CranePLCOrderBase :: setOrderID(long theVal)
{
	orderID=theVal;
}


//4 matType
long CranePLCOrderBase :: getMatType()
{
	return matType;
}
void CranePLCOrderBase :: setMatType(long theVal)
{
	matType=theVal;
}
//5 matYard
string CranePLCOrderBase :: getMatYard()
{
	return matYard;
}
void CranePLCOrderBase :: setMatYard(string theVal)
{
	matYard=theVal;
}
//6 matWeight
long CranePLCOrderBase :: getMatWeight()
{
	return matWeight;
}
void CranePLCOrderBase :: setMatWeight(long theVal)
{
	matWeight=theVal;
}



//7 planUpX
long CranePLCOrderBase :: getPlanUpX()
{
	return planUpX;
}
void CranePLCOrderBase :: setPlanUpX(long theVal)
{
	planUpX=theVal;
}

//8 planUpY
long CranePLCOrderBase :: getPlanUpY()
{
	return planUpY;
}
void CranePLCOrderBase :: setPlanUpY(long theVal)
{
	planUpY=theVal;
}

//9 planUpZ
long CranePLCOrderBase :: getPlanUpZ()
{
	return planUpZ;
}
void CranePLCOrderBase :: setPlanUpZ(long theVal)
{
	planUpZ=theVal;
}

////8 upRotateAngleSet
//long CranePLCOrderBase :: getUpRotateAngleSet()
//{
//	return upRotateAngleSet;
//}
//void CranePLCOrderBase :: setUpRptateAngleSet(long theVal)
//{
//	upRotateAngleSet=theVal;
//}

//10 planDownX
long CranePLCOrderBase :: getPlanDownX()
{
	return planDownX;
}
void CranePLCOrderBase :: setPlanDownX(long theVal)
{
	planDownX=theVal;
}

//11 planDownY
long CranePLCOrderBase :: getPlanDownY()
{
	return planDownY;
}
void CranePLCOrderBase :: setPlanDownY(long theVal)
{
	planDownY=theVal;
}

//12 planDownZ
long CranePLCOrderBase :: getPlanDownZ()
{
	return planDownZ;
}
void CranePLCOrderBase :: setPlanDownZ(long theVal)
{
	planDownZ=theVal;
}


//13 space
long CranePLCOrderBase :: getSpace()
{
	return space;
}
void CranePLCOrderBase :: setSpace(long theVal)
{
	space=theVal;
}

//14 crc
long CranePLCOrderBase :: getCrc()
{
	return crc;
}
void CranePLCOrderBase :: setCrc(long theVal)
{
	crc=theVal;
}
////12 downRotateAngleSet
//long CranePLCOrderBase :: getDownRotateAngleSet()
//{
//	return downRotateAngleSet;
//}
//void CranePLCOrderBase :: setDownRotateAngleSet(long theVal)
//{
//	downRotateAngleSet=theVal;
//}


//14 中间点list
map<long, map<string, long> > CranePLCOrderBase :: getMapMidPointList()
{
	return mapMidPointList;
}
void CranePLCOrderBase :: setMapMidPointList(map<long, map<string, long> > theVal)
{
	mapMidPointList=theVal;
}


void CranePLCOrderBase :: logOutValues()
{
	string functionName="CranePLCOrderBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class CranePLCOrderBase--------------------------------------"<<endl;
	//1
	log.Debug()<<"\t craneNO="<<craneNO;
	//2
	log.Debug()<<"\t shortCMD="<<shortCmd<<endl;
	//3
	log.Debug()<<"\t orderID="<<orderID;
	//4
	log.Debug()<<"\t matType="<<matType;
	//5
	log.Debug()<<"\t matType="<<matYard;
	//6
	log.Debug()<<"\t matWeight="<<matWeight;
	//7
	log.Debug()<<"\t planUpX="<<planUpX;
	//8
	log.Debug()<<"\t planUpY="<<planUpY;
	//9
	log.Debug()<<"\t planUpZ="<<planUpZ<<endl;
	////8
	//log.Debug()<<"\t  upRotateAngleSet="<<upRotateAngleSet;
	//10
	log.Debug()<<"\t planDownX="<<planDownX;
	//11
	log.Debug()<<"\t planDownY="<<planDownY;
	//12
	log.Debug()<<"\t planDownZ="<<planDownZ<<endl;
	//13
	log.Debug()<<"\t space="<<space<<endl;
	//14
	log.Debug()<<"\t crc="<<crc<<endl;
	////12
	//log.Debug()<<"\t downRotateAngleSet="<<downRotateAngleSet;

	//14 
	//log.Debug()<<"\t print mapMidPointList :  "<<endl;
	//map<long, map<string, long> >::iterator itor;
	//for (itor = mapMidPointList.begin(); itor != mapMidPointList.end(); itor ++)
	//{
	//	long pointNO = itor->first;
	//	map<string, long> mapPoint = itor->second;
	//	log.Debug()<<"\t mapMidPointList ="<<pointNO<<" : X="<<mapPoint["X"]<<" , Y="<<mapPoint["Y"]<<endl;
	//}

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

	
}