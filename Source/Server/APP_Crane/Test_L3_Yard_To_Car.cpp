#pragma once
#include "Test_L3_Yard_To_Car.h"

using namespace Monitor;

Test_L3_Yard_To_Car::Test_L3_Yard_To_Car(void )
{

}

Test_L3_Yard_To_Car::~Test_L3_Yard_To_Car(void )
{

}

bool Test_L3_Yard_To_Car::Test(string craneNO, OrderCurrentBase orderCurrent ,CranePLCStatusBase cranePLCStatusBase)
{

	bool ret=false;

	string functionName="Test_L3_Yard_To_Car::Test";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//上半关=================================================================

		//1. 是否发送过取料点激光扫描请求
		//2. 起始料堆激光扫描结果是否成功
		//3. 移动到取料点
		//4. 取料
		//5. 结束工作

		if(	orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
		{
			string actions="";

			actions += "ACTION_GRID_INFO_CHECK,";
			actions += "ACTION_CAR_SCAN_IS_OK,";
			actions += "ACTION_UP_POS_IS_OK,";
			actions += "ACTION_MOVE_TO_UP_POS,";
			actions += "ACTION_MAT_UP,";
			actions += "ACTION_FINISH_JOB";

			ACTION_COMMON_FUNCTION::Action_OutPut_Actions(craneNO, actions);
			string actionsSuccessed="";

			//action:ACTION_CHECK_COIL_POS
			if(ACTION_GRID_INFO_CHECK::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}else {actionsSuccessed=actionsSuccessed+"ACTION_GRID_INFO_CHECK"+",";  ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }

			//action
			if(ACTION_CAR_SCAN_IS_OK::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}	else {actionsSuccessed=actionsSuccessed+"ACTION_CAR_SCAN_IS_OK"+",";  	ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }
			
			//action
			if(ACTION_UP_POS_IS_OK::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}	else {actionsSuccessed=actionsSuccessed+"ACTION_UP_POS_IS_OK"+",";  	ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }

			//action
			if(ACTION_MOVE_TO_UP_POS::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}else {actionsSuccessed=actionsSuccessed+"ACTION_MOVE_TO_UP_POS"+","; ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }

			//action
			if(ACTION_MAT_UP::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}else {actionsSuccessed=actionsSuccessed+"ACTION_MAT_UP"+","; ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }

			//action
			if(ACTION_FINISH_JOB::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}else {actionsSuccessed=actionsSuccessed+"ACTION_FINISH_JOB"+","; ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }

			return true;
		}

		//=======================第二步：行车重钩运行到落卷位置所在鞍座库位并落卷====================================


		//1. 是否发送过放料点激光扫描请求
		//2. 目的料堆激光扫描结果是否成功
		//3. 移动到放料点
		//4. 放料
		//5. 结束工作
		if(orderCurrent.getCmdStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS)
		{
			string actions="";

			actions += "ACTION_GRID_INFO_CHECK,";
			actions += "ACTION_DOWN_POS_IS_OK,";
			actions += "ACTION_MOVE_TO_DOWN_POS,";
			actions += "ACTION_MAT_DOWN,";
			actions += "ACTION_FINISH_JOB";

			ACTION_COMMON_FUNCTION::Action_OutPut_Actions(craneNO, actions);
			string actionsSuccessed="";

			//action
			if(ACTION_GRID_INFO_CHECK::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}	else {actionsSuccessed=actionsSuccessed+"ACTION_GRID_INFO_CHECK"+",";  	ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }

			//action
			if(ACTION_DOWN_POS_IS_OK::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}	else {actionsSuccessed=actionsSuccessed+"ACTION_DOWN_POS_IS_OK"+",";  	ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed); }

			//action
			if(ACTION_MOVE_TO_DOWN_POS::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}else {actionsSuccessed=actionsSuccessed+"ACTION_MOVE_TO_DOWN_POS"+","; ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed);}

			//action
			if(ACTION_MAT_DOWN::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}else {actionsSuccessed=actionsSuccessed+"ACTION_MAT_DOWN"+","; ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed);}

			//action
			if(ACTION_FINISH_JOB::doAction(craneNO, orderCurrent.getBayNO(), orderCurrent, cranePLCStatusBase)==false){return false;}else {actionsSuccessed=actionsSuccessed+"ACTION_FINISH_JOB"+","; ACTION_COMMON_FUNCTION::Action_OutPut_ActionsSuccessed(craneNO, actionsSuccessed);}

			return true;

		}




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



