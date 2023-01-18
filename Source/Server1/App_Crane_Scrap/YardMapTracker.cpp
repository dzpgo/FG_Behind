#include "YardMapTracker.h"

#include <pace/MsgTube.h>
#include <pace/MsgTubeI.h>

#include "ACTION_COMMON_FUNCTION.h"


using namespace iPlature;


const bool YardMapTracker::COIL_UP=true;

const bool YardMapTracker::COIL_DOWN=false;

YardMapTracker::YardMapTracker( )
{    
	actionTrack = "No Work";
	CraneMonitor::getInstance()->getPLCStatus(cranePLCStatus_Last);
	orderIDOld = 0;
	orderNODurTrack = 0;
}




void  YardMapTracker::EventTrack_CraneActions()
{

	string functionName="YardMapTracker :: EventTrack_CraneActions()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//get  new PLCStatus
		CraneMonitor::getInstance()->getPLCStatus(cranePLCStatus_Current);
		log.Info()<<"craneNO = "<<cranePLCStatus_Current.getCraneNO()<<endl;		

		//get new ordercurrent
		OrderCurrentBase orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(cranePLCStatus_Current.getCraneNO());	

		orderIDNew=orderCurrent.getOrderNO();

		//
		if (orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY && 
			 orderIDOld != orderIDNew )
		{
			//初始化 动作跟踪tag点
			actionTrack = StringHelper::ToString(orderIDNew) + "=1";
			orderIDOld = orderIDNew;
		}

		if (orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			actionTrack = "No Work";
			orderIDOld = 0;
		}

		log.Info()<<"actionTrack = "<<actionTrack<<endl;

		//string tagName = "EV_";


//=======================================自动模式下 库图跟踪==============================================================

		if( cranePLCStatus_Current.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO )
		{
			log.Info()<<"....................................................................................................................................................................................................."<<endl;
			log.Info()<<"...............................................................Start Crane Action Tracker......................................................................................"<<endl;
			log.Info()<<"....................................................................................................................................................................................................."<<endl;
//--------------------------------------------------状态=2：吊具空载到取料位上方！-------------------------------------------------------------------------------------------------------------------------
			if (ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanUpX(), orderCurrent.getPlanUpY()) == true  
				&& cranePLCStatus_Current.getHasCoil() == 0 
				&& orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY 
				&& existSubString(actionTrack, ",2") == false )
			{				
				
				log.Info()<<">>>>>>状态=2：吊具空载到取料位上方！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",2";

				string cmdStatus = "2";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_PLAN_UP_POS_ARRIVE_2 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);
				


			}

//--------------------------------------------------状态=3：吊具空载下降到位！-------------------------------------------------------------------------------------------------------------------------
			if (ACTION_COMMON_FUNCTION::Assistant_Is_PlaceClampArrived(cranePLCStatus_Current.getZAct(), orderCurrent.getPlanUpZ(), "CoilUp") == true 
				&& ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanUpX(), orderCurrent.getPlanUpY()) == true
				&& cranePLCStatus_Current.getHasCoil() == 0 
				&& orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY  
				&& existSubString(actionTrack, ",3") == false)
			{
				log.Info()<<">>>>>>状态=3：吊具空载下降到位！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",3";

				string cmdStatus = "3";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_EMPTY_CLAMP_DOWN_3 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);

			}

//--------------------------------------------------状态=4：吊具空载变重载！-------------------------------------------------------------------------------------------------------------------------
			if(cranePLCStatus_Last.getHasCoil()==0 && cranePLCStatus_Current.getHasCoil() > 0 
				&& ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanUpX(), orderCurrent.getPlanUpY()) == true
				&& orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY 
				&& existSubString(actionTrack, ",4") == false)
			{
				log.Info()<<">>>>>>状态=4：吊具空载变重载！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",4";

				string cmdStatus = "4";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_CLAMP_EMPTY_TO_FULL_4 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);

				//更新行车当前指令表中的MAT_CUR_WGT=hascoil
				long matCurWgt = cranePLCStatus_Current.getHasCoil();
				Adapter_UACS_CRANE_ORDER_CURRENT::UpdMatCurWgt(orderCurrent.getCraneNO(), matCurWgt);
				log.Info()<<"Update MatCurWgt into uacs_crane_order_current........................................................."<<endl;


			}

//--------------------------------------------------状态=5：吊具重载上升到位！-------------------------------------------------------------------------------------------------------------------------
			if ( ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanUpX(), orderCurrent.getPlanUpY()) == true 
				&& ACTION_COMMON_FUNCTION::Assistant_Is_ZValueArrived( cranePLCStatus_Current.getZAct(), 5000 ) == true 
			    && cranePLCStatus_Current.getHasCoil() > 0  
			    && orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY  
			    && existSubString(actionTrack, ",5") == false)
			{
				log.Info()<<">>>>>>状态=5：吊具重载上升到位！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",5";

				string cmdStatus = "5";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_FULL_CLAMP_UP_5 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);

			}

//--------------------------------------------------状态=6：吊具重载到放料点上方！-------------------------------------------------------------------------------------------------------------------------
			if (ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanDownX(), orderCurrent.getPlanDownY()) == true 
				&& cranePLCStatus_Current.getHasCoil() > 0 
				&& orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY  
				&& existSubString(actionTrack, ",6") == false)
			{
				log.Info()<<">>>>>>状态=6：吊具重载到放料点上方！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",6";

				string cmdStatus = "6";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_PLAN_DOWN_POS_ARRIVE_6 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);

			}

//--------------------------------------------------状态=7：吊具重载下降到位！-------------------------------------------------------------------------------------------------------------------------
			if (ACTION_COMMON_FUNCTION::Assistant_Is_PlaceClampArrived(cranePLCStatus_Current.getZAct(), orderCurrent.getPlanDownZ(), "CoilDown") == true 
				&& cranePLCStatus_Current.getHasCoil() > 0 
				&& ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanDownX(), orderCurrent.getPlanDownY()) == true
				&& orderCurrent.getCmdStatus() != CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY  
				&& existSubString(actionTrack, ",7") ==false)
			{
				log.Info()<<">>>>>>状态=7：吊具重载下降到位！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",7";

				string cmdStatus = "7";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_FULL_CLAMP_DOWN_7 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);

			}

//--------------------------------------------------状态=8：吊具重载变空载！-------------------------------------------------------------------------------------------------------------------------
			if( cranePLCStatus_Last.getHasCoil() > 0 &&  cranePLCStatus_Current.getHasCoil()==0 
				&& ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanDownX(), orderCurrent.getPlanDownY()) == true  
				&& orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY  
				&& existSubString(actionTrack, ",8") == false)	
			{
				log.Info()<<">>>>>>状态=8：吊具重载变空载！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",8";

				string cmdStatus = "8";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_CLAMP_FULL_TO_EMPTY_8 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);

				//更新matCurWgt=0
				//更加matActWgt累加
				long matCurWgt = cranePLCStatus_Last.getHasCoil();
				Adapter_UACS_CRANE_ORDER_CURRENT::UpdMatCurWgt(orderCurrent.getCraneNO(), 0);
				log.Info()<<"Upd MatCurWgt = 0..........................................."<<endl;
				Adapter_UACS_CRANE_ORDER_CURRENT::UpdMatActWgt(orderCurrent.getCraneNO(), matCurWgt);
				log.Info()<<"Upd MatActWgt = MatActWgt + MatCurWgt..........................................."<<endl;

			}

//--------------------------------------------------状态=9：吊具空载上升到位！-------------------------------------------------------------------------------------------------------------------------
			if(ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived(cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), orderCurrent.getPlanDownX(), orderCurrent.getPlanDownY()) == true 
				&& ACTION_COMMON_FUNCTION::Assistant_Is_ZValueArrived(cranePLCStatus_Current.getZAct(), 5000) == true 
				&& cranePLCStatus_Current.getHasCoil() == 0 
				&& orderCurrent.getCmdStatus() != CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY
				&& 
				(existSubString(actionTrack, ",6") == true || //6
				existSubString(actionTrack, ",7") == true ||  //7
				existSubString(actionTrack, ",8") == true ) //8
				&& existSubString(actionTrack, ",9") == false  
			 )
			{
				log.Info()<<">>>>>>状态=9：吊具空载上升到位！<<<<<<"<<endl;
				log.Info()<<"指令号="<<orderCurrent.getOrderNO()<<endl;
				log.Info()<<"物料代码="<<orderCurrent.getMatCode()<<endl;
				log.Info()<<"取料位库位="<<orderCurrent.getFromStockNO()<<endl;
				log.Info()<<"放料位库位="<<orderCurrent.getToStockNO()<<endl;

				actionTrack += ",9";

				string cmdStatus = "9";

				//获取当前所在stockno
				string stockNO = "UnKnown";
				Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(orderCurrent.getBayNO(), cranePLCStatus_Current.getXAct(), cranePLCStatus_Current.getYAct(), stockNO);

				//将相关数据插入行车实绩表 uacs_order_oper
				Adapter_UACS_CRANE_ORDER_CURRENT::InsOrderOper(orderCurrent.getOrderNO(), 
																														orderCurrent.getOrderType(), 
																														orderCurrent.getBayNO(), 
																														orderCurrent.getMatCode(), 
																														orderCurrent.getCompCode(), 
																														orderCurrent.getMatType(), 
																														orderCurrent.getMatReqWgt(), 
																														orderCurrent.getMatCurWgt(), 
																														cranePLCStatus_Current.getHasCoil(), 
																														orderCurrent.getFromStockNO(), 
																														orderCurrent.getToStockNO(), 
																														stockNO, 
																														cmdStatus, 
																														orderCurrent.getCmdSeq(), 
																														cranePLCStatus_Current.getPlanUpX(), 
																														cranePLCStatus_Current.getPlanUpY(), 
																														cranePLCStatus_Current.getPlanUpZ(), 
																														cranePLCStatus_Current.getXAct(), 
																														cranePLCStatus_Current.getYAct(), 
																														cranePLCStatus_Current.getZAct(), 
																														StringHelper::ToString( cranePLCStatus_Current.getControlMode()) );

				//tag点通知指令模块更新相关指令表
				//通知指令模块 ：指令状态变化tag点：EV_CRANE_ORDER_CMD_STATUS
				//格式：指令号（orderNO），指令执行次数（cmdSeq），指令状态，当次作业量
				//指令状态（）
				string tagName = "EV_CRANE_ORDER_CMD_STATUS";
				string tagValue = StringHelper::ToString(orderCurrent.getOrderNO()) + "," + StringHelper::ToString(orderCurrent.getCmdSeq());
				tagValue += "," + OrderQueueBase::CMD_STATUS_EMPTY_CLAMP_UP_9 + StringHelper::ToString(cranePLCStatus_Current.getHasCoil());
				ACTION_COMMON_FUNCTION::setEVTag(tagName, tagValue);

			}

			log.Info()<<"....................................................................................................................................................................................................."<<endl;
			log.Info()<<"...............................................................End Crane Action Tracker......................................................................................"<<endl;
			log.Info()<<"....................................................................................................................................................................................................."<<endl;

		}

		
//===================================自动模式下 激光扫描请求发送 UL01  UL02=================================================

		if( cranePLCStatus_Current.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO )
		{
			log.Info()<<"Start UL01  UL02  Send Handle..........................................................................................................................."<<endl;

			if( cranePLCStatus_Current.getHasCoil() == 0 && orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS )
			{
				log.Info()<<"Hascoil=0   COIL_UP_PROCESS.............................................................................................................."<<endl;
				//入库归堆指令
				//1
				if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
				{
					log.Info()<<"ORDER_TYPE_L3_CAR_TO_YARD_11.............................................................................................................."<<endl;
					if (orderCurrent.getPlanUpX() != DB_INT_NULL && orderCurrent.getPlanUpY() != DB_INT_NULL)
					{
						log.Info()<<"getPlanUpXY has Value.............................................................................................................."<<endl;
					}
					else//封9  是否需要发送UL01
					{
						log.Info()<<"getPlanUpXY has NO Value,ready to enter sendUL01.............................................................................................................."<<endl;
						sendUL01(orderCurrent, cranePLCStatus_Current);
					}
				}//end of 1

				//2
				if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
					orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
				{
					log.Info()<<"ORDER_TYPE_L3_YARD_TO_CAR_21  ORDER_TYPE_EAF_YARD_TO_CAR_22............................................"<<endl;
					//是否有车辆激光扫描号
					if (!orderCurrent.getCarScanNO().empty())//有车辆激光扫描号
					{
						log.Info()<<"CarScanNO  has Value.............................................................................................................."<<endl;
						if (orderCurrent.getPlanUpX() != DB_INT_NULL && orderCurrent.getPlanUpY() != DB_INT_NULL )
						{
							log.Info()<<"getPlanUpXY has Value.............................................................................................................."<<endl;
						}
						else//封9  是否需要发送UL01
						{
							log.Info()<<"getPlanUpXY has  NO Value,ready to enter sendUL01.............................................................................................................."<<endl;
							sendUL01(orderCurrent, cranePLCStatus_Current);
						}
					}
					else
					{
						log.Info()<<"CarScanNO  NO  Value, ready to Enter sendUL02.............................................................."<<endl;
						sendUL02(orderCurrent, cranePLCStatus_Current);
					}					
				}//end of 2
			}//end of hascoil=0 coilUpProcess



			if( cranePLCStatus_Current.getHasCoil() > 0 && orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS )
			{
				log.Info()<<"Hascoil>0   COIL_DOWN_PROCESS.............................................................................................................."<<endl;
				//入库归堆指令
				//3
				if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
				{
					log.Info()<<"ORDER_TYPE_L3_CAR_TO_YARD_11.............................................................................................................."<<endl;
					if (orderCurrent.getPlanDownX() != DB_INT_NULL && orderCurrent.getPlanDownY() != DB_INT_NULL)
					{
						log.Info()<<"getPlanDownXY has Value.............................................................................................................."<<endl;
					}
					else//封9  是否需要发送UL01
					{
						log.Info()<<"getPlanDownXY NO Value,ready to enter sendUL01.............................................................................................................."<<endl;
						sendUL01(orderCurrent, cranePLCStatus_Current);
					}
				}//end of 3

				//4
				if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
					orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
				{
					log.Info()<<"ORDER_TYPE_L3_YARD_TO_CAR_21  ORDER_TYPE_EAF_YARD_TO_CAR_22............................................"<<endl;
					
					if (orderCurrent.getPlanDownX() != DB_INT_NULL && orderCurrent.getPlanDownY() != DB_INT_NULL )
					{
						log.Info()<<"getPlanDownXY has Value.............................................................................................................."<<endl;
					}
					else//封9  是否需要发送UL01
					{
						log.Info()<<"getPlanDownXY has  NO Value,ready to enter sendUL01.............................................................................................................."<<endl;
						sendUL01(orderCurrent, cranePLCStatus_Current);
					}					
				}//end of 4
				
			}//end of hascoil=1 coilDownProcess
			log.Info()<<"End  UL01  UL02  Send Handle..........................................................................................................................."<<endl;

		}


//===========================跟踪记录行车扫描车辆动作是否完成==============================================
		if (cranePLCStatus_Current.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO)
		{//11
			log.Info()<<"Start to Handle CAR SCAN CRANE MOVE .................................................................."<<endl;

			if (orderCurrent.getCmdStatus() != OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
			{//22
				string parkingNO = "";
				long planStartX = DB_INT_NULL;
				long planStartY = DB_INT_NULL;
				long planEndX = DB_INT_NULL;
				long planEndY = DB_INT_NULL;
				long actStartX = DB_INT_NULL;
				long actStartY = DB_INT_NULL;
				long actEndX = DB_INT_NULL;
				long actEndY = DB_INT_NULL;
				string moveDir = "";
				string scanActionFlag = "";

				if (true == Adapter_UACS_CRANE_ORDER_CURRENT::SelCarScanOrderRec(orderCurrent.getOrderNO(), 
																																						parkingNO, 
																																						planStartX, 
																																						planStartY, 
																																						planEndX, 
																																						planEndY, 
																																						actStartX, 
																																						actStartY, 
																																						actEndX, 
																																						actEndY, 
																																						moveDir, 
																																						scanActionFlag))
				{//33
					if (scanActionFlag != "1")//未完成
					{//44

						if (actStartX != DB_INT_NULL && actStartY != DB_INT_NULL)//如果act起始点具备 说明已经开始了
						{
							log.Info()<<"actStartX != DB_INT_NULL && actStartY != DB_INT_NULL...................................................................................."<<endl;
							
							if (false == notLeaveCenter(moveDir, planStartX, planEndX, planStartY, planEndY, cranePLCStatus_Current) )//偏离中心点 认为是做别的任务
							{
								log.Info()<<"Crane scan car action leave center.........................."<<endl;
								//清空起始点actStartXY为 DB_INT_NULL
								Adapter_UACS_CRANE_ORDER_CURRENT::InitActStartXYInCarScanOrderRec(orderCurrent.getOrderNO());
							}
							else//不偏离中心点  跟踪终止点
							{
								log.Info()<<"Crane scan car action NOT leave center.........................."<<endl;
								if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus_Current.getXAct(), 
																																													cranePLCStatus_Current.getYAct(), 
																																													planEndX, 
																																													planEndY, 
																																													500, 
																																													500) )
								{
									//到达终止点，更新actXY进表
									log.Info()<<"Crane scan car action Arrive scan end point...........ready to write actendXY into table..............."<<endl;
									Adapter_UACS_CRANE_ORDER_CURRENT::UpdActEndXYInCarScanOrderRec(orderCurrent.getOrderNO(), 
																																												cranePLCStatus_Current.getXAct(), 
																																												cranePLCStatus_Current.getYAct());
									log.Info()<<"Ready to Update scanActionFlag = 1.........................."<<endl;
									Adapter_UACS_CRANE_ORDER_CURRENT::UpdScanActionFlag(orderCurrent.getOrderNO(), "1");
								}
							}
						}
						else if (actStartX == DB_INT_NULL || actStartY == DB_INT_NULL)
						{
							log.Info()<<"actStartX == DB_INT_NULL || actStartY == DB_INT_NULL...................................................................................."<<endl;
							//跟踪开始点
							if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus_Current.getXAct(), 
																																												cranePLCStatus_Current.getYAct(), 
																																												planStartX, 
																																												planStartY, 
																																												500, 
																																												500) )
							{
								log.Info()<<"Crane scan car action Arrive scan start point...........ready to write actstartXY into table..............."<<endl;
								//到达开始点，更新actXY进表
								Adapter_UACS_CRANE_ORDER_CURRENT::UpdActStartXYInCarScanOrderRec(orderCurrent.getOrderNO(), 
																																											cranePLCStatus_Current.getXAct(), 
																																											cranePLCStatus_Current.getYAct());
							}
						}

					}//44
				}//33
			}//22

		}//11









		





		



		cranePLCStatus_Last = cranePLCStatus_Current;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}

}


bool YardMapTracker::existSubString(string str1, string str2)
{
	string functionName="YardMapTracker :: existSubString()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool ret = false;
	try
	{
		string::size_type idx = str1.find( str2 );
		if ( idx != string::npos )
			ret = true;
		else
			ret = false;
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;
}

void YardMapTracker::sendUL01(OrderCurrentBase orderCurrent, CranePLCStatusBase cranePLCStatus)
{
	string functionName="YardMapTracker :: sendUL01()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Info()<<"Start sendUL01.............................................................................................................."<<endl;
		//获取当前tagValue值
		string tagName = "EV_CRANE_" + orderCurrent.getCraneNO() + "_UL01";
		string tagValue = ACTION_COMMON_FUNCTION::getTagValue(tagName);

		//20220920 zhangyuhong add
		//考虑到 行车切手动后，是否需要重新发扫描请求，因为手动行车可能会改变料堆形状  ，需要重新扫描料堆
		//因此，在行车切手动后，把此tag点置成一个 固定字符串，以区分
		//切手动后，此tag点值为  MANU
		if (tagValue == "MANU")
		{
			string newTagValue = "";
			if ( true == getUL01TagValue(orderCurrent, cranePLCStatus, newTagValue) )
			{
				ACTION_COMMON_FUNCTION::setEVTag(tagName, newTagValue);
			}
			return;
		}

		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(tagValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA))); 

		if (kValues.size() < 13)
		{
			log.Info()<<"UL01 tagValue , kValues.size() < 13 , return ...................................................."<<endl;
			return;
		}

		string actionType = kValues[2];

		long orderNOTag = StringHelper::ToNumber<long>(kValues[5]);
		long cmdSeqTag = StringHelper::ToNumber<long>(kValues[6]);

		if (orderCurrent.getOrderNO() == orderNOTag && orderCurrent.getCmdSeq() == cmdSeqTag )//已经发送过
		{
			log.Info()<<"Just send UL01....................................................."<<endl;
			//根据orderNO 和 actionType 查询 UACS_PARKING_SRS_MAT_INFO 获取最新一条记录  就是刚才发的  
			//然后判断这条记录中的  scanResult 是否是0-失败
			string scanResult = "";
			Adapter_UACS_CRANE_ORDER_CURRENT::SelSRSMatInfoScanResult(orderNOTag, actionType, scanResult);
			if (scanResult == "0")//扫描反馈结果是失败  准备重发一次  
			{
				log.Info()<<"But Just send UL01 ScanResult  = 0 , means  failed,  ready ReSend....................................................."<<endl;
				//重新发送
				string newTagValue = "";
				if ( true == getUL01TagValue(orderCurrent, cranePLCStatus, newTagValue) )
				{
					ACTION_COMMON_FUNCTION::setEVTag(tagName, newTagValue);
				}
			}
		} 
		else//orderNO 或者 cmdSeq不相同  说明还未发送  准备发送
		{
			log.Info()<<"Not yet send UL01,  ready to send....................................................."<<endl;
			//发送
			string newTagValue = "";
			if ( true == getUL01TagValue(orderCurrent, cranePLCStatus, newTagValue) )
			{
				ACTION_COMMON_FUNCTION::setEVTag(tagName, newTagValue);
			}
		}

	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
}


void YardMapTracker::sendUL02(OrderCurrentBase orderCurrent, CranePLCStatusBase cranePLCStatus)
{
	string functionName="YardMapTracker :: sendUL02()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Info()<<"Start sendUL02 handler.........................................................................."<<endl;
		//获取当前tagValue值
		string tagName = "EV_CRANE_" + orderCurrent.getCraneNO() + "_UL02";
		string tagValue = ACTION_COMMON_FUNCTION::getTagValue(tagName);

		vector<string> kValues;
		kValues = StringHelper::ToVector<string>(tagValue, const_cast<char*>(SPLIT_COMMA), static_cast<int>(strlen(SPLIT_COMMA))); 

		if (kValues.size() < 12)
		{
			log.Info()<<"UL02 tagValue , kValues.size() < 12 , return ...................................................."<<endl;
			return;
		}

		long orderNOTag = StringHelper::ToNumber<long>(kValues[11]);

		if (orderCurrent.getOrderNO() == orderNOTag )//此条指令号对应的车辆激光扫描请求已经发送过
		{
			log.Info()<<"Just send UL02....................................................."<<endl;
			//根据orderNO  查询 UACS_PARKING_SRS_CAR_INFO 获取最新一条记录  就是刚才发的  
			//然后判断这条记录中的  scanResult 是否是0-失败
			string scanResult = "";
			Adapter_UACS_CRANE_ORDER_CURRENT::SelSRSCarInfoScanResult(orderNOTag, scanResult);
			if (scanResult == "0")//车辆扫描反馈结果是失败  准备重发一次  
			{
				log.Info()<<"But Just send UL02 ScanResult  = 0 , means  failed,  ready ReSend....................................................."<<endl;
				//重新发送
				string newTagValue = "";
				if ( true == getUL02TagValue(orderCurrent, newTagValue) )
				{
					ACTION_COMMON_FUNCTION::setEVTag(tagName, newTagValue);
				}
			}
			else if (scanResult == "1") //扫描成功
			{
				log.Info()<<"Just send UL02 ScanResult  = 1 , means  success..........return.........................................."<<endl;
				return;
			}
			else//等待扫描结果
			{
				log.Info()<<"Just send UL02 ScanResult  is UnKnown , wait a moment..........return.........................................."<<endl;
				return;
			}
		} 
		else//orderNO 不相同  说明还未发送  准备发送
		{
			log.Info()<<"Not yet send UL02,  ready to send....................................................."<<endl;
			//发送
			string newTagValue = "";
			if ( true == getUL02TagValue(orderCurrent, newTagValue) )
			{
				ACTION_COMMON_FUNCTION::setEVTag(tagName, newTagValue);
			}
		}

	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
}


bool YardMapTracker::getUL01TagValue(OrderCurrentBase orderCurrent, CranePLCStatusBase cranePLCStatus, string& tagValue)
{
	string functionName="YardMapTracker :: getUL01TagValue()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{

		//tag格式 增加 cmdSeq   用orderNO和cmdSeq来判断是否发过
		//KEY_MessageNo,KEY_CraneNo,KEY_ActionType,KEY_CraneX,KEY_CraneY, orderNO, cmdSeq, areaType,areaNO，
		//（车辆上料取料点请求/库区倒料取料点请求/库区倒料放料点请求）KEY_AreaStartX,KEY_AreaEndX,KEY_AreaStartY,KEY_AreaEndY,
		//（车辆上料放料点请求）KEY_PointX1，KEY_PointY1,KEY_PointZ1,KEY_PointX2，KEY_PointY2,KEY_PointZ2,KEY_PointX3，KEY_PointY3,KEY_PointZ3,KEY_PointX4，KEY_PointY4,KEY_PointZ4
		//KEY_MessageNo=1001  KEY_ActionType=0  ：车辆上料取料点请求
		//KEY_MessageNo=1001  KEY_ActionType=1  ：车辆上料放料点请求  : 这个比较特殊，传过来的字段比其它事件多
		//KEY_MessageNo=1003  KEY_ActionType=0  ：库区倒料取料点请求
		//KEY_MessageNo=1003  KEY_ActionType=1  ：库区倒料放料点请求	

		string scanMessageNO = "";
		string scanCraneNO = orderCurrent.getCraneNO();
		string scanActionType = "";
		string craneActX = StringHelper::ToString(cranePLCStatus.getXAct());
		string craneActY = StringHelper::ToString(cranePLCStatus.getYAct());
		string orderNO = StringHelper::ToString(orderCurrent.getOrderNO());
		string cmdSeq = StringHelper::ToString(orderCurrent.getCmdSeq());
		string areaType = "";//1-卸料区 2-料格 3-停车位
		string areaNO = "";

//------------------组织主要数据------------------------------------------------------------------

		//scanMessageNO
		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
			orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
		{
			scanMessageNO = "1001";
		}
		else if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			scanMessageNO = "1003";
		}

		//scanType
		if (cranePLCStatus.getHasCoil() == 0 && orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
		{
			scanActionType = "0";
		}
		else if (cranePLCStatus.getHasCoil() > 0 && orderCurrent.getCmdStatus() == OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS)
		{
			scanActionType = "1";
		}

		//areaType  areaNO
		if (scanMessageNO == "1001" && scanActionType == "0")//车辆上料取料点请求
		{
			areaType = "2";
			areaNO = orderCurrent.getFromStockNO();
		}
		else if (scanMessageNO == "1001" && scanActionType == "1")//车辆上料放料点请求
		{
			areaType = "3";
			areaNO = orderCurrent.getToStockNO();
		}
		else if (scanMessageNO == "1003" && scanActionType == "0" && orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)//库区倒料取料点请求
		{
			areaType = "2";
			areaNO = orderCurrent.getFromStockNO();
		}
		else if (scanMessageNO == "1003" && scanActionType == "1" && orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)//库区倒料放料点请求
		{
			areaType = "1";
			areaNO = orderCurrent.getToStockNO();
		}

		if (scanMessageNO.empty() || scanCraneNO.empty() || scanActionType.empty() || 
			craneActX.empty() || craneActY.empty() || orderNO.empty() || cmdSeq.empty() || areaType.empty() || areaNO.empty() )
		{
			log.Info()<<"UL01 tagvalue main data is miss,  return false..................."<<endl;
			ret = false;
			return ret;
		}

		tagValue = scanMessageNO + "," + scanCraneNO + "," + scanActionType + "," + craneActX + "," + craneActY + "," + orderNO + "," + cmdSeq + "," + areaType + "," + areaNO;

//---------------------组织次要数据-----------------------------------------
		long areaStartX = 0;
		long areaEndX = 0;
		long areaStartY = 0;
		long areaEndY = 0;

		if( (scanMessageNO == "1001" && scanActionType == "0") ||   
			 (scanMessageNO == "1003" && scanActionType == "0") || 
			 (scanMessageNO == "1003" && scanActionType == "1") )
		{
			Adapter_UACS_CRANE_ORDER_CURRENT::GetScanAreaXY(areaType, areaNO, areaStartX, areaEndX, areaStartY, areaEndY);

			if (areaStartX == 0 || areaEndX == 0 || areaStartY == 0 || areaEndY == 0 )
			{
				log.Info()<<"UL01 tagvalue secondary 1 data is miss,  return false..................."<<endl;
				ret = false;
				return ret;
			}
			string strAreaStartX = StringHelper::ToString(areaStartX);
			string strAreaEndX = StringHelper::ToString(areaEndX);
			string strAreaStartY = StringHelper::ToString(areaStartY);
			string strAreaEndY = StringHelper::ToString(areaEndY);

			tagValue += "," + strAreaStartX + "," + strAreaEndX + "," + strAreaStartY + "," + strAreaEndY;

			ret = true;
			return ret;
		}

		string carPointX1 = "";
		string carPointY1 = "";
		string carPointZ1 = "";
		string carPointX2 = "";
		string carPointY2 = "";
		string carPointZ2 = "";
		string carPointX3 = "";
		string carPointY3 = "";
		string carPointZ3 = "";
		string carPointX4 = "";
		string carPointY4 = "";
		string carPointZ4 = "";

		if( scanMessageNO == "1001" && scanActionType == "1")
		{
			vector<long> vecPoint;
			if ( false == Adapter_UACS_CRANE_ORDER_CURRENT::SelSRSCarInfo(orderCurrent.getCarScanNO(), vecPoint) )//注意！！！！这里的scanNO要修改的  
			{
				log.Info()<<"UL01 tagvalue secondary 2 data is miss,  return false..................."<<endl;
				ret = false;
				return ret;
			}

			carPointX1 = StringHelper::ToString(vecPoint[0]);
			carPointY1 = StringHelper::ToString(vecPoint[1]);
			carPointZ1 = StringHelper::ToString(vecPoint[2]);

			carPointX2 = StringHelper::ToString(vecPoint[3]);
			carPointY2 = StringHelper::ToString(vecPoint[4]);
			carPointZ2 = StringHelper::ToString(vecPoint[5]);

			carPointX3 = StringHelper::ToString(vecPoint[6]);
			carPointY3 = StringHelper::ToString(vecPoint[7]);
			carPointZ3 = StringHelper::ToString(vecPoint[8]);

			carPointX4 = StringHelper::ToString(vecPoint[9]);
			carPointY4 = StringHelper::ToString(vecPoint[10]);
			carPointZ4 = StringHelper::ToString(vecPoint[11]);

			tagValue += "," + carPointX1 + "," + carPointY1 + "," + carPointZ1 + "," + carPointX2 + "," + carPointY2 + "," + carPointZ2;
			tagValue += "," + carPointX3 + "," + carPointY3 + "," + carPointZ3 + "," + carPointX4 + "," + carPointY4 + "," + carPointZ4;

			ret = true;
			return ret;

		}
		return ret;

	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;
}


bool YardMapTracker::getUL02TagValue(OrderCurrentBase orderCurrent, string& tagValue)
{
	string functionName="YardMapTracker :: getUL02TagValue()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		//strValue格式：
		//KEY_CraneNo,KEY_MessageNo,KEY_ParkingNo,KEY_VehicleType,KEY_MaterialType,KEY_LoadFlag,KEY_ScanMode,KEY_StartP,KEY_EndP,KEY_ScanCount,KEY_LaserIP
		//orderNO

		string scanCraneNO = orderCurrent.getCraneNO();
		string scanMessageNO = "101";//车辆扫描 101
		string parkingNO = orderCurrent.getToStockNO();//装车时，目的库区就是停车位 应该可以的
		string vehicleType = "101";  //社会车辆-101   RGV-108
		string materialType = "12"; //暂定12
		string loadFlag = "0"; //空重拼标识 默认 0
		string scanMode = "2"; //扫描模式  0-云台  1-大车走行  2-小车走行  暂定2
		string startP = "";//扫描起始地址  一般为停车位起始结束
		string endP = ""; //扫描结束地址
		string scanCount = "1"; //扫描次数  默认1
		string laserIP = ""; //扫描仪IP  数据库表配置

		//组织数据

		//获取停车位定义数据
		long xStart = 0;
		long xEnd = 0;
		long yStart = 0;
		long yEnd = 0;

		Adapter_UACS_CRANE_ORDER_CURRENT::SelParkingInfoDefine(parkingNO, xStart, xEnd, yStart, yEnd);

		if (scanMode == "1")
		{
			startP = StringHelper::ToString(xStart);
			endP = StringHelper::ToString(xEnd);
		}
		if (scanMode == "2")
		{
			startP = StringHelper::ToString(yStart);
			endP = StringHelper::ToString(yEnd);
		}

		if (startP == "0" || endP == "0")
		{
			log.Info()<<"startP = 0 || endP = 0, return false..........................................."<<endl;
			ret = false;
			return ret;
		}

		//扫描仪IP读数据库表
		Adapter_UACS_CRANE_ORDER_CURRENT::SelCraneSrsIPConfig(scanCraneNO, laserIP);
		if (laserIP.empty())
		{
			log.Info()<<"laserIP  is  EMPTY, return false..........................................."<<endl;
			ret = false;
			return ret;
		}

		//数据具备，开始整理
		tagValue = scanCraneNO + "," + scanMessageNO + "," + parkingNO + "," + vehicleType + "," + materialType + "," + loadFlag + ",";
		tagValue += scanMode + "," + startP + "," + endP + "," + scanCount + "," + laserIP;

		ret = true;
		return ret;

	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;
}


bool YardMapTracker::notLeaveCenter(string moveDir, long startX, long endX, long startY, long endY, CranePLCStatusBase cranePLCStatus)
{
	string functionName="YardMapTracker :: notLeaveCenter()";
	LOG log(functionName, AUTO_CATCH_PID);
	bool ret = false;

	try
	{
		long moveCenterP = DB_INT_NULL;
		if (moveDir == "X")
		{
			moveCenterP = (startY + endY)/2;
			if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_Y_By_Distance(cranePLCStatus.getYAct(), moveCenterP, 500))
			{
				ret = true;
				return ret;
			}
		}
		if (moveDir == "Y")
		{
			moveCenterP = (startX + endX)/2;
			if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_X_By_Distance(cranePLCStatus.getXAct(), moveCenterP, 500))
			{
				ret = true;
				return ret;
			}			
		}
	}
	catch (std::exception& stdex)
	{
		string errorMessage=stdex.what();
		string msg=functionName +"   error:"+ errorMessage;
		log.Debug()<<msg<<endl;
	}
	catch (...)
	{
		string msg = functionName +"   error:";
		log.Debug()<<msg<<endl;
	}
	return ret;
}