#include "ToBe_Or_Not_ToBe.h"

using namespace Monitor;

const string  ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER="DO_WMSORDER";
const string  ToBe_Or_Not_ToBe::CHOISE_DO_EVADE="DO_EVADE";
const string  ToBe_Or_Not_ToBe::CHOISE_NOTHING_TODO="NOTHING_TODO";

ToBe_Or_Not_ToBe :: ToBe_Or_Not_ToBe(void)
{
}



ToBe_Or_Not_ToBe :: ~ToBe_Or_Not_ToBe(void)
{
}



//1 doAction
string ToBe_Or_Not_ToBe :: choose(string craneNO, CranePLCStatusBase cranePLCStatus)
{
	string choise= ToBe_Or_Not_ToBe::CHOISE_NOTHING_TODO;

	string functionName="ToBe_Or_Not_ToBe :: choose()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		//*****************************************************************************************************
		//*
		//*				1、读取避让指令表
		//*
		//*****************************************************************************************************
		bool hasEvadeRequest=false;
		CraneEvadeRequestBase  craneEvadeRequestBase;
		Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);

		//INIT属于有避让指令
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
		{
					hasEvadeRequest=true;
		}

		//TO_DO属于有避让指令
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_TO_DO)
		{
					hasEvadeRequest=true;
		}

		//EXCUTING属于有避让指令
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_EXCUTING)
		{
					hasEvadeRequest=true;
		}


		//*****************************************************************************************************
		//*
		//*				2、读取WMS指令表
		//*
		//*****************************************************************************************************
		bool hasWMSOrder=false;
		OrderCurrentBase craneOrderCurrent;
		craneOrderCurrent=Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

		//COIL_UP_PROCESS 属于有WMS指令
		if(craneOrderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
		{
					hasWMSOrder=true;
		}

		//COIL_DOWN_PROCESS 属于有WMS指令
		if(craneOrderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS)
		{
					hasWMSOrder=true;
		}

		//*****************************************************************************************************
		//*
		//*				3、对特殊工况场合进行行车避让ActionType的升级，升级后，重新再从表中读避让指令
		//*
		//******************************************************************************************************************
		//*				3.1 如果当前行车时4-6，其WMS指令不是PA2收料，空钩，且4-7是PA2收料，则4-6立即升级为 RIGHT_NOW
		//******************************************************************************************************************
		if (true == UpgradeActionType_4_6::tryUpdate(craneNO,cranePLCStatus, craneOrderCurrent, craneEvadeRequestBase))
		{
			//read it again
			Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
		}

		//******************************************************************************************************************
		//*				3.2 如果当前行车时4-5，对方行车4-6是给C175  176上料，则4-5立即升级为 RIGHT_NOW
		//******************************************************************************************************************
		if (true == UpgradeActionType_4_5::tryUpdate(craneNO,cranePLCStatus, craneOrderCurrent, craneEvadeRequestBase))
		{
			//read it again
			Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
		}

		//******************************************************************************************************************
		//*				3.3   4-4行车的避让指令升级到RIGHT_NOW
		//******************************************************************************************************************
		if (true == UpgradeActionType_4_4::tryUpdate(craneNO,cranePLCStatus, craneOrderCurrent, craneEvadeRequestBase))
		{
			//read it again
			Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
		}

		//*****************************************************************************************************
		//*
		//*				4、根据ActionType的类型值，对Status进行升级：TO_DO
		//*
		//*****************************************************************************************************

		//*****************************************************************************************************
		//*
		//*				4.1  将立即执行(TYPE_RIGHT_NOW)的避让指令（状态是INIT）进行升级 升级为TODO
		//*
		//*****************************************************************************************************
		if(craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_RIGHT_NOW)
		{
			if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
			{
				Adapter_UACS_CRANE_EVADE_REQUEST::UpdateStatus(craneNO,  CraneEvadeRequestBase::STATUS_TO_DO);
				//read it again
				Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
			}
		}

		//*****************************************************************************************************
		//*
		//*				4.2  无WMS指令的情况下，将关后执行(TYPE_AFTER_JOB)的避让指令（状态是INIT）升级到TODO
		//*
		//*****************************************************************************************************
		if( hasWMSOrder==false &&  craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_AFTER_JOB)
		{
			if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
			{
				Adapter_UACS_CRANE_EVADE_REQUEST::UpdateStatus(craneNO,  CraneEvadeRequestBase::STATUS_TO_DO);
				//read it again
				Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
			}
		}

		
		//*****************************************************************************************************
		//*
		//*				5  避让指令Status=STATUS_TO_DO或者STATUS_EXCUTING时，做避让指令，但有特例
		//*
		//*****************************************************************************************************
		bool evade_TODO_Excuting=false;
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_TO_DO)
		{
			evade_TODO_Excuting=true;
		}
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_EXCUTING)
		{
			evade_TODO_Excuting=true;
		}

		if( hasEvadeRequest==true && evade_TODO_Excuting == true )
		{
			//*****************************************************************************************************
			//*
			//*				5.1  避让指令Status=STATUS_TO_DO或者STATUS_EXCUTING时，做避让指令
			//*
			//*****************************************************************************************************
			choise= ToBe_Or_Not_ToBe::CHOISE_DO_EVADE;

			//*****************************************************************************************************
			//*
			//*				5.2  定制特例1：4-6有卷的情况下，如果是从小于A1_X_MIN的位置 避让 超过A1_X_MIN，则不做避让，先做WMS
			//*
			//*****************************************************************************************************
			if( EvadeException_4_6::satifyException(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}
			if (EvadeException_4_5::satifyException(craneNO, cranePLCStatus, craneOrderCurrent, craneEvadeRequestBase) )
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}

			//*****************************************************************************************************
			//*
			//*				5.6  普遍特例1：对于重钩大车已经到达落卷位置的情况，不再避让，执行WMS指令
			//*
			//*****************************************************************************************************
			//2018.10.23 zhangyuhong add
			//修正：只要大车有卷到位就先做WMS指令
			//if(EvadeException_Normal_ArrivedDownPos::satifyException(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			if(EvadeException_Normal_ArrivedDownPos::satifyExceptionHasCoilWhenXOK(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}

			//*****************************************************************************************************
			//*
			//*				5.6  普遍特例1：对于空钩大车已经到达起卷位置的情况，不再避让，执行WMS指令
			//*
			//*****************************************************************************************************
			//2018.10.23 zhangyuhong add
			//修正：只要大车有卷到位就先做WMS指令
			//if(EvadeException_Normal_ArrivedDownPos::satifyException(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			if(EvadeException_Normal_ArrivedDownPos::satifyExceptionHasNoCoilWhenXOK(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}

			//*****************************************************************************************************
			//*
			//*				5.7  普遍特例2：对于本车会在避让方向上走的更加远的情况，不再避让，执行WMS指令
			//*
			//*****************************************************************************************************
			//普遍特列，对于本车会在避让方向上走的更加远的情况
			if(EvadeException_Normal_I_Will_Leave::satifyException(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}
			return choise;
		}

		//*****************************************************************************************************
		//*
		//*				6  无避让指令，有WMS指令，则执行WMS指令
		//*
		//*****************************************************************************************************
		if(hasEvadeRequest==false && hasWMSOrder==true)
		{
			choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
			return choise;
		}

		//*****************************************************************************************************
		//*
		//*				7  有避让指令，但未在执行中TO_DO/EXCUTING，则执行WMS指令
		//*
		//*****************************************************************************************************
		if(hasEvadeRequest==true && evade_TODO_Excuting==false && hasWMSOrder==true)
		{
			choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
			return choise;
		}

		//*****************************************************************************************************
		//*
		//*				8  无避让指令，无WMS指令，则行车什么也不做
		//*
		//*****************************************************************************************************
		if(hasEvadeRequest==false &&  hasWMSOrder==false)
		{
			choise= ToBe_Or_Not_ToBe::CHOISE_NOTHING_TODO;
			return choise;
		}
		return choise;
	}
	catch(iDA::Exception &x)
	{
		try
		{
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
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return choise;
}
