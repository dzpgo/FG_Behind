#pragma  once
#include "Crane_Testing_Main.h"

using namespace Monitor;

Crane_Testing_Main::Crane_Testing_Main(void )
{

}

Crane_Testing_Main::~Crane_Testing_Main(void )
{

}

bool  Crane_Testing_Main::Test_AfterRolling(string craneNO, CranePLCStatusBase cranePLCStatusBase )
{

	bool ret=false;

	string functionName="Crane_Testing_Main :: Test_AfterRolling()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		OrderCurrentBase orderCurrent;
		orderCurrent = Adapter_UACS_CRANE_ORDER_CURRENT::getData(craneNO);


		if( (	orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY ||
			orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_ORDER_INIT ||
			orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS ||
			orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS )
			==false)
		{
			log.Debug()<<"��ǰָ��״̬��CMD_STATUS��UACS_CRANE_ORDER_CURRENT���У�δ���壡����false��"<<endl;
			ret=false;
			return ret;
		}

		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			log.Debug()<<"��ǰָ��״̬��CMD_STATUS��UACS_CRANE_ORDER_CURRENT���У�=EMPTY������false��"<<endl;
			ret=false;
			return ret;
		}

		if(orderCurrent.getCmdStatus()==CraneOrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_ORDER_INIT)
		{
			log.Debug()<<"��ǰָ��״̬��CMD_STATUS��UACS_CRANE_ORDER_CURRENT���У�=INIT������false��"<<endl;
			ret=false;
			return ret;
		}

		if(ACTION_COMMON_FUNCTION::CustomOffice_Is_Auto_Ready_AskPlan(craneNO,cranePLCStatusBase)==false)
		{
			ret=false;
			return ret;
		}

//------------------------------------------------�����г��߼�------------------------------------------------------------------------------------------------------------

		if ( craneNO == "1"  ||  craneNO == "2" || craneNO == "3" || craneNO == "4")
		{
			if (craneNO == "1" )
			{
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
				log.Info()<<"                                                                                       ��¯�ϸֶѳ�-------1#�г�                                                                                                               " <<endl; 
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
			}
			else if (craneNO == "2")
			{
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
				log.Info()<<"                                                                                       ��¯�ϸֶѳ�-------2#�г�                                                                                                               " <<endl; 
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
			}
			else if (craneNO == "3")
			{
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
				log.Info()<<"                                                                                       ��¯�ϸֶѳ�-------3#�г�                                                                                                               " <<endl; 
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
			}
			else if (craneNO == "4")
			{
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
				log.Info()<<"                                                                                       ��¯�ϸֶѳ�-------4#�г�                                                                                                                " <<endl; 
				log.Info()<<"*******************************************************************************************************************************************"<<endl; 
			}

			if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				log.Info()<<"1-------L3�ƻ��������ж��ָ�------"<<endl;
				Test_L3_Car_To_Yard::Test(craneNO, orderCurrent, cranePLCStatusBase);
				return true;
			}



			log.Debug()<<"��ƥ��ָ�.............................................."<<endl;
			//2018.7.12 zhangyuhong add
			//���ӱ������빦��
			ACTION_COMMON_FUNCTION::SetTagValue(craneNO, 
																							   ACTION_COMMON_FUNCTION::TAGNAME_WMS_CRANE_ALARM_CODE_ADDRESS, 
																							   ACTION_COMMON_FUNCTION::WMS_CRANE_ALARM_CODE_8004);

		}	

		//====================================================================================================
		//====================================================================================================

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