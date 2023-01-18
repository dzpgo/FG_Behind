#include "ACTION_UP_POS_IS_OK.h"

using namespace Monitor;

ACTION_UP_POS_IS_OK :: ACTION_UP_POS_IS_OK(void)
{
}



ACTION_UP_POS_IS_OK :: ~ACTION_UP_POS_IS_OK(void)
{
}



//1 doAction
bool ACTION_UP_POS_IS_OK :: doAction(string craneNO, 
																		 string bayNO,
																		 OrderCurrentBase orderCurrent, 
																		 CranePLCStatusBase cranePLCStatus)	
{
	bool ret=false;

	string functionName="ACTION_UP_POS_IS_OK :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_UP_POS_IS_OK---------------------------- -----------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( ! ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getCmdStatus()"<<orderCurrent.getCmdStatus()<<endl;
		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;

		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && cranePLCStatus.getHasCoil() > 0)
		{
			log.Debug()<<"行车当前指令处于起卷CoilUp状态，且行车hascoil > 0！返回true！"<<endl;
			ret=true;
			return ret;
		}

		//取料点是否有值  全都非封9
		if (orderCurrent.getPlanUpX() != DB_INT_NULL && orderCurrent.getPlanUpY() != DB_INT_NULL && orderCurrent.getPlanUpZ() != DB_INT_NULL)
		{
			log.Info()<<"planUpXYZ IS NOT 999999, means  planUpXYZ is OK, return true..................................................."<<endl;
			ret =  true;
			return ret;
		}

		//取料点 封9的话 判断检查 MAT_UP_SCAN_NO是否是 NO_MAT  如果是  则取料完成
		if (orderCurrent.getMatUpScanNO() == "NO_MAT")
		{
			//如果是归堆指令，则
			if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				//清空当前指令表  
				log.Info()<<"orderCurrent.getMatUpScanNO() == NO_MAT, means END OF MAT UP..........init OrderCurrent , return false......................................."<<endl;
				//清空指令表，返回false
				//方法：
				//1.清空指令表
				//2.通知指令模块 归堆指令完成
			}

			//如果是装车指令, 则报警提示,返回false
			if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
				orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
			{
				log.Info()<<"orderCurrent.getMatUpScanNO() == NO_MAT, means ERROR OF MAT UP.......... return false......................................."<<endl;
			}


			ret = false;
			return ret;
		}


		//判断行车是否在要取料的区域内  卸料区  或者料格	

		//首先获取卸料区或料格的中心点坐标
		map<string, long> mapXYZValue;
			
		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			//fromStockNO就是卸料区
			if ( false == Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromDumpingInfo(orderCurrent.getFromStockNO(), mapXYZValue) )
			{
				log.Info()<<"this DUMPING area is no define in UACS_DUMPING_INFO_DEFINE.........return false............."<<endl;
				ret = false;
				return ret;
			}
		}

		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
			orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
		{
			//fromStockNO就是料格
			if ( false == Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromGridInfo(orderCurrent.getFromStockNO(), mapXYZValue) )
			{
				log.Info()<<"this GRID area is no define in UACS_YARDMAP_GRID_INFO_DEFINE.........return false............."<<endl;
				ret = false;
				return ret;
			}
		}

		long scanXCenter = mapXYZValue["X_CENTER"];
		long scanYCenter = mapXYZValue["Y_CENTER"];

		//行车是否到达取料扫描区域接近中心点
		if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							scanXCenter, 
																																							scanYCenter, 
																																							100, 
																																							100 ) )
		{
			log.Debug()<<"行车已经到达 取料 扫描区域接近中心点 ！返回 false！"<<endl;
			ret=false;
			return ret;
		}

		//行车还未到达  发送指令让行车去
		Clone_DownLoadMoving_Order::go(bayNO, 
																			craneNO, 
																			orderCurrent.getOrderNO(), 
																			cranePLCStatus.getXAct(), 
																			cranePLCStatus.getYAct(), 
																			scanXCenter, 
																			scanYCenter, 
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


