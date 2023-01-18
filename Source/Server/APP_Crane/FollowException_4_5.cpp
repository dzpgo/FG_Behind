#include "FollowException_4_5.h"

using namespace Monitor;


FollowException_4_5 :: FollowException_4_5(void)
{
}



FollowException_4_5 :: ~FollowException_4_5(void)
{
}



//1 doAction
bool FollowException_4_5 :: satifyException(string craneNO, 
																				long targetX, 
																			   CranePLCStatusBase cranePLCStatus,
																			   OrderCurrentBase craneOrderCurrent, 
																			   string neighborCraneNO, 
																			   CranePLCStatusBase neighborCranePLCStatus)
{
	bool stifyException=false;

	string functionName="FollowException_4_5 :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//����������4_5
		//�����4-5��PA1�չ�ȥ���ϣ��򷵻�true
		//�ֱ���PA1��4�����ϰ�����X����
		bool bFlag = (targetX == 375628 || targetX == 372538 || targetX == 369540 || targetX == 366680);
		if( craneNO=="4_5")
		{
			OrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);	
			//����4-5�г� ��ҪȥPA1���� �ҵ�Ŀ��λ����PA1�����ϰ��� �ҿչ� �Ҵ����ϰ��
			if(craneOrderCurrent.getFromStockNO().find("PA01PR1A") != string::npos && 
				bFlag == true && 
				cranePLCStatus.getHasCoil() == 0 &&
				craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && 

				//�ڳ���4-4     �����ϰ��   ��4-4��ǰҪȥ��Xλ�� ���� ��ָ���е�λ��
				neighborCraneNO == "4_4" && 
				//Test_Order_Postion_Answer::isUpPos_PA1_Exit(neighborCraneOrderCurrent) == false && 
				neighborCraneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && 
				neighborCranePLCStatus.getPlanUpX() != DB_INT_NULL && 
				neighborCranePLCStatus.getPlanUpX() != neighborCraneOrderCurrent.getPlanUpX() ) 
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
