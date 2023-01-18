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
			log.Debug()<<"行车当前指令处于起卷CoilUp状态，且行车hascoil != 0！返回true！"<<endl;
			ret=true;
			return ret;
		}

		log.Debug()<<"orderCurrent.getPlanUpX()"<<orderCurrent.getPlanUpX()<<endl;
		log.Debug()<<"orderCurrent.getPlanUpY()"<<orderCurrent.getPlanUpY()<<endl;
		if ( orderCurrent.getPlanUpX() == DB_INT_NULL || orderCurrent.getPlanUpY() == DB_INT_NULL )//取料点坐标封9
		{
			log.Debug()<<"取料点坐标封9， 返回 false！"<<endl;
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
			log.Debug()<<"行车已经到达 取料点 ！返回true！"<<endl;
			ret=true;
			return ret;
		}

		//准备下发行车移动指令（扫描移动指令）
		//当前要取料重量
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

		log.Debug()<<"Moving Order已经下发至行车PLC，等待行车走行至取料位....进程完成，返回false...."<<endl;
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


