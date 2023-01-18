#include "ACTION_MOVE_TO_DOWN_POS.h"

using namespace Monitor;

ACTION_MOVE_TO_DOWN_POS :: ACTION_MOVE_TO_DOWN_POS(void)
{
}



ACTION_MOVE_TO_DOWN_POS :: ~ACTION_MOVE_TO_DOWN_POS(void)
{
}



//1 doAction
bool ACTION_MOVE_TO_DOWN_POS :: doAction(string craneNO, 
																						   string bayNO,
																						   OrderCurrentBase orderCurrent, 
																						   CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_MOVE_TO_DOWN_POS :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_MOVE_TO_DOWN_POS------------------------ -----------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( ! ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getCmdStatus()"<<orderCurrent.getCmdStatus()<<endl;
		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;
		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS && cranePLCStatus.getHasCoil() == 0)
		{
			log.Debug()<<"行车当前指令处于起卷CoilDown状态，且行车hascoil = 0！返回true！"<<endl;
			ret=true;
			return ret;
		}

		log.Debug()<<"orderCurrent.getPlanDownX()"<<orderCurrent.getPlanDownX()<<endl;
		log.Debug()<<"orderCurrent.getPlanDownY()"<<orderCurrent.getPlanDownY()<<endl;
		if ( orderCurrent.getPlanDownX() == DB_INT_NULL || orderCurrent.getPlanDownY() == DB_INT_NULL )//取料点坐标封9
		{
			log.Debug()<<"放料点坐标封9， 返回 false！"<<endl;
			ret=false;
			return ret;
		}

		if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							orderCurrent.getPlanDownX(), 
																																							orderCurrent.getPlanDownY(), 
																																							100, 
																																							100 ) )
		{
			log.Debug()<<"行车已经到达 放料点 ！返回true！"<<endl;
			ret=true;
			return ret;
		}

		//准备下发行车移动指令（扫描移动指令）
		Clone_DownLoadMoving_Order::go(bayNO, 
																			craneNO, 
																			orderCurrent.getOrderNO(), 
																			cranePLCStatus.getXAct(), 
																			cranePLCStatus.getYAct(), 
																			orderCurrent.getPlanDownX(), 
																			orderCurrent.getPlanDownY(), 
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


