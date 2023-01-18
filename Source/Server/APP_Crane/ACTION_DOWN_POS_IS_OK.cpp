#include "ACTION_DOWN_POS_IS_OK.h"

using namespace Monitor;

ACTION_DOWN_POS_IS_OK :: ACTION_DOWN_POS_IS_OK(void)
{
}



ACTION_DOWN_POS_IS_OK :: ~ACTION_DOWN_POS_IS_OK(void)
{
}



//1 doAction
bool ACTION_DOWN_POS_IS_OK :: doAction(string craneNO, 
																					   string bayNO,
																					   OrderCurrentBase orderCurrent, 
																					   CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_DOWN_POS_IS_OK :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_DOWN_POS_IS_OK------------------------ ----------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( ! ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getCmdStatus()"<<orderCurrent.getCmdStatus()<<endl;
		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;
		if(orderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_COIL_DOWN_PROCESS && cranePLCStatus.getHasCoil() == 0)
		{
			log.Debug()<<"�г���ǰָ������CoilDown״̬�����г�hascoil = 0������true��"<<endl;
			ret=true;
			return ret;
		}

		//���ϵ��Ƿ���ֵ  ȫ���Ƿ�9
		if (orderCurrent.getPlanDownX() != DB_INT_NULL && orderCurrent.getPlanDownY() != DB_INT_NULL && orderCurrent.getPlanDownZ() != DB_INT_NULL)
		{
			log.Info()<<"PlanDownXYZ IS NOT 999999, means  PlanDownXYZ is OK, return true..................................................."<<endl;
			ret =  true;
			return ret;
		}

		//����Ƿ�9  ˵�����ϵ㻹û�յ�  ��ʱ�Ȱ��г��������ϵ㸽��  һ�������ĵ�

		long centerX = DB_INT_NULL;
		long centerY = DB_INT_NULL;

		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			map<string, long> mapXYZValue;
			//toStockNO�����ϸ�
			if ( false == Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromGridInfo(orderCurrent.getToStockNO(), mapXYZValue) )
			{
				log.Info()<<"this GRID area is no define in UACS_YARDMAP_GRID_INFO_DEFINE.........return false............."<<endl;
				ret = false;
				return ret;
			}
			centerX = mapXYZValue["X_CENTER"];
			centerY = mapXYZValue["Y_CENTER"];
		}

		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
			orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
		{
			//toStockNO���ǳ���
			//���û��carScanNO �򷵻�false
			if (orderCurrent.getCarScanNO().empty())
			{
				log.Info()<<"CarScanNO in OrderCurrent   IS   EMPTY,  return false........................."<<endl;
				ret = false;
				return ret;
			}

			//����carScanNO��ȡ uacs_parking_srs_car_info �еĳ���ɨ�����ĵ�
			if (false == Adapter_UACS_YARDMAP_STOCK_INFO::SelCarCenterXY(orderCurrent.getCarScanNO(), centerX, centerY))
			{
				log.Info()<<"CarScanNO Record in UACS_PARKING_SRS_CAR_INFO   IS   EMPTY,  return false........................."<<endl;
				ret = false;
				return ret;
			}			
		}

		if (centerX == DB_INT_NULL || centerY == DB_INT_NULL)
		{
			log.Info()<<"centerX == 999999 || centerY == 999999,  return false........................."<<endl;
			ret = false;
			return ret;
		}

		if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							centerX, 
																																							centerY, 
																																							100, 
																																							100 ) )
		{
			log.Debug()<<"�г��Ѿ����� ���� ɨ������ӽ����ĵ�  ������false��"<<endl;
			ret=false;
			return ret;
		}

		//׼���·��г��ƶ�ָ�ɨ���ƶ�ָ�
		Clone_DownLoadMoving_Order::go(bayNO, 
																			craneNO, 
																			orderCurrent.getOrderNO(), 
																			cranePLCStatus.getXAct(), 
																			cranePLCStatus.getYAct(), 
																			centerX, 
																			centerY, 
																			cranePLCStatus.getHasCoil(), 
																			DB_INT_NULL, 
																			DB_INT_NULL, 
																			1);

		log.Debug()<<"Moving Order�Ѿ��·����г�PLC���ȴ��г�������ȡ��ɨ��λ....������ɣ�����false...."<<endl;
		ret = false;
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


