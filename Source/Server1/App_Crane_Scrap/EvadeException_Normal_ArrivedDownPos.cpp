#include "EvadeException_Normal_ArrivedDownPos.h"

using namespace Monitor;


EvadeException_Normal_ArrivedDownPos :: EvadeException_Normal_ArrivedDownPos(void)
{

}



EvadeException_Normal_ArrivedDownPos :: ~EvadeException_Normal_ArrivedDownPos(void)
{
	


}



//1 doAction
bool EvadeException_Normal_ArrivedDownPos :: satifyException(string craneNO, 
																CranePLCStatusBase cranePLCStatus,
																CraneOrderCurrentBase craneOrderCurrent,
																CraneEvadeRequestBase  craneEvadeRequestBase)
{
    bool stifyException=false;

	string functionName="EvadeException_Normal_ArrivedDownPos :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{		
			 //�ձ����ж����Ѿ��������λ��
			if( craneOrderCurrent.getCMDStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS &&  cranePLCStatus.getHasCoil()==1)
			 {
							 //�Ѿ��������λ��
							if( ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived( cranePLCStatus.getXAct(), cranePLCStatus.getYAct(),  craneOrderCurrent.getPlanDownX(),  craneOrderCurrent.getPlanDownY()) )
							{
								stifyException=true;
								return stifyException;
							}
			}			
			 return stifyException;
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


//1 doAction
bool EvadeException_Normal_ArrivedDownPos :: satifyExceptionHasCoilWhenXOK(string craneNO, 
															 CranePLCStatusBase cranePLCStatus,
															 OrderCurrentBase craneOrderCurrent,
															 CraneEvadeRequestBase  craneEvadeRequestBase)
{
	bool stifyException=false;

	string functionName="EvadeException_Normal_ArrivedDownPos :: satifyExceptionHasCoilWhenXOK()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{		
		//�ձ����ж����Ѿ��������λ��
		if( craneOrderCurrent.getCmdStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS &&  cranePLCStatus.getHasCoil()==1)
		{
			//�Ѿ��������λ��
			if( ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_X( cranePLCStatus.getXAct(),  craneOrderCurrent.getPlanDownX() )  == true )
			{
				stifyException=true;
				return stifyException;
			}
		}			
		return stifyException;
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


//1 doAction
bool EvadeException_Normal_ArrivedDownPos :: satifyExceptionHasNoCoilWhenXOK(string craneNO, 
																		   CranePLCStatusBase cranePLCStatus,
																		   OrderCurrentBase craneOrderCurrent,
																		   CraneEvadeRequestBase  craneEvadeRequestBase)
{
	bool stifyException=false;

	string functionName="EvadeException_Normal_ArrivedDownPos :: satifyExceptionHasNoCoilWhenXOK()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{		
		//�ձ����ж����Ѿ��������λ��
		if( craneOrderCurrent.getCmdStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS &&  cranePLCStatus.getHasCoil()==0)
		{
			//�Ѿ��������λ��
			if( ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_X( cranePLCStatus.getXAct(),  craneOrderCurrent.getPlanUpX() ) == true )
			{
				stifyException=true;
				return stifyException;
			}
		}			
		return stifyException;
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
