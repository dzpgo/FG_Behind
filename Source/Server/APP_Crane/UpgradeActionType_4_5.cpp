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


		//��������г���4-5
		//�Է��г�4-6׼����C175 176����
		//������4-5����ָ��ΪRIGHT_NOW
		//����������4_5
		if( craneNO=="4_5")
		{
			bool bFlagCrane = false;
			bool bFlagSender = false;

			//4-6 ��ȥC715  176����
			string sender = craneEvadeRequestBase.getSender();
			OrderCurrentBase senderOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(sender);
			bFlagSender = (sender == "4_6") ;
				//&& (Test_Order_Postion_Answer::isUpPos_In_Yard(senderOrderCurrent) && Test_Order_Postion_Answer	::isDownPos_C175_Entry(senderOrderCurrent) || 
				//Test_Order_Postion_Answer::isUpPos_In_Yard(senderOrderCurrent) && Test_Order_Postion_Answer	::isDownPos_C176_Entry(senderOrderCurrent));


			if(craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
			{
				if ( bFlagSender == true )
				{
					log.Info()<<"TYPE_AFTER_JOB ====> TYPE_RIGHT_NOW��4-6��175/176���ϣ�4-5�����ã�"<<endl;
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
