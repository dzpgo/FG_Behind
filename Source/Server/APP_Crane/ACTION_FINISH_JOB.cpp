#include "ACTION_FINISH_JOB.h"

using namespace Monitor;

ACTION_FINISH_JOB :: ACTION_FINISH_JOB(void)
{
}



ACTION_FINISH_JOB :: ~ACTION_FINISH_JOB(void)
{
}



//1 doAction
bool ACTION_FINISH_JOB :: doAction(string craneNO, 
																   string bayNO,
																   OrderCurrentBase orderCurrent, 
																   CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_FINISH_JOB :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_FINISH_JOB------------------------ ------------------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		//2017.9.20  zhangyuhong  add
		//读取避让的指令
		CraneEvadeRequestBase  craneEvadeRequestBase;
		Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);

		//再确认有无避让指令  初始化  等着做 正在做  就是实实在在存在的
		bool hasEvadeRequest=false;
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
		{
			hasEvadeRequest=true;
		}
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_TO_DO)
		{
			hasEvadeRequest=true;
		}
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_EXCUTING)
		{
			hasEvadeRequest=true;
		}

		//重钩 finish
		if(cranePLCStatus.getHasCoil() > 0)
		{
			log.Debug()<<"当前行车已经有卷重载，CoilUp动作完成，修改指令状态CMDStatus=COIL_DOWN...."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::update_CMDStatus(craneNO,CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS);

			//20220725 zhangyuhong add
			//更新取料点扫描号=NULL，取料点planUpXYZ = 999999
			Adapter_UACS_CRANE_ORDER_CURRENT::InitPlanUpXYZMatUpScanNO(craneNO);

			//起吊阶段完成了，如果有预先收到的避让指令，并且避让指令没有放开，并且避让指令类型是立即，那么放开它
			if(true == hasEvadeRequest  && craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
			{
				if( craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_RIGHT_NOW)
				{
					Adapter_UACS_CRANE_EVADE_REQUEST::UpdateStatus(craneNO,  CraneEvadeRequestBase::STATUS_TO_DO);
				}
			}
		}

		//空钩finish
		else if(cranePLCStatus.getHasCoil()==0)
		{
			log.Debug()<<"当前行车已经无卷空载，CoilDown动作完成，.........................."<<endl;

			//20220725 zhangyuhong add
			//更新放料点扫描号=NULL，放料点planUpXYZ = 999999
			Adapter_UACS_CRANE_ORDER_CURRENT::InitPlanDownXYZMatDownScanNO(craneNO);

			//针对指令类型
			if ( true == ACTION_COMMON_FUNCTION::CoilDownIsOverInFinishJob(cranePLCStatus, orderCurrent) )
			{
				//清空指令
				Adapter_UACS_CRANE_ORDER_CURRENT::initialise(craneNO);
				Adapter_UACS_CRANE_ORDER_CURRENT::update_CMDStatus(craneNO,CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY);
			}
			else
			{
				//coilDownprocess->coilUpprocess       cmdSeq = cmdSeq + 1
				Adapter_UACS_CRANE_ORDER_CURRENT::update_CMDStatus(craneNO,CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS);
				Adapter_UACS_CRANE_ORDER_CURRENT::Update_CmdSeq_Add_1(craneNO);

			}


			//Adapter_UACS_CRANE_ORDER_CURRENT::initialise(craneNO);
			//Adapter_UACS_CRANE_ORDER_CURRENT::update_CMDStatus(craneNO,CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY);

			//整关阶段完成了，如果有预先收到的避让指令，并且避让指令没有放开，那么放开它
			if(true == hasEvadeRequest  && craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
			{
				Adapter_UACS_CRANE_EVADE_REQUEST::UpdateStatus(craneNO,  CraneEvadeRequestBase::STATUS_TO_DO);
			}
		}

		ret=true;
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


