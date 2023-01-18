#include "L3PlanInfo.h"

using namespace Monitor;

//建议归堆标记
const  string L3PlanInfo::START_FLAG_G = "G";//
const  string L3PlanInfo::START_FLAG_C = "C";//

//是否需要质检
const  string L3PlanInfo::QC_FLAG_1 = "1";//
const  string L3PlanInfo::QC_FLAG_0 = "0";//

//计划类型
const  string L3PlanInfo::PLAN_TYPE_ZC = "1";//
const  string L3PlanInfo::PLAN_TYPE_XL = "2";//
const  string L3PlanInfo::PLAN_TYPE_ZC_XL = "3";//

//计划合法非法标记
const  string L3PlanInfo::PLAN_VALID_YES = "1";//
const  string L3PlanInfo::PLAN_VALID_NO = "2";//

//计划操作标记
const  string L3PlanInfo::OPERATE_FLAG_I = "I";//
const  string L3PlanInfo::OPERATE_FLAG_D = "D";//

L3PlanInfo :: L3PlanInfo(void)
{
	initValues();
}


L3PlanInfo :: ~L3PlanInfo(void)
{

}

void L3PlanInfo :: initValues()
{

	//1 workSeqNO
	workSeqNO=DF_STR_NULL;

	//2 operateFlag
	operateFlag=DF_STR_NULL;

	//3 carNO
	carNO=DF_STR_NULL;

	//4 weighAppNO
	weighAppNO =DF_STR_NULL;

	//5 weighAppTime
	weighAppTime=DB_TIME_NULL;

	//6 recCreator
	recCreator =DF_STR_NULL;

	//7 srcStockCode
	srcStockCode = DF_STR_NULL;

	//8 srcLocCode
	srcLocCode = DF_STR_NULL;

	//9 srcMatCode
	srcMatCode = DF_STR_NULL;

	//10 srcCompCode
	srcCompCode = DF_STR_NULL;

	//11 dstStockCode
	dstStockCode=DF_STR_NULL;

	//12 dstLocCode
	dstLocCode =DF_STR_NULL;

	//13 dstMatCode
	dstMatCode = DF_STR_NULL;

	//14 dstCompCode
	dstCompCode = DF_STR_NULL;

	//15 estimateWgt
	estimateWgt = DF_INT_NULL;

	//16 startFlag
	startFlag = DF_STR_NULL;

	//17 qcFlag
	qcFlag = DF_STR_NULL;

	//18 planType
	planType = DF_STR_NULL;

	//19 planStatus
	planStatus = DF_STR_NULL;

	//20 planValid
	planValid = DF_STR_NULL;

}


//1 
string L3PlanInfo :: getWorkSeqNO()
{
	return workSeqNO;
}
void L3PlanInfo :: setWorkSeqNO(string theVal)
{
	workSeqNO=theVal;
}

//2 
string L3PlanInfo :: getOperateFlag()
{
	return operateFlag;
}
void L3PlanInfo :: setOperateFlag(string theVal)
{
	operateFlag=theVal;
}

//3 
string L3PlanInfo :: getCarNO()
{
	return carNO;
}
void L3PlanInfo :: setCarNO(string theVal)
{
	carNO=theVal;
}

//4 
string L3PlanInfo :: getWeighAppNO()
{
	return weighAppNO;
}
void L3PlanInfo :: setWeighAppNO(string theVal)
{
	weighAppNO=theVal;
}

//5 
iDA::DateTime L3PlanInfo :: getWeighAppTime()
{
	return weighAppTime;
}
void L3PlanInfo :: setWeighAppTime(iDA::DateTime theVal)
{
	weighAppTime=theVal;
}

//6 
string L3PlanInfo :: getRecCreator()
{
	return recCreator;
}
void L3PlanInfo :: setRecCreator(string theVal)
{
	recCreator=theVal;
}

//7 
string L3PlanInfo :: getSrcStockCode()
{
	return srcStockCode;
}
void L3PlanInfo :: setSrcStockCode(string theVal)
{
	srcStockCode = theVal;
}


//8 
string L3PlanInfo :: getSrcLocCode()
{
	return srcLocCode;
}
void L3PlanInfo :: setSrcLocCode(string theVal)
{
	srcLocCode = theVal;
}

//9 
string L3PlanInfo :: getSrcMatCode()
{
	return srcMatCode;
}
void L3PlanInfo :: setSrcMatCode(string theVal)
{
	srcMatCode = theVal;
}

//10 
string L3PlanInfo :: getSrcCompCode()
{
	return srcCompCode;
}
void L3PlanInfo :: setSrcCompCode(string theVal)
{
	srcCompCode = theVal;
}

//11 
string L3PlanInfo :: getDstStockCode()
{
	return dstStockCode;
}
void L3PlanInfo :: setDstStockCode(string theVal)
{
	dstStockCode = theVal;
}

//12 
string L3PlanInfo :: getDstLocCode()
{
	return dstLocCode;
}
void L3PlanInfo :: setDstLocCode(string theVal)
{
	dstLocCode = theVal;
}

//13
string L3PlanInfo :: getDstMatCode()
{
	return dstMatCode;
}
void L3PlanInfo :: setDstMatCode(string theVal)
{
	dstMatCode = theVal;
}

//14
string L3PlanInfo :: getDstCompCode()
{
	return dstCompCode;
}
void L3PlanInfo :: setDstCompCode(string theVal)
{
	dstCompCode = theVal;
}

//15
long L3PlanInfo :: getEstimateWgt()
{
	return estimateWgt;
}
void L3PlanInfo :: setEstimateWgt(long theVal)
{
	estimateWgt = theVal;
}

//16
string L3PlanInfo :: getStartFlag()
{
	return startFlag;
}
void L3PlanInfo :: setStartFlag(string theVal)
{
	startFlag = theVal;
}

//17
string L3PlanInfo :: getQCFlag()
{
	return qcFlag;
}
void L3PlanInfo :: setQCFlag(string theVal)
{
	qcFlag = theVal;
}

//18
string L3PlanInfo :: getPlanType()
{
	return planType;
}
void L3PlanInfo :: setPlanType(string theVal)
{
	planType = theVal;
}

//19
string L3PlanInfo :: getPlanStatus()
{
	return planStatus;
}
void L3PlanInfo :: setPlanStatus(string theVal)
{
	planStatus = theVal;
}

//20
string L3PlanInfo :: getPlanValid()
{
	return planValid;
}
void L3PlanInfo :: setPlanValid(string theVal)
{
	planValid = theVal;
}



void L3PlanInfo :: logOutValues()
{
	string functionName="L3PlanInfo :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class L3PlanInfo--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t workSeqNO="<<workSeqNO<<endl;
	//2
	log.Debug()<<"\t operateFlag="<<operateFlag<<endl;
	//3
	log.Debug()<<"\t carNO="<<carNO<<endl;
	//4
	log.Debug()<<"\t weighAppNO="<<weighAppNO<<endl;
	//5
	log.Debug()<<"\t weighAppTime="<<weighAppTime<<endl;
	//6
	log.Debug()<<"\t recCreator="<<recCreator<<endl;
	//7
	log.Debug()<<"\t srcStockCode="<<srcStockCode<<endl;
	//8
	log.Debug()<<"\t srcLocCode="<<srcLocCode<<endl;
	//9
	log.Debug()<<"\t srcMatCode="<<srcMatCode<<endl;
	//10
	log.Debug()<<"\t srcCompCode="<<srcCompCode<<endl;
	//11
	log.Debug()<<"\t dstStockCode="<<dstStockCode<<endl;
	//12
	log.Debug()<<"\t dstLocCode="<<dstLocCode<<endl;
	//13
	log.Debug()<<"\t dstMatCode="<<dstMatCode<<endl;
	//14
	log.Debug()<<"\t dstCompCode="<<dstCompCode<<endl;
	//15
	log.Debug()<<"\t estimateWgt="<<estimateWgt<<endl;
	//16
	log.Debug()<<"\t startFlag="<<startFlag<<endl;
	//17
	log.Debug()<<"\t qcFlag="<<qcFlag<<endl;
	//18
	log.Debug()<<"\t planType="<<planType<<endl;
	//19
	log.Debug()<<"\t planStatus="<<planStatus<<endl;
	//20
	log.Debug()<<"\t planValid="<<planValid<<endl;


	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}

