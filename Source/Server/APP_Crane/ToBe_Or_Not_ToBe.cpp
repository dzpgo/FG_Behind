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
		//*				1����ȡ����ָ���
		//*
		//*****************************************************************************************************
		bool hasEvadeRequest=false;
		CraneEvadeRequestBase  craneEvadeRequestBase;
		Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);

		//INIT�����б���ָ��
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
		{
					hasEvadeRequest=true;
		}

		//TO_DO�����б���ָ��
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_TO_DO)
		{
					hasEvadeRequest=true;
		}

		//EXCUTING�����б���ָ��
		if(craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_EXCUTING)
		{
					hasEvadeRequest=true;
		}


		//*****************************************************************************************************
		//*
		//*				2����ȡWMSָ���
		//*
		//*****************************************************************************************************
		bool hasWMSOrder=false;
		OrderCurrentBase craneOrderCurrent;
		craneOrderCurrent=Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);

		//COIL_UP_PROCESS ������WMSָ��
		if(craneOrderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS)
		{
					hasWMSOrder=true;
		}

		//COIL_DOWN_PROCESS ������WMSָ��
		if(craneOrderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS)
		{
					hasWMSOrder=true;
		}

		//*****************************************************************************************************
		//*
		//*				3�������⹤�����Ͻ����г�����ActionType�������������������ٴӱ��ж�����ָ��
		//*
		//******************************************************************************************************************
		//*				3.1 �����ǰ�г�ʱ4-6����WMSָ���PA2���ϣ��չ�����4-7��PA2���ϣ���4-6��������Ϊ RIGHT_NOW
		//******************************************************************************************************************
		if (true == UpgradeActionType_4_6::tryUpdate(craneNO,cranePLCStatus, craneOrderCurrent, craneEvadeRequestBase))
		{
			//read it again
			Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
		}

		//******************************************************************************************************************
		//*				3.2 �����ǰ�г�ʱ4-5���Է��г�4-6�Ǹ�C175  176���ϣ���4-5��������Ϊ RIGHT_NOW
		//******************************************************************************************************************
		if (true == UpgradeActionType_4_5::tryUpdate(craneNO,cranePLCStatus, craneOrderCurrent, craneEvadeRequestBase))
		{
			//read it again
			Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
		}

		//******************************************************************************************************************
		//*				3.3   4-4�г��ı���ָ��������RIGHT_NOW
		//******************************************************************************************************************
		if (true == UpgradeActionType_4_4::tryUpdate(craneNO,cranePLCStatus, craneOrderCurrent, craneEvadeRequestBase))
		{
			//read it again
			Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);
		}

		//*****************************************************************************************************
		//*
		//*				4������ActionType������ֵ����Status����������TO_DO
		//*
		//*****************************************************************************************************

		//*****************************************************************************************************
		//*
		//*				4.1  ������ִ��(TYPE_RIGHT_NOW)�ı���ָ�״̬��INIT���������� ����ΪTODO
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
		//*				4.2  ��WMSָ�������£����غ�ִ��(TYPE_AFTER_JOB)�ı���ָ�״̬��INIT��������TODO
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
		//*				5  ����ָ��Status=STATUS_TO_DO����STATUS_EXCUTINGʱ��������ָ���������
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
			//*				5.1  ����ָ��Status=STATUS_TO_DO����STATUS_EXCUTINGʱ��������ָ��
			//*
			//*****************************************************************************************************
			choise= ToBe_Or_Not_ToBe::CHOISE_DO_EVADE;

			//*****************************************************************************************************
			//*
			//*				5.2  ��������1��4-6�о������£�����Ǵ�С��A1_X_MIN��λ�� ���� ����A1_X_MIN���������ã�����WMS
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
			//*				5.6  �ձ�����1�������ع����Ѿ��������λ�õ���������ٱ��ã�ִ��WMSָ��
			//*
			//*****************************************************************************************************
			//2018.10.23 zhangyuhong add
			//������ֻҪ���о�λ������WMSָ��
			//if(EvadeException_Normal_ArrivedDownPos::satifyException(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			if(EvadeException_Normal_ArrivedDownPos::satifyExceptionHasCoilWhenXOK(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}

			//*****************************************************************************************************
			//*
			//*				5.6  �ձ�����1�����ڿչ����Ѿ��������λ�õ���������ٱ��ã�ִ��WMSָ��
			//*
			//*****************************************************************************************************
			//2018.10.23 zhangyuhong add
			//������ֻҪ���о�λ������WMSָ��
			//if(EvadeException_Normal_ArrivedDownPos::satifyException(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			if(EvadeException_Normal_ArrivedDownPos::satifyExceptionHasNoCoilWhenXOK(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}

			//*****************************************************************************************************
			//*
			//*				5.7  �ձ�����2�����ڱ������ڱ��÷������ߵĸ���Զ����������ٱ��ã�ִ��WMSָ��
			//*
			//*****************************************************************************************************
			//�ձ����У����ڱ������ڱ��÷������ߵĸ���Զ�����
			if(EvadeException_Normal_I_Will_Leave::satifyException(craneNO , cranePLCStatus , craneOrderCurrent , craneEvadeRequestBase) ) 
			{
				choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
				return choise;
			}
			return choise;
		}

		//*****************************************************************************************************
		//*
		//*				6  �ޱ���ָ���WMSָ���ִ��WMSָ��
		//*
		//*****************************************************************************************************
		if(hasEvadeRequest==false && hasWMSOrder==true)
		{
			choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
			return choise;
		}

		//*****************************************************************************************************
		//*
		//*				7  �б���ָ���δ��ִ����TO_DO/EXCUTING����ִ��WMSָ��
		//*
		//*****************************************************************************************************
		if(hasEvadeRequest==true && evade_TODO_Excuting==false && hasWMSOrder==true)
		{
			choise= ToBe_Or_Not_ToBe::CHOISE_DO_WMSORDER;
			return choise;
		}

		//*****************************************************************************************************
		//*
		//*				8  �ޱ���ָ���WMSָ����г�ʲôҲ����
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
