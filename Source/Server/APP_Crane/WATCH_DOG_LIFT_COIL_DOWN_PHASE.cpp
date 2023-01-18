#include "WATCH_DOG_LIFT_COIL_DOWN_PHASE.h"
#include "CranePLCOrderBase.h"
#include "MsgEUCR01.h"

using namespace Monitor;



WATCH_DOG_LIFT_COIL_DOWN_PHASE::WATCH_DOG_LIFT_COIL_DOWN_PHASE()
{
	nCountPA1Lock = 0;
	tagValuePA1LockCurrent = "0";
	tagValuePA1LockLast = "0";
	craneNOSendPA1Lock = "";

	wmsAlarmCodeCurrent = 0;
	wmsAlarmCodeLast = 0;
}



//WATCH_DOG_LIFT_COIL_DOWN_PHASE::~WATCH_DOG_LIFT_COIL_DOWN_PHASE(void)
//{
//	
//
//
//}


void WATCH_DOG_LIFT_COIL_DOWN_PHASE:: watch(string craneNO  )
{
	
    bool ret=false;
	string functionName="WATCH_DOG_LIFT_COIL_DOWN_PHASE :: watch()";
	LOG log(functionName, AUTO_CATCH_PID);


	try
	{

		

		
	}
	
	catch(iDA::Exception &x)
	{
		try
		{
			CDataAccess::GetInstance()->m_DBCon.Rollback();
		}
		catch(iDA::Exception &)
		{
		}
		log.Debug()<<functionName<<"   error:"<<x.ErrMsg()<<endl;
	}
    catch (std::exception& stdex)
    {
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
    }
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}


}

