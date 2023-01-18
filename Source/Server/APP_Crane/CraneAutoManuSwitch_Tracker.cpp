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
		//��ʱ�Զ�ģʽʱ����¼�г���ǰָ����������
		if (cranePLCStatus_Current.getControlMode() == CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			craneOrderCurrentLastAuto = Adapter_UACS_CRANE_ORDER_CURRENT::getData(cranePLCStatus_Current.getCraneNO());
			log.Info()<<"craneOrderCurrentLastAuto.getOrderNO() = "<<craneOrderCurrentLastAuto.getOrderNO()<<endl;
		}

		// �г��Զ�����ģʽ��ʧ
		if( cranePLCStatus_Last.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO &&  cranePLCStatus_Current.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO)
		{
			log.Debug()<<"�г� ���Զ�------>���Զ���"<<endl;

			
			string tagCraneAlarmCode = ACTION_COMMON_FUNCTION::GetTagValue(cranePLCStatus_Current.getCraneNO(), ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS);
			long craneAlarmCode = StringHelper::ToNumber<long>(tagCraneAlarmCode);
			
			
			//�Զ�ģʽ��ʧʱ��д�� UACS_CRANE_ALARM_HIS���Լ�¼�г�PLC �Զ� ͻ�� �ֶ��ļ�¼
			//4--�Զ�    2--�ֶ�
			Adapter_UACS_CRANE_MOVEORDER_MSG::insertCraneAutoManuSwitch(cranePLCStatus_Current.getCraneNO(), "AUTO", "MANU");

			//ȡ�����������б���Ҫ�󣬲���������Ҫ����
			EvadeCancelSender::senderByManuAutoSwitch(cranePLCStatus_Current.getCraneNO());
			//�����ı��÷�����reset
			EvadeRequestSender::getInstance()->reset();

			//��ձ���ָ���ָ��
			Adapter_UACS_CRANE_EVADE_REQUEST::Init(cranePLCStatus_Current.getCraneNO());
		
			
		}
		
		//�г��Զ�����ģʽ���
		if( cranePLCStatus_Last.getControlMode()!=CranePLCStatusBase::CONTROL_MODE_AUTO &&  cranePLCStatus_Current.getControlMode()==CranePLCStatusBase::CONTROL_MODE_AUTO)
		{			
			//���Զ����Զ������������
			ACTION_COMMON_FUNCTION::SetTagValue(cranePLCStatus_Current.getCraneNO(), 
																								ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS, 
																								ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_0);

			//�Զ�ģʽ�ָ�ʱ��д�� UACS_CRANE_ALARM_HIS���Լ�¼�г�PLC �Զ� ͻ�� �ֶ�����ͻ����Զ��ļ�¼
			//4--�Զ�    2--�ֶ�
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


