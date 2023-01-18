#include "EvadeException_4_4.h"

using namespace Monitor;


EvadeException_4_4 :: EvadeException_4_4(void)
{

}



EvadeException_4_4 :: ~EvadeException_4_4(void)
{
	


}



//1 doAction
bool EvadeException_4_4 :: satifyException(string craneNO, 
																CranePLCStatusBase cranePLCStatus,
																OrderCurrentBase craneOrderCurrent,
																CraneEvadeRequestBase  craneEvadeRequestBase)
{
    bool stifyException=false;

	string functionName="EvadeException_4_4 :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		
			 //车辆特例对4_4
			 if( craneNO=="4_4")
			 {
				 //如果4-4有卷，且正在做PA1收料指令，则不做避让

				 if(craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS  && 
					cranePLCStatus.getHasCoil()==1 && 
					craneOrderCurrent.getOrderType() == "11")
					{
						stifyException = true;
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
