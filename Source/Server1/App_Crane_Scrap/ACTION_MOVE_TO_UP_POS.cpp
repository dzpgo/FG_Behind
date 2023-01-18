#include "ACTION_MOVE_TO_UP_POS.h"

using namespace Monitor;

ACTION_MOVE_TO_UP_POS :: ACTION_MOVE_TO_UP_POS(void)
{
}



ACTION_MOVE_TO_UP_POS :: ~ACTION_MOVE_TO_UP_POS(void)
{
}



//1 doAction
bool ACTION_MOVE_TO_UP_POS :: doAction(string craneNO, 
																				   string bayNO,
																				   OrderCurrentBase orderCurrent, 
																				   CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_MOVE_TO_UP_POS :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_MOVE_TO_UP_POS------------------------ -----------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( ! ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getCmdStatus()"<<orderCurrent.getCmdStatus()<<endl;
		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;
		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && cranePLCStatus.getHasCoil() != 0)
		{
			log.Debug()<<"�г���ǰָ������CoilUp״̬�����г�hascoil != 0������true��"<<endl;
			ret=true;
			return ret;
		}

		log.Debug()<<"orderCurrent.getPlanUpX()"<<orderCurrent.getPlanUpX()<<endl;
		log.Debug()<<"orderCurrent.getPlanUpY()"<<orderCurrent.getPlanUpY()<<endl;
		if ( orderCurrent.getPlanUpX() == DB_INT_NULL || orderCurrent.getPlanUpY() == DB_INT_NULL )//ȡ�ϵ������9
		{
			log.Debug()<<"ȡ�ϵ������9�� ���� false��"<<endl;
			ret=false;
			return ret;
		}

		if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							orderCurrent.getPlanUpX(), 
																																							orderCurrent.getPlanUpY(), 
																																							100, 
																																							100 ) )
		{
			log.Debug()<<"�г��Ѿ����� ȡ�ϵ� ������true��"<<endl;
			ret=true;
			return ret;
		}

		//׼���·��г��ƶ�ָ�ɨ���ƶ�ָ�
		//��ǰҪȡ������
		Clone_DownLoadMoving_Order::go(bayNO, 
																			craneNO, 
																			orderCurrent.getOrderNO(), 
																			cranePLCStatus.getXAct(), 
																			cranePLCStatus.getYAct(), 
																			orderCurrent.getPlanUpX(), 
																			orderCurrent.getPlanUpY(), 
																			cranePLCStatus.getHasCoil(), 
																			DB_INT_NULL, 
																			DB_INT_NULL, 
																			1);

		log.Debug()<<"Moving Order�Ѿ��·����г�PLC���ȴ��г�������ȡ��λ....������ɣ�����false...."<<endl;
		ret = false;
		return ret;		

	}
	catch(iDA::Exception &x)
	{
		try
		{
			ret=false;

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
		ret=false;

		log.Debug()<<functionName<<"   error:"<<endl;
	}

	return ret;
}


