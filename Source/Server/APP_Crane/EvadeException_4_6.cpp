#include "EvadeException_4_6.h"

using namespace Monitor;


EvadeException_4_6 :: EvadeException_4_6(void)
{

}



EvadeException_4_6 :: ~EvadeException_4_6(void)
{
	


}



//1 doAction
bool EvadeException_4_6 :: satifyException(string craneNO, 
																CranePLCStatusBase cranePLCStatus,
																OrderCurrentBase craneOrderCurrent,
																CraneEvadeRequestBase  craneEvadeRequestBase)
{
    bool stifyException=false;

	string functionName="EvadeException_4_6 :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		
			 //����������4-6
			//���4-6�ع�����ʱ��Xλ���Ǵ�С��A1_X_MIN��λ�ó�����A1_X_MIN������ô�����ã���4-6�ѵ�ǰָ������
			 if( craneNO=="4_6")
			 {
							/*map<string, long>		mapAreaXMinMax = SafetyArea_Bay::getInstance()->getMapAreaXMinMax();
							if(craneOrderCurrent.getCMDStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS && 
								cranePLCStatus.getHasCoil() == 1 && 
								craneEvadeRequestBase.getEvadeX() > mapAreaXMinMax[C2A_1_SPECIAL_POINT::A1_X_MIN]  && 
								cranePLCStatus.getXAct() < mapAreaXMinMax[C2A_1_SPECIAL_POINT::A1_X_MIN] )
							{
									stifyException = true;
							}*/
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
