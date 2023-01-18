#include "EAFPlanInfoDetail.h"

using namespace Monitor;


//层合法非法标记
const  string EAFPlanInfoDetail::LAY_VALID_YES = "1";//
const  string EAFPlanInfoDetail::LAY_VALID_NO = "2";//

//状态标记
const  string EAFPlanInfoDetail::STATUS_NOT_START = "1";//
const  string EAFPlanInfoDetail::STATUS_START = "2";//
const  string EAFPlanInfoDetail::STATUS_FINISH = "3";//

EAFPlanInfoDetail :: EAFPlanInfoDetail(void)
{
	initValues();
}


EAFPlanInfoDetail :: ~EAFPlanInfoDetail(void)
{

}

void EAFPlanInfoDetail :: initValues()
{

	//0 operID
	operID=DF_STR_NULL;

	//1 detailID
	detailID=DF_INT_NULL;

	//2 pono
	pono=DF_STR_NULL;

	//3 bSeqNum
	bSeqNum=DF_STR_NULL;

	//4 pitNum
	pitNum =DF_STR_NULL;

	//5 layNO
	layNO=DF_INT_NULL;

	//6 scrID
	scrID =DF_STR_NULL;

	//7 scrWeight
	scrWeight = DF_INT_NULL;

	//8 craneWeight
	craneWeight = DF_INT_NULL;

	//9 sclWeight
	sclWeight = DF_INT_NULL;

	//10 carNO
	carNO = DF_STR_NULL;

	//11 gridNO
	gridNO=DF_STR_NULL;

	//12 matCode
	matCode =DF_STR_NULL;

	//13 compCode
	compCode = DF_STR_NULL;

	//14 layValid
	layValid = DF_STR_NULL;

	//15 status
	status = DF_STR_NULL;
	

}

//0
string EAFPlanInfoDetail :: getOperID()
{
	return operID;
}
void EAFPlanInfoDetail :: setOperID(string theVal)
{
	operID=theVal;
}

//1 
long EAFPlanInfoDetail :: getDetailID()
{
	return detailID;
}
void EAFPlanInfoDetail :: setDetailID(long theVal)
{
	detailID=theVal;
}

//2 
string EAFPlanInfoDetail :: getPono()
{
	return pono;
}
void EAFPlanInfoDetail :: setPono(string theVal)
{
	pono=theVal;
}

//3 
string EAFPlanInfoDetail :: getBSeqNum()
{
	return bSeqNum;
}
void EAFPlanInfoDetail :: setBSeqNum(string theVal)
{
	bSeqNum=theVal;
}

//4 
string EAFPlanInfoDetail :: getPitNum()
{
	return pitNum;
}
void EAFPlanInfoDetail :: setPitNum(string theVal)
{
	pitNum=theVal;
}

//5 
long EAFPlanInfoDetail :: getLayNO()
{
	return layNO;
}
void EAFPlanInfoDetail :: setLayNO(long theVal)
{
	layNO=theVal;
}

//6 
string EAFPlanInfoDetail :: getScrID()
{
	return scrID;
}
void EAFPlanInfoDetail :: setScrID(string theVal)
{
	scrID=theVal;
}

//7 
long EAFPlanInfoDetail :: getScrWeight()
{
	return scrWeight;
}
void EAFPlanInfoDetail :: setScrWeight(long theVal)
{
	scrWeight = theVal;
}


//8 
long EAFPlanInfoDetail :: getCraneWeight()
{
	return craneWeight;
}
void EAFPlanInfoDetail :: setCraneWeight(long theVal)
{
	craneWeight = theVal;
}

//9 
long EAFPlanInfoDetail :: getSclWeight()
{
	return sclWeight;
}
void EAFPlanInfoDetail :: setSclWeight(long theVal)
{
	sclWeight = theVal;
}

//10 
string EAFPlanInfoDetail :: getCarNO()
{
	return carNO;
}
void EAFPlanInfoDetail :: setCarNO(string theVal)
{
	carNO = theVal;
}

//11 
string EAFPlanInfoDetail :: getGridNO()
{
	return gridNO;
}
void EAFPlanInfoDetail :: setGridNO(string theVal)
{
	gridNO = theVal;
}

//12 
string EAFPlanInfoDetail :: getMatCode()
{
	return matCode;
}
void EAFPlanInfoDetail :: setMatCode(string theVal)
{
	matCode = theVal;
}

//13
string EAFPlanInfoDetail :: getCompCode()
{
	return compCode;
}
void EAFPlanInfoDetail :: setCompCode(string theVal)
{
	compCode = theVal;
}

//14
string EAFPlanInfoDetail :: getLayValid()
{
	return layValid;
}
void EAFPlanInfoDetail :: setLayValid(string theVal)
{
	layValid = theVal;
}

//15
string EAFPlanInfoDetail :: getStatus()
{
	return status;
}
void EAFPlanInfoDetail :: setStatus(string theVal)
{
	status = theVal;
}





void EAFPlanInfoDetail :: logOutValues()
{
	string functionName="EAFPlanInfoDetail :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class EAFPlanInfoDetail--------------------------------------"<<endl;

	//0
	log.Debug()<<"\t operID="<<operID<<endl;
	//1
	log.Debug()<<"\t detailID="<<detailID<<endl;
	//2
	log.Debug()<<"\t pono="<<pono<<endl;
	//3
	log.Debug()<<"\t bSeqNum="<<bSeqNum<<endl;
	//4
	log.Debug()<<"\t pitNum="<<pitNum<<endl;
	//5
	log.Debug()<<"\t layNO="<<layNO<<endl;
	//6
	log.Debug()<<"\t scrID="<<scrID<<endl;
	//7
	log.Debug()<<"\t scrWeight="<<scrWeight<<endl;
	//8
	log.Debug()<<"\t craneWeight="<<craneWeight<<endl;
	//9
	log.Debug()<<"\t sclWeight="<<sclWeight<<endl;
	//10
	log.Debug()<<"\t carNO="<<carNO<<endl;
	//11
	log.Debug()<<"\t gridNO="<<gridNO<<endl;
	//12
	log.Debug()<<"\t matCode="<<matCode<<endl;
	//13
	log.Debug()<<"\t compCode="<<compCode<<endl;
	//14
	log.Debug()<<"\t layValid="<<layValid<<endl;
	//15
	log.Debug()<<"\t status="<<status<<endl;


	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}

