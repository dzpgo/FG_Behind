#include "EvadeException_Normal_I_Will_Leave.h"

using namespace Monitor;


EvadeException_Normal_I_Will_Leave :: EvadeException_Normal_I_Will_Leave(void)
{

}



EvadeException_Normal_I_Will_Leave :: ~EvadeException_Normal_I_Will_Leave(void)
{
	


}



//1 doAction
bool EvadeException_Normal_I_Will_Leave :: satifyException(string craneNO, 
																CranePLCStatusBase cranePLCStatus,
																OrderCurrentBase craneOrderCurrent,
																CraneEvadeRequestBase  craneEvadeRequestBase)
{
    bool stifyException=false;

	string functionName="EvadeException_Normal_I_Will_Leave :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		
		bool hasExcutingWMSOrder=false;

		if(craneOrderCurrent.getCmdStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
		{
			hasExcutingWMSOrder=true;
		}
		if(craneOrderCurrent.getCmdStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS)
		{
			hasExcutingWMSOrder=true;
		}
	 
		//无WMS指令，直接返回
		if(hasExcutingWMSOrder==false)
		{
			 return stifyException;
		}

		long myTargetX=cranePLCStatus.getXAct();
		if(cranePLCStatus.getHasCoil()==0)
		{
			myTargetX=cranePLCStatus.getPlanUpX();
		}
		else if(cranePLCStatus.getHasCoil()==1)
		{
			myTargetX=cranePLCStatus.getPlanDownX();
		}
		string myDirection=MOVING_DIR::getDirection(craneNO, cranePLCStatus.getXAct(),  myTargetX);

		//方向不一致，直接返回
		if(myDirection!= craneEvadeRequestBase.getEvadeDirection())
		{
			 return stifyException;
		}

		if(myDirection==MOVING_DIR::DIR_X_INC)
		{
			if(myTargetX>craneEvadeRequestBase.getEvadeX())
			{
				stifyException=true;
				return stifyException;
			}
		}
		else if(myDirection==MOVING_DIR::DIR_X_DES)
		{
			if(myTargetX<craneEvadeRequestBase.getEvadeX())
			{
				stifyException=true;
				return stifyException;
			}
		}
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
	return stifyException;
}
