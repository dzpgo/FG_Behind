#include "ACTION_DOWN_POS_IS_OK.h"

using namespace Monitor;

ACTION_DOWN_POS_IS_OK :: ACTION_DOWN_POS_IS_OK(void)
{
}



ACTION_DOWN_POS_IS_OK :: ~ACTION_DOWN_POS_IS_OK(void)
{
}



//1 doAction
bool ACTION_DOWN_POS_IS_OK :: doAction(string craneNO, 
																					   string bayNO,
																					   OrderCurrentBase orderCurrent, 
																					   CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_DOWN_POS_IS_OK :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_DOWN_POS_IS_OK------------------------ ----------------------------"<<endl;
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

		//放料点是否有值  全都非封9
		if (orderCurrent.getPlanDownX() != DB_INT_NULL && orderCurrent.getPlanDownY() != DB_INT_NULL && orderCurrent.getPlanDownZ() != DB_INT_NULL)
		{
			log.Info()<<"PlanDownXYZ IS NOT 999999, means  PlanDownXYZ is OK, return true..................................................."<<endl;
			ret =  true;
			return ret;
		}

		//如果是封9  说明放料点还没收到  此时先把行车开到放料点附近  一般是中心点

		long centerX = DB_INT_NULL;
		long centerY = DB_INT_NULL;

		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			map<string, long> mapXYZValue;
			//toStockNO就是料格
			if ( false == Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromGridInfo(orderCurrent.getToStockNO(), mapXYZValue) )
			{
				log.Info()<<"this GRID area is no define in UACS_YARDMAP_GRID_INFO_DEFINE.........return false............."<<endl;
				ret = false;
				return ret;
			}
			centerX = mapXYZValue["X_CENTER"];
			centerY = mapXYZValue["Y_CENTER"];
		}

		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
			orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
		{
			//toStockNO就是车辆
			//如果没有carScanNO 则返回false
			if (orderCurrent.getCarScanNO().empty())
			{
				log.Info()<<"CarScanNO in OrderCurrent   IS   EMPTY,  return false........................."<<endl;
				ret = false;
				return ret;
			}

			//根据carScanNO获取 uacs_parking_srs_car_info 中的车辆扫描中心点
			if (false == Adapter_UACS_YARDMAP_STOCK_INFO::SelCarCenterXY(orderCurrent.getCarScanNO(), centerX, centerY))
			{
				log.Info()<<"CarScanNO Record in UACS_PARKING_SRS_CAR_INFO   IS   EMPTY,  return false........................."<<endl;
				ret = false;
				return ret;
			}			
		}

		if (centerX == DB_INT_NULL || centerY == DB_INT_NULL)
		{
			log.Info()<<"centerX == 999999 || centerY == 999999,  return false........................."<<endl;
			ret = false;
			return ret;
		}

		if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							centerX, 
																																							centerY, 
																																							100, 
																																							100 ) )
		{
			log.Debug()<<"行车已经到达 放料 扫描区域接近中心点  ！返回false！"<<endl;
			ret=false;
			return ret;
		}

		//准备下发行车移动指令（扫描移动指令）
		Clone_DownLoadMoving_Order::go(bayNO, 
																			craneNO, 
																			orderCurrent.getOrderNO(), 
																			cranePLCStatus.getXAct(), 
																			cranePLCStatus.getYAct(), 
																			centerX, 
																			centerY, 
																			cranePLCStatus.getHasCoil(), 
																			DB_INT_NULL, 
																			DB_INT_NULL, 
																			1);

		log.Debug()<<"Moving Order已经下发至行车PLC，等待行车走行至取料扫描位....进程完成，返回false...."<<endl;
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


