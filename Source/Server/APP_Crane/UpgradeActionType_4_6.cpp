#include "UpgradeActionType_4_6.h"

using namespace Monitor;


UpgradeActionType_4_6 :: UpgradeActionType_4_6(void)
{

}



UpgradeActionType_4_6 :: ~UpgradeActionType_4_6(void)
{
	


}



//1 doAction
bool UpgradeActionType_4_6 :: tryUpdate(string craneNO, 
																CranePLCStatusBase cranePLCStatus,
																OrderCurrentBase craneOrderCurrent,
																CraneEvadeRequestBase  craneEvadeRequestBase)
{

	bool upgraded=false;
	string functionName="UpgradeActionType_4_6 :: tryUpdate()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{


			 //如果4-6空钩，
			 //且4-6当前WMS指令不是PA2的机组收料指令
			 //且避让指令中，发出者是4-7，且4-7当前要执行的WMS指令是去PA2收料
			 //则提升4-6避让指令为RIGHT_NOW
			 //车辆特例对4_6
			 if( craneNO=="4_6")
			{
					bool bFlagCrane = false;
					bool bFlagSender = false;

					//4-6当前的WMS指令是去PA2收料
					bFlagCrane = true;  //Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent);				

					//4-7当前WMS指令是去PA2收料
					string sender = craneEvadeRequestBase.getSender();
					OrderCurrentBase senderOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(sender);
					bFlagSender = (sender == "4_7") ;
						//&& Test_Order_Postion_Answer::isUpPos_PA2_Exit(senderOrderCurrent) && Test_Order_Postion_Answer	::isDownPos_In_Yard(senderOrderCurrent);
					
					if(craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
					{
							if (cranePLCStatus.getHasCoil() == 0)
							{
								if (bFlagCrane == false && bFlagSender == true)
								{
									log.Info()<<"TYPE_AFTER_JOB ====> TYPE_RIGHT_NOW：4-7收料，4-6立即让！"<<endl;
									Adapter_UACS_CRANE_EVADE_REQUEST::UpdateActionType(craneNO, CraneEvadeRequestBase::TYPE_RIGHT_NOW);
									upgraded=true;
								}
							}
					}
			}

			return upgraded;


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

	return upgraded;
}
