#include "ACTION_FINISH_EVADE.h"

using namespace Monitor;



ACTION_FINISH_Evade :: ACTION_FINISH_Evade(void)
{

}



ACTION_FINISH_Evade :: ~ACTION_FINISH_Evade(void)
{
	


}



//1 doAction
bool ACTION_FINISH_Evade :: doAction(string craneNO, 
																string bayNO,
																CraneEvadeRequestBase craneEvadeRequest, 
																CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_FINISH_Evade :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

			log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
			log.Debug()<<" ---------------------------------------------- action finish evade ----------------------------------------"<<endl;
			log.Debug()<<" --------------------------------------------------------------------------------------------------------------"<<endl;

			//Adapter_UACS_CRANE_EVADE_REQUEST::Init(craneNO);

			OrderCurrentBase craneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);
			//如果是放水指令  此时清空指令表
			if ( craneOrderCurrent.getOrderType() == "X2" )
			{
					Adapter_UACS_CRANE_ORDER_CURRENT::initialise(craneNO);
					Adapter_UACS_CRANE_ORDER_CURRENT::update_CMDStatus(craneNO,OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY);
			}

			ret=true;
			return true;

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

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
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}
