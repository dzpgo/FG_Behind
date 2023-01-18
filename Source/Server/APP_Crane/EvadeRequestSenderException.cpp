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
	//false : û������
	//true��������
    bool bStifyException=false;

	string functionName="EvadeRequestSenderException :: satifyException()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{		
		if(craneNO=="4_6")
		{
			//�Է�4_7��
			if(neighborCraneNO=="4_7")
			{
				//4_6�ƶ����С�����ҿչ� ��������4-7�ķ����ƶ�
				if(movingDirection==MOVING_DIR::DIR_X_DES)
				{
					OrderCurrentBase craneOrderCurrent_Neightbor;
					craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
					//4-7��PA2����
					if( 1/*Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent_Neightbor)*/ )
					{
						if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
						{
							log.Info()<<"�Է��� 4-7׼��PA2���ϣ��Ҵ����ϰ�أ��ҷ���4-6������������������ͱ�������"<<endl;
							bStifyException = true;
							return bStifyException;
						}
					}
				}
			}
		}

		//***************����2��4-6��PA2���ϣ�4-6Ҫ����4-7����4-7Ŀǰ�����ϰ��ʱ*********************
		//4-7��
		if(craneNO=="4_7")
		{
			//�Է�4_6��
			if(neighborCraneNO=="4_6")
			{
				//4_7�ƶ��������� ��������4-6�ķ����ƶ�
				if(movingDirection==MOVING_DIR::DIR_X_INC)
				{
							OrderCurrentBase craneOrderCurrent_Neightbor;
							craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
							//4-6��PA2����
							//if( Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent_Neightbor) )
							if (1)
							{
								if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
								{
									log.Info()<<"�Է��� 4-6׼��PA2���ϣ��Ҵ����ϰ�أ��ҷ���4-7������������������ͱ�������"<<endl;
									bStifyException = true;
									return bStifyException;
								}
							}
				}
			}
		}

		//***************����3��4-6��C715 176���ϣ���ʱ4-5�����ͱ�������**************************************************
		//4-5��
		if(craneNO=="4_5")
		{
			//�Է�4_6��
			if(neighborCraneNO=="4_6")
			{
				//4_5�ƶ����С���� ��������4-6�ķ����ƶ�
				if(movingDirection==MOVING_DIR::DIR_X_DES)
				{
							OrderCurrentBase craneOrderCurrent_Neightbor;
							craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
							//4-6��C175  176 ����
							/*if(Test_Order_Postion_Answer::isUpPos_In_Yard(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_C175_Entry(craneOrderCurrent_Neightbor) || 
								Test_Order_Postion_Answer::isUpPos_In_Yard(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_C176_Entry(craneOrderCurrent_Neightbor))*/
							if (1)
							{
								if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
								{
									log.Info()<<"�Է��� 4-6׼��ΪC175��C176���ϣ��Ҵ����ϰ�أ��ҷ���4-5������������������ͱ�������"<<endl;
									bStifyException = true;
									return bStifyException;
								}
							}
				}
			}
		}


		if(craneNO=="4_6")
		{
			//�Է�4_7��
			if(neighborCraneNO=="4_7")
			{
				//4_6�ƶ����С���� ��������4-7�ķ����ƶ�
				if(movingDirection==MOVING_DIR::DIR_X_DES)
				{
					OrderCurrentBase craneOrderCurrent_Neightbor;
					craneOrderCurrent_Neightbor=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neighborCraneNO);
					//4-7��PA2����
					//if(Test_Order_Postion_Answer::isUpPos_PA2_Exit(craneOrderCurrent_Neightbor) && Test_Order_Postion_Answer::isDownPos_In_Yard(craneOrderCurrent_Neightbor) )
					if (1)
					{
						if(craneOrderCurrent_Neightbor.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
						{
							log.Info()<<"�Է��� 4-7׼��PA2���ϣ��Ҵ����ϰ�أ��ҷ���4-6������������������ͱ�������"<<endl;
							bStifyException = true;
							return bStifyException;
						}
					}
				}
			}
		}
		
		log.Info()<<"�޷�������������"<<endl;
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
