#include "EvadeException_4_5.h"

using namespace Monitor;


EvadeException_4_5 :: EvadeException_4_5(void)
{

}



EvadeException_4_5 :: ~EvadeException_4_5(void)
{
	


}



//1 doAction
bool EvadeException_4_5 :: satifyException(string craneNO, 
																CranePLCStatusBase cranePLCStatus,
																OrderCurrentBase craneOrderCurrent,
																CraneEvadeRequestBase  craneEvadeRequestBase)
{
    bool stifyException=false;

	string functionName="EvadeException_4_5 :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
			 //����������4_5
			 //����ҵ�ǰָ����PA1����
			//���ǿչ���˵����ȥPA1ȡ������WMSָ��
			 if( craneNO=="4_5")
			 {
				 if( 
					 cranePLCStatus.getHasCoil() == 0 && 
					 craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)  
					{
						log.Info()<<"4-5 �չ���ȥPA1���ϣ���ִ��WMSָ�"<<endl;
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
