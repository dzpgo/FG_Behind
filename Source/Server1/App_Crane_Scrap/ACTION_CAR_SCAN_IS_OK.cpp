#include "ACTION_CAR_SCAN_IS_OK.h"

using namespace Monitor;

ACTION_CAR_SCAN_IS_OK :: ACTION_CAR_SCAN_IS_OK(void)
{
}



ACTION_CAR_SCAN_IS_OK :: ~ACTION_CAR_SCAN_IS_OK(void)
{
}



//1 doAction
bool ACTION_CAR_SCAN_IS_OK :: doAction(string craneNO, 
																				string bayNO,
																				OrderCurrentBase orderCurrent, 
																				CranePLCStatusBase cranePLCStatus)	
{
	bool ret=false;

	string functionName="ACTION_CAR_SCAN_IS_OK :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_CAR_SCAN_IS_OK----------------------- -----------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( !ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
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

		//检查carScanNo是否为空
		if (!orderCurrent.getCarScanNO().empty())//有车辆激光扫描号 说明已经获取到车辆扫描数据
		{
			log.Info()<<"CarScanNO IS NOT EMPTY，Del rec from UACS_CAR_SCAN_ORDER_REC by orderno.........return true....................."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::DelCarScanOrderRecByOrderNO(orderCurrent.getOrderNO());
			ret = true;
			return ret;
		}

		//发送行车到车辆区域扫描走行指令
		//获取车辆走行指令路径起点  终点
		long planStartX = DB_INT_NULL;
		long planStartY = DB_INT_NULL;
		long planEndX = DB_INT_NULL;
		long planEndY = DB_INT_NULL;
		string moveDir = "";
		if (false == ACTION_COMMON_FUNCTION::GetCarScanStartEndP(orderCurrent.getToStockNO(), planStartX, planStartY, planEndX, planEndY, moveDir))
		{
			//无法获取扫描起始点
			log.Info()<<"getCarScanStartEndP return false, .......................return false......................................"<<endl;
			ret = false;
			return ret;
		}

		//carScanNo为空情况
		string scanActionFlag = "";
		if ( false == Adapter_UACS_CRANE_ORDER_CURRENT::SelFlagInCarScanOrderRec(orderCurrent.getOrderNO(), scanActionFlag) )//无记录
		{
			//是否在起点 如果不在 发送 到起点指令；如果在，发送到终点指令
			if ( false == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), cranePLCStatus.getYAct(), planStartX, planStartY, 100, 100))
			{
				//发送到起点指令
				Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planStartX, 
																				planStartY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
				log.Info()<<"1.1 发送到停车位扫描起点指令......................................................................."<<endl;
			}
			else
			{
				//发送到终点指令
				Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planEndX, 
																				planEndY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
				log.Info()<<"1.2 发送到停车位扫描终点指令......................................................................."<<endl;
			}
			//插入记录到UACS_CAR_SCAN_ORDER_REC//orderNO, planstartXY planendXY  parkingNO  moveDir  rec_time
			Adapter_UACS_CRANE_ORDER_CURRENT::InsCarScanOrderRec(orderCurrent.getOrderNO(), 
																																orderCurrent.getToStockNO(), 
																																planStartX, 
																																planStartY, 
																																planEndX, 
																																planEndY, 
																																moveDir);
			log.Info()<<"新插入记录到 .....CarScanOrderRec table...........................return false......................................."<<endl;

			ret = false;
			return ret;
		}

		//下面是有记录的
		//carScan不为空
		if (scanActionFlag == "1")//行车的车辆扫描走行动作已经完成
		{
			log.Info()<<"scanActionFlag==1, means Crane Scan Car Action is FINISH...........wait scan result...............return false............... "<<endl;
			ret  =false;
			return ret;
		}

		//scanActionFlag不为1  说明行车扫描走行动作没有完成
		//可能是中间被中断了
		//重新发送行车到车辆扫描走行指令
		//是否在起点 如果不在 发送 到起点指令；如果在，发送到终点指令
		if ( false == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), cranePLCStatus.getYAct(), planStartX, planStartY, 100, 100))
		{
			//发送到起点指令
			Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planStartX, 
																				planStartY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
			log.Info()<<"2.1 发送到停车位扫描起点指令......................................................................."<<endl;
		}
		else
		{
			//发送到终点指令
			Clone_DownLoadMoving_Order::go(bayNO, 
																				craneNO, 
																				orderCurrent.getOrderNO(), 
																				cranePLCStatus.getXAct(), 
																				cranePLCStatus.getYAct(), 
																				planEndX, 
																				planEndY, 
																				cranePLCStatus.getHasCoil(), 
																				DB_INT_NULL, 
																				DB_INT_NULL, 
																				1);
			log.Info()<<"2.2 发送到停车位扫描终指令......................................................................."<<endl;
		}
		log.Info()<<"发送完毕，return false......................................................................."<<endl;
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


