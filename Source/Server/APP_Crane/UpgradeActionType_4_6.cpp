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


			 //���4-6�չ���
			 //��4-6��ǰWMSָ���PA2�Ļ�������ָ��
			 //�ұ���ָ���У���������4-7����4-7��ǰҪִ�е�WMSָ����ȥPA2����
			 //������4-6����ָ��ΪRIGHT_NOW
			 //����������4_6
			 if( craneNO=="4_6")
			{
					bool bFlagCrane = false;
					bool bFlagSender = false;

					//4-6��ǰ��WMSָ����ȥPA2����
					bFlagCrane = true;  //Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent);				

					//4-7��ǰWMSָ����ȥPA2����
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
									log.Info()<<"TYPE_AFTER_JOB ====> TYPE_RIGHT_NOW��4-7���ϣ�4-6�����ã�"<<endl;
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
