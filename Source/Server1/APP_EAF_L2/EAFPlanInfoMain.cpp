#include "EAFPlanInfoMain.h"

using namespace Monitor;

//recipeType
const  string EAFPlanInfoMain::RECIPE_TYPE_ADD = "1";//
const  string EAFPlanInfoMain::RECIPE_TYPE_MODIFY = "2";//
const  string EAFPlanInfoMain::RECIPE_TYPE_DELETE = "3";//

//planSrc
const  string EAFPlanInfoMain::PLAN_SRC_NEW_EAF = "1";//
const  string EAFPlanInfoMain::PLAN_SRC_OLD_EAF = "2";//


EAFPlanInfoMain :: EAFPlanInfoMain(void)
{
	initValues();
}


EAFPlanInfoMain :: ~EAFPlanInfoMain(void)
{

}

void EAFPlanInfoMain :: initValues()
{

	//1 pono
	pono=DF_STR_NULL;

	//2 htno
	htno=DF_STR_NULL;

	//3 recipeType
	recipeType=DF_STR_NULL;

	//4 steelGrade
	steelGrade =DF_STR_NULL;

	//5 tapTime
	tapTime=DB_TIME_NULL;

	//6 planSrc
	planSrc =DF_STR_NULL;


}


//1 
string EAFPlanInfoMain :: getPono()
{
	return pono;
}
void EAFPlanInfoMain :: setPono(string theVal)
{
	pono=theVal;
}

//2 
string EAFPlanInfoMain :: getHtno()
{
	return htno;
}
void EAFPlanInfoMain :: setHtno(string theVal)
{
	htno=theVal;
}

//3 
string EAFPlanInfoMain :: getRecipeType()
{
	return recipeType;
}
void EAFPlanInfoMain :: setRecipeType(string theVal)
{
	recipeType=theVal;
}

//4 
string EAFPlanInfoMain :: getSteelGrade()
{
	return steelGrade;
}
void EAFPlanInfoMain :: setSteelGrade(string theVal)
{
	steelGrade=theVal;
}

//5 
iDA::DateTime EAFPlanInfoMain :: getTapTime()
{
	return tapTime;
}
void EAFPlanInfoMain :: setTapTime(iDA::DateTime theVal)
{
	tapTime=theVal;
}

//6 
string EAFPlanInfoMain :: getPlanSrc()
{
	return planSrc;
}
void EAFPlanInfoMain :: setPlanSrc(string theVal)
{
	planSrc=theVal;
}



void EAFPlanInfoMain :: logOutValues()
{
	string functionName="EAFPlanInfoMain :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class EAFPlanInfoMain--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t pono="<<pono<<endl;
	//2
	log.Debug()<<"\t htno="<<htno<<endl;
	//3
	log.Debug()<<"\t recipeType="<<recipeType<<endl;
	//4
	log.Debug()<<"\t steelGrade="<<steelGrade<<endl;
	//5
	log.Debug()<<"\t tapTime="<<tapTime<<endl;
	//6
	log.Debug()<<"\t planSrc="<<planSrc<<endl;


	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;


}

