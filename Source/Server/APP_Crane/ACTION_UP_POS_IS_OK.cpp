#include "ACTION_UP_POS_IS_OK.h"

using namespace Monitor;

ACTION_UP_POS_IS_OK :: ACTION_UP_POS_IS_OK(void)
{
}



ACTION_UP_POS_IS_OK :: ~ACTION_UP_POS_IS_OK(void)
{
}



//1 doAction
bool ACTION_UP_POS_IS_OK :: doAction(string craneNO, 
																		 string bayNO,
																		 OrderCurrentBase orderCurrent, 
																		 CranePLCStatusBase cranePLCStatus)	
{
	bool ret=false;

	string functionName="ACTION_UP_POS_IS_OK :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_UP_POS_IS_OK---------------------------- -----------------------------"<<endl;
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

		//ȡ�ϵ��Ƿ���ֵ  ȫ���Ƿ�9
		if (orderCurrent.getPlanUpX() != DB_INT_NULL && orderCurrent.getPlanUpY() != DB_INT_NULL && orderCurrent.getPlanUpZ() != DB_INT_NULL)
		{
			log.Info()<<"planUpXYZ IS NOT 999999, means  planUpXYZ is OK, return true..................................................."<<endl;
			ret =  true;
			return ret;
		}

		//ȡ�ϵ� ��9�Ļ� �жϼ�� MAT_UP_SCAN_NO�Ƿ��� NO_MAT  �����  ��ȡ�����
		if (orderCurrent.getMatUpScanNO() == "NO_MAT")
		{
			//����ǹ��ָ���
			if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
			{
				//��յ�ǰָ���  
				log.Info()<<"orderCurrent.getMatUpScanNO() == NO_MAT, means END OF MAT UP..........init OrderCurrent , return false......................................."<<endl;
				//���ָ�������false
				//������
				//1.���ָ���
				//2.ָ֪ͨ��ģ�� ���ָ�����
			}

			//�����װ��ָ��, �򱨾���ʾ,����false
			if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
				orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
			{
				log.Info()<<"orderCurrent.getMatUpScanNO() == NO_MAT, means ERROR OF MAT UP.......... return false......................................."<<endl;
			}


			ret = false;
			return ret;
		}


		//�ж��г��Ƿ���Ҫȡ�ϵ�������  ж����  �����ϸ�	

		//���Ȼ�ȡж�������ϸ�����ĵ�����
		map<string, long> mapXYZValue;
			
		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_CAR_TO_YARD_11)
		{
			//fromStockNO����ж����
			if ( false == Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromDumpingInfo(orderCurrent.getFromStockNO(), mapXYZValue) )
			{
				log.Info()<<"this DUMPING area is no define in UACS_DUMPING_INFO_DEFINE.........return false............."<<endl;
				ret = false;
				return ret;
			}
		}

		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
			orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22)
		{
			//fromStockNO�����ϸ�
			if ( false == Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromGridInfo(orderCurrent.getFromStockNO(), mapXYZValue) )
			{
				log.Info()<<"this GRID area is no define in UACS_YARDMAP_GRID_INFO_DEFINE.........return false............."<<endl;
				ret = false;
				return ret;
			}
		}

		long scanXCenter = mapXYZValue["X_CENTER"];
		long scanYCenter = mapXYZValue["Y_CENTER"];

		//�г��Ƿ񵽴�ȡ��ɨ������ӽ����ĵ�
		if (true == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							scanXCenter, 
																																							scanYCenter, 
																																							100, 
																																							100 ) )
		{
			log.Debug()<<"�г��Ѿ����� ȡ�� ɨ������ӽ����ĵ� ������ false��"<<endl;
			ret=false;
			return ret;
		}

		//�г���δ����  ����ָ�����г�ȥ
		Clone_DownLoadMoving_Order::go(bayNO, 
																			craneNO, 
																			orderCurrent.getOrderNO(), 
																			cranePLCStatus.getXAct(), 
																			cranePLCStatus.getYAct(), 
																			scanXCenter, 
																			scanYCenter, 
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


