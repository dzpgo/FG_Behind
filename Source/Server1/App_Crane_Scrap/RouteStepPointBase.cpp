#include "RouteStepPointBase.h"

using namespace Monitor;



RouteStepPointBase :: RouteStepPointBase(void)
{

	initValues();
}



RouteStepPointBase :: ~RouteStepPointBase(void)
{
	


}

void RouteStepPointBase :: initValues()
{
	
	//1 x
	x=DB_INT_NULL;

	//2 y
	y=DB_INT_NULL;

	//3 flagReachFinalTarget
	flagReachFinalTarget=false;


}



//1 x
long RouteStepPointBase :: getX()
{
	return x;
}
void RouteStepPointBase :: setX(long theVal)
{
	x=theVal;
}

//2 y
long RouteStepPointBase :: getY()
{
	return y;
}
void RouteStepPointBase :: setY(long theVal)
{
	y=theVal;
}

//3 flagReachFinalTarget
bool RouteStepPointBase :: getFlagReachFinalTarget()
{
	return flagReachFinalTarget;
}
void RouteStepPointBase :: setFlagReachFinalTarget(bool theVal)
{
	flagReachFinalTarget=theVal;
}



void RouteStepPointBase :: logOutValues()
{
	string functionName="RouteStepPointBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"------------------------------the values in the class RouteStepPointBase--------------------------------------"<<endl;

	//1
	log.Debug()<<"\t x="<<x;
	//2
	log.Debug()<<"\t y="<<y;
	//3
	log.Debug()<<"\t flagReachFinalTarget="<<flagReachFinalTarget<<endl;

	

	log.Debug()<<"----------------------------------------------------------------------------------------------------------------------"<<endl;

	
}
