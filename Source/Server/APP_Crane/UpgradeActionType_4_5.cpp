#include "UpgradeActionType_4_5.h"

using namespace Monitor;


UpgradeActionType_4_5 :: UpgradeActionType_4_5(void)
{

}



UpgradeActionType_4_5 :: ~UpgradeActionType_4_5(void)
{



}



//1 doAction
bool UpgradeActionType_4_5 :: tryUpdate(string craneNO, 
										CranePLCStatusBase cranePLCStatus,
										OrderCurrentBase craneOrderCurrent,
										CraneEvadeRequestBase  craneEvadeRequestBase)
{

	bool upgraded=false;
	string functionName="UpgradeActionType_4_5 :: tryUpdate()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{


		//如果本方行车是4-5
		//对方行车4-6准备给C175 176上料
		//则提升4-5避让指令为RIGHT_NOW
		//车辆特例对4_5
		if( craneNO=="4_5")
		{
			bool bFlagCrane = false;
			bool bFlagSender = false;

			//4-6 是去C715  176上料
			string sender = craneEvadeRequestBase.getSender();
			OrderCurrentBase senderOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(sender);
			bFlagSender = (sender == "4_6") ;
				//&& (Test_Order_Postion_Answer::isUpPos_In_Yard(senderOrderCurrent) && Test_Order_Postion_Answer	::isDownPos_C175_Entry(senderOrderCurrent) || 
				//Test_Order_Postion_Answer::isUpPos_In_Yard(senderOrderCurrent) && Test_Order_Postion_Answer	::isDownPos_C176_Entry(senderOrderCurrent));


			if(craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
			{
				if ( bFlagSender == true )
				{
					log.Info()<<"TYPE_AFTER_JOB ====> TYPE_RIGHT_NOW：4-6给175/176上料，4-5立即让！"<<endl;
					Adapter_UACS_CRANE_EVADE_REQUEST::UpdateActionType(craneNO, CraneEvadeRequestBase::TYPE_RIGHT_NOW);
					upgraded=true;
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
