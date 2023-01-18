#pragma once 

#include "CraneEvadeRequestBase.h"


using namespace Monitor;

const long CraneEvadeRequestBase::ORDER_NO_EVADE=116;
const long CraneEvadeRequestBase::ORDER_NO_BOARDING=115;
const long CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH=101;
const long CraneEvadeRequestBase::ORDER_NO_MANU_AUTO_SWITCH_TEST=999999;

const string CraneEvadeRequestBase::STATUS_EMPTY="EMPTY";
const string CraneEvadeRequestBase::STATUS_INIT="INIT";
const string CraneEvadeRequestBase::STATUS_TO_DO="TO_DO";
const string CraneEvadeRequestBase::STATUS_EXCUTING="EXCUTING";
const string CraneEvadeRequestBase::STATUS_FINISHED="FINISHED";

const string CraneEvadeRequestBase::TYPE_RIGHT_NOW="RIGHT_NOW";
const string CraneEvadeRequestBase::TYPE_AFTER_JOB="AFTER_JOB";

CraneEvadeRequestBase:: CraneEvadeRequestBase()
{
	initValues( );
}

CraneEvadeRequestBase:: ~CraneEvadeRequestBase()
{

}

void   CraneEvadeRequestBase::initValues(  )
{


	//1.TARGET_CRANE_NO
	targetCraneNO = DB_STR_NULL;

	//2.SENDER
	sender = DB_STR_NULL;

	//3.ORIGINAL_SENDER
	originalSender = DB_STR_NULL;

	//4.EVADE_X_REQUEST
	evadeXRequest = DB_INT_NULL;

	//5.EVADE_X
	evadeX = DB_INT_NULL;

	//6.EVADE_DIRECTION
	evadeDirection = DB_STR_NULL;

	//7.EVADE_ACTION_TYPE
	evadeActionType = DB_STR_NULL;

	//8.STATUS
	status = DB_STR_NULL;

	//9.priority
	priority = DB_INT_NULL;


}


void   CraneEvadeRequestBase::logOutValues(  )
{

	string functionName = "CraneEvadeRequestBase :: logOutValues()";

	LOG log(functionName, AUTO_CATCH_PID);
	log.Debug()<<"----------------------------------------------------------------------- "<<endl;

	//1.TARGET_CRANE_NO
	log.Debug() << "targetCraneNO = " << targetCraneNO<<endl;


	//2.SENDER
	log.Debug() << "sender = " << sender<<endl;


	//3.ORIGINAL_SENDER
	log.Debug() << "originalSender = " << originalSender<<endl;


	//4.EVADE_X_REQUEST
	log.Debug() << "evadeXRequest = " << evadeXRequest<<endl;


	//5.EVADE_X
	log.Debug() << "evadeX = " << evadeX<<endl;


	//6.EVADE_DIRECTION
	log.Debug() << "evadeDirection = " << evadeDirection<<endl;


	//7.EVADE_ACTION_TYPE
	log.Debug() << "evadeActionType = " << evadeActionType<<endl;


	//8.STATUS
	log.Debug() << "status = " << status<<endl;

	//9.PRIORITY
	log.Debug() << "priority = " << priority << endl;

	log.Debug()<<"----------------------------------------------------------------------- "<<endl;

}


//1.TARGET_CRANE_NO
string   CraneEvadeRequestBase::getTargetCraneNO( )
{
	return targetCraneNO;
}

void   CraneEvadeRequestBase::setTargetCraneNO( string   theVal )
{
	targetCraneNO= theVal;
}

//2.SENDER
string   CraneEvadeRequestBase::getSender( )
{
	return sender;
}

void   CraneEvadeRequestBase::setSender( string   theVal )
{
	sender= theVal;
}

//3.ORIGINAL_SENDER
string   CraneEvadeRequestBase::getOriginalSender( )
{
	return originalSender;
}

void   CraneEvadeRequestBase::setOriginalSender( string   theVal )
{
	originalSender= theVal;
}

//4.EVADE_X_REQUEST
long   CraneEvadeRequestBase::getEvadeXRequest( )
{
	return evadeXRequest;
}

void   CraneEvadeRequestBase::setEvadeXRequest( long   theVal )
{
	evadeXRequest= theVal;
}

//5.EVADE_X
long   CraneEvadeRequestBase::getEvadeX( )
{
	return evadeX;
}

void   CraneEvadeRequestBase::setEvadeX( long   theVal )
{
	evadeX= theVal;
}

//6.EVADE_DIRECTION
string   CraneEvadeRequestBase::getEvadeDirection( )
{
	return evadeDirection;
}

void   CraneEvadeRequestBase::setEvadeDirection( string   theVal )
{
	evadeDirection= theVal;
}

//7.EVADE_ACTION_TYPE
string   CraneEvadeRequestBase::getEvadeActionType( )
{
	return evadeActionType;
}

void   CraneEvadeRequestBase::setEvadeActionType( string   theVal )
{
	evadeActionType= theVal;
}

//8.STATUS
string   CraneEvadeRequestBase::getStatus( )
{
	return status;
}

void   CraneEvadeRequestBase::setStatus( string   theVal )
{
	status= theVal;
}

//9.PRIORITY
double CraneEvadeRequestBase::getPriority()
{
	return priority;
}

void CraneEvadeRequestBase::setPriority(double theValue)
{
	priority = theValue;
}

