#include "EvadeRequestSenderException.h"

using namespace Monitor;


EvadeRequestSenderException :: EvadeRequestSenderException(void)
{

}



EvadeRequestSenderException :: ~EvadeRequestSenderException(void)
{
	


}



//1 doAction
bool EvadeRequestSenderException :: satifyException(string craneNO, 
																									string neighborCraneNO,
																									string  movingDirection)
{
	//false : 没有特例
	//true：有特例
    bool bStifyException=false;

	string functionName="EvadeRequestSenderException :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{		
		if(craneNO=="4_6")
		{
			//对方4_7车
			if(neighborCraneNO=="4_7")
			{
				//4_6移动向减小方向，且空钩 ，即向着4-7的方向移动
				if(movingDirection==MOVING_DIR::DIR_X_DES)
				{
					OrderCurrentBase craneOrderCurrent_Neightbor;
					craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
					//4-7在PA2收料
					if( 1/*Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent_Neightbor)*/ )
					{
						if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
						{
							log.Info()<<"对方车 4-7准备PA2收料，且处于上半关！我方车4-6靠近！此种情况不发送避让请求！"<<endl;
							bStifyException = true;
							return bStifyException;
						}
					}
				}
			}
		}

		//***************特例2：4-6在PA2收料，4-6要靠近4-7，且4-7目前处于上半关时*********************
		//4-7车
		if(craneNO=="4_7")
		{
			//对方4_6车
			if(neighborCraneNO=="4_6")
			{
				//4_7移动向增大方向 ，即向着4-6的方向移动
				if(movingDirection==MOVING_DIR::DIR_X_INC)
				{
							OrderCurrentBase craneOrderCurrent_Neightbor;
							craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
							//4-6在PA2收料
							//if( Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent_Neightbor) )
							if (1)
							{
								if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
								{
									log.Info()<<"对方车 4-6准备PA2收料，且处于上半关！我方车4-7靠近！此种情况不发送避让请求！"<<endl;
									bStifyException = true;
									return bStifyException;
								}
							}
				}
			}
		}

		//***************特例3：4-6给C715 176上料，此时4-5不发送避让请求**************************************************
		//4-5车
		if(craneNO=="4_5")
		{
			//对方4_6车
			if(neighborCraneNO=="4_6")
			{
				//4_5移动向减小方向 ，即向着4-6的方向移动
				if(movingDirection==MOVING_DIR::DIR_X_DES)
				{
							OrderCurrentBase craneOrderCurrent_Neightbor;
							craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
							//4-6给C175  176 上料
							/*if(Test_Order_Postion_Answer::isUpPos_In_Yard(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_C175_Entry(craneOrderCurrent_Neightbor) || 
								Test_Order_Postion_Answer::isUpPos_In_Yard(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_C176_Entry(craneOrderCurrent_Neightbor))*/
							if (1)
							{
								if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
								{
									log.Info()<<"对方车 4-6准备为C175或C176上料，且处于上半关！我方车4-5靠近！此种情况不发送避让请求！"<<endl;
									bStifyException = true;
									return bStifyException;
								}
							}
				}
			}
		}


		if(craneNO=="4_6")
		{
			//对方4_7车
			if(neighborCraneNO=="4_7")
			{
				//4_6移动向减小方向 ，即向着4-7的方向移动
				if(movingDirection==MOVING_DIR::DIR_X_DES)
				{
					OrderCurrentBase craneOrderCurrent_Neightbor;
					craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
					//4-7在PA2收料
					//if(Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent_Neightbor) )
					if (1)
					{
						if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
						{
							log.Info()<<"对方车 4-7准备PA2收料，且处于上半关！我方车4-6靠近！此种情况不发送避让请求！"<<endl;
							bStifyException = true;
							return bStifyException;
						}
					}
				}
			}
		}
		
		log.Info()<<"无发送请求特例！"<<endl;
		return bStifyException;



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

	return bStifyException;
}
