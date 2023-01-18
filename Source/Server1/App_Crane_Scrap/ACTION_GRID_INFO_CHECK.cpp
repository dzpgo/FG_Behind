#include "ACTION_GRID_INFO_CHECK.h"

using namespace Monitor;

ACTION_GRID_INFO_CHECK :: ACTION_GRID_INFO_CHECK(void)
{
}



ACTION_GRID_INFO_CHECK :: ~ACTION_GRID_INFO_CHECK(void)
{
}



//1 doAction
bool ACTION_GRID_INFO_CHECK :: doAction(string craneNO, 
																				 string bayNO,
																				 OrderCurrentBase orderCurrent, 
																				 CranePLCStatusBase cranePLCStatus)	
{
	bool ret=false;

	string functionName="ACTION_GRID_INFO_CHECK :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_GRID_INFO_CHECK----------------------- -----------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( ! ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getCmdStatus()"<<orderCurrent.getCmdStatus()<<endl;
		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;

		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && cranePLCStatus.getHasCoil() > 0)
		{
			log.Debug()<<"�г���ǰָ������CoilUp״̬�����г�hascoil > 0������true��"<<endl;
			ret=true;
			return ret;
		}

		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS && cranePLCStatus.getHasCoil() == 0)
		{
			log.Debug()<<"�г���ǰָ������CoilDown״̬�����г�hascoil == 0������true��"<<endl;
			ret=true;
			return ret;
		}

		//ֻ����ϸ���ȡ�� �� �ϸ��ڷ��� �Ƿ�����ϸ�����зŵ����ϴ���
		bool actionUp = (orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_UP_PROCESS && cranePLCStatus.getHasCoil() == 0);
		bool yardToCarOrderType = ( orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
															  orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 );

		bool actionDown = (orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS && cranePLCStatus.getHasCoil() > 0);
		bool carToYardOrderType = ( orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11 );


		if ( actionUp == true && carToYardOrderType == true)
		{
			log.Info()<<"actionUp and carToYardOrderType �� NO CHECK, return true...................................."<<endl;
			ret = true;
			return ret;
		}

		if ( actionDown == true && yardToCarOrderType == true)
		{
			log.Info()<<"actionDown and yardToCarOrderType �� NO CHECK, return true...................................."<<endl;
			ret = true;
			return ret;
		}


		if ( actionUp == true && yardToCarOrderType == true )
		{
			log.Info()<<"actionUp and yardToCarOrderType...................................."<<endl;
			//���ȡ�ϵ��ϸ�
			string matCode = "";
			string compCode = "";
			if (false == Adapter_UACS_YARDMAP_STOCK_INFO::SelMatCompCodeFromGridInfo(orderCurrent.getFromStockNO(), matCode, compCode))
			{
				log.Debug()<<"No MAT_NO, COMP_NO Data in UACS_YARDMAP_GRID_INO ������false��"<<endl;
				ret = false;
				return ret;
			}
			if ( matCode == orderCurrent.getMatCode() && compCode == orderCurrent.getCompCode() )
			{
				log.Debug()<<"ACTION_GRID_INFO_CHECK  is OK ������true��"<<endl;
				ret = true;
				return ret;
			}
			log.Debug()<<"ACTION_GRID_INFO_CHECK  is FAILED ������false��"<<endl;
			ret = false;
			return ret;
		}

		////////
		
		if ( actionDown == true && carToYardOrderType == true )
		{
			log.Info()<<"actionDown and carToYardOrderType...................................."<<endl;
			//�����ϵ��ϸ�
			string matCode = "";
			string compCode = "";
			if (false == Adapter_UACS_YARDMAP_STOCK_INFO::SelMatCompCodeFromGridInfo(orderCurrent.getToStockNO(), matCode, compCode))
			{
				log.Debug()<<"No MAT_NO, COMP_NO Data in UACS_YARDMAP_GRID_INO ������false��"<<endl;
				ret = false;
				return ret;
			}
			if ( matCode == orderCurrent.getMatCode() && compCode == orderCurrent.getCompCode() )
			{
				log.Debug()<<"ACTION_GRID_INFO_CHECK  is OK ������true��"<<endl;
				ret = true;
				return ret;
			}
			log.Debug()<<"ACTION_GRID_INFO_CHECK  is FAILED ������false��"<<endl;
			ret = false;
			return ret;
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


