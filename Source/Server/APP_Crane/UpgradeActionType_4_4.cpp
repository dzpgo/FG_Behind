#include "UpgradeActionType_4_4.h"

using namespace Monitor;


UpgradeActionType_4_4 :: UpgradeActionType_4_4(void)
{

}



UpgradeActionType_4_4 :: ~UpgradeActionType_4_4(void)
{



}



//1 doAction
bool UpgradeActionType_4_4 :: tryUpdate(string craneNO, 
										CranePLCStatusBase cranePLCStatus,
										OrderCurrentBase craneOrderCurrent,
										CraneEvadeRequestBase  craneEvadeRequestBase)
{

	bool upgraded=false;
	string functionName="UpgradeActionType_4_4 :: tryUpdate()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{


		//如果我是4-4
		

		if( craneNO=="4_4")
		{
			bool bFlagSender1 = false;
			bool bFlagSender2 = false;
			bool bFlagSender3 = false;
			bool bFlagSender4 = false;
			bool bFlagSender = false;
			string sender = craneEvadeRequestBase.getSender();
			OrderCurrentBase senderOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(sender);

			//我拿到了PA1的收料指令
			//我空钩
			//我收到了4-5的请求避让指令
			//4-5当前是PA1的收料指令
			//我在我当前PA1收料位X的大侧
			//则我先执行避让，让4-5过来收料
			bFlagSender1 = (sender == "4_5") && 
										(cranePLCStatus.getHasCoil() == 0) &&
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent)) && 
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent)) && 
										(cranePLCStatus.getXAct() > craneOrderCurrent.getPlanUpX());


			//我拿到了PA1的收料指令
			//我重钩
			//我收到了4-5的请求避让指令
			//4-5当前是PA1的收料指令
			//我在我当前X是在PA1的起吊位
			//则我先执行避让，让4-5过来收料
			bFlagSender2 = (sender == "4_5") && 
										(cranePLCStatus.getHasCoil() == 1) &&
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent)) && 
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent)) && 
										(abs(cranePLCStatus.getXAct() - craneOrderCurrent.getPlanUpX()) < 100);

			//我拿到了非PA1的收料指令
			//我空钩
			//我收到了4-5的请求避让指令
			//4-5当前是PA1的收料指令
			//则我先执行避让，让4-5过来收料
			bFlagSender3 = (sender == "4_5") && 
											(cranePLCStatus.getHasCoil() == 0); //&&
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent) == false ) && 
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent));

			//我拿到了非PA1的收料指令
			//我重钩
			//我收到了4-5的请求避让指令
			//4-5当前是PA1的收料指令
			//如果我的落卷位置在4-5起卷位置X的大侧
			//则我先执行避让，让4-5过来收料
			bFlagSender4 = (sender == "4_5") && 
											(cranePLCStatus.getHasCoil() == 0) &&
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent) == false ) && 
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent)) && 
											( craneOrderCurrent.getPlanDownX() > senderOrderCurrent.getPlanUpX() ) ;

			if (bFlagSender1 == true)
			{
				log.Info()<<"4-4在PA1收料，空钩，收到4-5请求避让，4-5也在PA1收料，我在PA1收料位X大侧，则执行避让！"<<endl;
				bFlagSender = true;
			}

			if (bFlagSender2 == true)
			{
				log.Info()<<"4-4在PA1收料，重钩，收到4-5请求避让，4-5也在PA1收料，我就在当前收料位置X，则执行避让！"<<endl;
				bFlagSender = true;
			}

			if (bFlagSender3 == true)
			{
				log.Info()<<"4-4非PA1收料，空钩，收到4-5请求避让，4-5在PA1收料，则执行避让！"<<endl;
				bFlagSender = true;
			}

			if (bFlagSender4 == true)
			{
				log.Info()<<"4-4非PA1收料，重钩，收到4-5请求避让，4-5在PA1收料，4-4的落卷位位置在4-5起卷位置X大侧，则执行避让！"<<endl;
				bFlagSender = true;
			}

			if(craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
			{
				if ( bFlagSender == true)
				{
					log.Info()<<"TYPE_AFTER_JOB ====> TYPE_RIGHT_NOW：4-4先执行避让！"<<endl;
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
