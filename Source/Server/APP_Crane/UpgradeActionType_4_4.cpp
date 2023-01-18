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


		//�������4-4
		

		if( craneNO=="4_4")
		{
			bool bFlagSender1 = false;
			bool bFlagSender2 = false;
			bool bFlagSender3 = false;
			bool bFlagSender4 = false;
			bool bFlagSender = false;
			string sender = craneEvadeRequestBase.getSender();
			OrderCurrentBase senderOrderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(sender);

			//���õ���PA1������ָ��
			//�ҿչ�
			//���յ���4-5���������ָ��
			//4-5��ǰ��PA1������ָ��
			//�����ҵ�ǰPA1����λX�Ĵ��
			//������ִ�б��ã���4-5��������
			bFlagSender1 = (sender == "4_5") && 
										(cranePLCStatus.getHasCoil() == 0) &&
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent)) && 
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent)) && 
										(cranePLCStatus.getXAct() > craneOrderCurrent.getPlanUpX());


			//���õ���PA1������ָ��
			//���ع�
			//���յ���4-5���������ָ��
			//4-5��ǰ��PA1������ָ��
			//�����ҵ�ǰX����PA1�����λ
			//������ִ�б��ã���4-5��������
			bFlagSender2 = (sender == "4_5") && 
										(cranePLCStatus.getHasCoil() == 1) &&
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent)) && 
										//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent)) && 
										(abs(cranePLCStatus.getXAct() - craneOrderCurrent.getPlanUpX()) < 100);

			//���õ��˷�PA1������ָ��
			//�ҿչ�
			//���յ���4-5���������ָ��
			//4-5��ǰ��PA1������ָ��
			//������ִ�б��ã���4-5��������
			bFlagSender3 = (sender == "4_5") && 
											(cranePLCStatus.getHasCoil() == 0); //&&
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent) == false ) && 
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent));

			//���õ��˷�PA1������ָ��
			//���ع�
			//���յ���4-5���������ָ��
			//4-5��ǰ��PA1������ָ��
			//����ҵ����λ����4-5���λ��X�Ĵ��
			//������ִ�б��ã���4-5��������
			bFlagSender4 = (sender == "4_5") && 
											(cranePLCStatus.getHasCoil() == 0) &&
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(craneOrderCurrent) == false ) && 
											//(Test_Order_Postion_Answer::isUpPos_PA1_Exit(senderOrderCurrent)) && 
											( craneOrderCurrent.getPlanDownX() > senderOrderCurrent.getPlanUpX() ) ;

			if (bFlagSender1 == true)
			{
				log.Info()<<"4-4��PA1���ϣ��չ����յ�4-5������ã�4-5Ҳ��PA1���ϣ�����PA1����λX��࣬��ִ�б��ã�"<<endl;
				bFlagSender = true;
			}

			if (bFlagSender2 == true)
			{
				log.Info()<<"4-4��PA1���ϣ��ع����յ�4-5������ã�4-5Ҳ��PA1���ϣ��Ҿ��ڵ�ǰ����λ��X����ִ�б��ã�"<<endl;
				bFlagSender = true;
			}

			if (bFlagSender3 == true)
			{
				log.Info()<<"4-4��PA1���ϣ��չ����յ�4-5������ã�4-5��PA1���ϣ���ִ�б��ã�"<<endl;
				bFlagSender = true;
			}

			if (bFlagSender4 == true)
			{
				log.Info()<<"4-4��PA1���ϣ��ع����յ�4-5������ã�4-5��PA1���ϣ�4-4�����λλ����4-5���λ��X��࣬��ִ�б��ã�"<<endl;
				bFlagSender = true;
			}

			if(craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
			{
				if ( bFlagSender == true)
				{
					log.Info()<<"TYPE_AFTER_JOB ====> TYPE_RIGHT_NOW��4-4��ִ�б��ã�"<<endl;
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
