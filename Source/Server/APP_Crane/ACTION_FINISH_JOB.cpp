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
		//��ȡ���õ�ָ��
		CraneEvadeRequestBase  craneEvadeRequestBase;
		Adapter_UACS_CRANE_EVADE_REQUEST::GetData(craneNO,craneEvadeRequestBase);

		//��ȷ�����ޱ���ָ��  ��ʼ��  ������ ������  ����ʵʵ���ڴ��ڵ�
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

		//�ع� finish
		if(cranePLCStatus.getHasCoil() > 0)
		{
			log.Debug()<<"��ǰ�г��Ѿ��о����أ�CoilUp������ɣ��޸�ָ��״̬CMDStatus=COIL_DOWN...."<<endl;
			Adapter_UACS_CRANE_ORDER_CURRENT::update_CMDStatus(craneNO,CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS);

			//20220725 zhangyuhong add
			//����ȡ�ϵ�ɨ���=NULL��ȡ�ϵ�planUpXYZ = 999999
			Adapter_UACS_CRANE_ORDER_CURRENT::InitPlanUpXYZMatUpScanNO(craneNO);

			//����׶�����ˣ������Ԥ���յ��ı���ָ����ұ���ָ��û�зſ������ұ���ָ����������������ô�ſ���
			if(true == hasEvadeRequest  && craneEvadeRequestBase.getStatus()==CraneEvadeRequestBase::STATUS_INIT)
			{
				if( craneEvadeRequestBase.getEvadeActionType()==CraneEvadeRequestBase::TYPE_RIGHT_NOW)
				{
					Adapter_UACS_CRANE_EVADE_REQUEST::UpdateStatus(craneNO,  CraneEvadeRequestBase::STATUS_TO_DO);
				}
			}
		}

		//�չ�finish
		else if(cranePLCStatus.getHasCoil()==0)
		{
			log.Debug()<<"��ǰ�г��Ѿ��޾���أ�CoilDown������ɣ�.........................."<<endl;

			//20220725 zhangyuhong add
			//���·��ϵ�ɨ���=NULL�����ϵ�planUpXYZ = 999999
			Adapter_UACS_CRANE_ORDER_CURRENT::InitPlanDownXYZMatDownScanNO(craneNO);

			//���ָ������
			if ( true == ACTION_COMMON_FUNCTION::CoilDownIsOverInFinishJob(cranePLCStatus, orderCurrent) )
			{
				//���ָ��
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

			//���ؽ׶�����ˣ������Ԥ���յ��ı���ָ����ұ���ָ��û�зſ�����ô�ſ���
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


