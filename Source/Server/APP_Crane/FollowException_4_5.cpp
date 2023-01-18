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
		//车辆特例对4_5
		//如果是4-5是PA1空钩去收料，则返回true
		//分别是PA1的4个收料鞍座的X坐标
		bool bFlag = (targetX == 375628 || targetX == 372538 || targetX == 369540 || targetX == 366680);
		if( craneNO=="4_5")
		{
			OrderCurrentBase neighborCraneOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);	
			//我是4-5行车 我要去PA1收料 我的目标位就是PA1的收料鞍座 我空钩 我处于上半关
			if(craneOrderCurrent.getFromStockNO().find("PA01PR1A") != string::npos && 
				bFlag == true && 
				cranePLCStatus.getHasCoil() == 0 &&
				craneOrderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && 

				//邻车是4-4     处于上半关   且4-4当前要去的X位置 不是 其指令中的位置
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
