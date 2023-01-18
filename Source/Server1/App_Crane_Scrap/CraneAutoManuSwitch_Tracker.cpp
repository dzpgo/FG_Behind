#include "CraneAutoManuSwitch_Tracker.h"

#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"

#include "Adapter_UACS_CRANE_MOVEORDER_MSG.h"




using namespace iPlature;


CraneAutoManuSwitch_Tracker::CraneAutoManuSwitch_Tracker( )
{
    
	CraneMonitor::getInstance()->getPLCStatus(cranePLCStatus_Last);

}


void  CraneAutoManuSwitch_Tracker::Track_AutoManuSwitch( )
{

	string functionName="CraneAutoManuSwitch_Tracker :: Track_AutoManuSwitch()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		//get  new PLCStatus
		CraneMonitor::getInstance()->getPLCStatus(cranePLCStatus_Current);

		//2018.7.23 zhangyuhong add
		//当时自动模式时，记录行车当前指令表里的数据
		if (cranePLCStatus_Current.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			craneOrderCurrentLastAuto = Adapter_UACS_CRANE_ORDER_CURRENT::getData(cranePLCStatus_Current.getCraneNO());
			log.Info()<<"craneOrderCurrentLastAuto.getOrderNO() = "<<craneOrderCurrentLastAuto.getOrderNO()<<endl;
		}

		// 行车自动控制模式丢失
		if( cranePLCStatus_Last.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO &&  cranePLCStatus_Current.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Debug()<<"行车 ：自动------>非自动！"<<endl;

			
			string tagCraneAlarmCode = ACTION_COMMON_FUNCTION::GetTagValue(cranePLCStatus_Current.getCraneNO(), ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS);
			long craneAlarmCode = StringHelper::ToNumber<long>(tagCraneAlarmCode);
			
			
			//自动模式丢失时，写入 UACS_CRANE_ALARM_HIS，以记录行车PLC 自动 突变 手动的记录
			//4--自动    2--手动
			Adapter_UACS_CRANE_MOVEORDER_MSG::insertCraneAutoManuSwitch(cranePLCStatus_Current.getCraneNO(), "AUTO", "MANU");

			//取消本车的所有避让要求，不在有领土要求了
			EvadeCancelSender::senderByManuAutoSwitch(cranePLCStatus_Current.getCraneNO());
			//本车的避让发送器reset
			EvadeRequestSender::getInstance()->reset();

			//清空避让指令表指令
			Adapter_UACS_CRANE_EVADE_REQUEST::Init(cranePLCStatus_Current.getCraneNO());
		
			
		}
		
		//行车自动控制模式获得
		if( cranePLCStatus_Last.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO &&  cranePLCStatus_Current.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO)
		{			
			//非自动切自动，将报警清掉
			ACTION_COMMON_FUNCTION::SetTagValue(cranePLCStatus_Current.getCraneNO(), 
																								ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS, 
																								ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_0);

			//自动模式恢复时，写入 UACS_CRANE_ALARM_HIS，以记录行车PLC 自动 突变 手动，又突变回自动的记录
			//4--自动    2--手动
			Adapter_UACS_CRANE_MOVEORDER_MSG::insertCraneAutoManuSwitch(cranePLCStatus_Current.getCraneNO(), "MANU", "AUTO");
		}


		//copy the current photo to the old ph
		cranePLCStatus_Last=cranePLCStatus_Current;
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


