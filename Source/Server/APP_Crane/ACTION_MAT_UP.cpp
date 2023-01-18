#include "ACTION_MAT_UP.h"

using namespace Monitor;

ACTION_MAT_UP :: ACTION_MAT_UP(void)
{
}



ACTION_MAT_UP :: ~ACTION_MAT_UP(void)
{
}



//1 doAction
bool ACTION_MAT_UP :: doAction(string craneNO, 
															   string bayNO,
															   OrderCurrentBase orderCurrent, 
															   CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_MAT_UP :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_MAT_UP------------------------ ----------------------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( ! ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;
		if( cranePLCStatus.getHasCoil() != 0 )
		{
			log.Debug()<<"�г���ǰȡ����ɣ��г�hascoil != 0������true��"<<endl;
			ret=true;
			return ret;
		}
		

		log.Debug()<<"orderCurrent.getPlanUpX()"<<orderCurrent.getPlanUpX()<<endl;
		log.Debug()<<"orderCurrent.getPlanUpY()"<<orderCurrent.getPlanUpY()<<endl;
		if ( orderCurrent.getPlanUpX() == DB_INT_NULL || orderCurrent.getPlanUpY() == DB_INT_NULL )//ȡ�ϵ������9
		{
			log.Debug()<<"ȡ�ϵ�XY�����9�� ���� false��"<<endl;
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getPlanUpZ()"<<orderCurrent.getPlanUpZ()<<endl;
		if ( orderCurrent.getPlanUpZ() == DB_INT_NULL )//ȡ�ϵ�߶�Z��9
		{
			log.Debug()<<"ȡ�ϵ�Z�����9�� ���� false��"<<endl;
			ret=false;
			return ret;
		}

		if (false == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							orderCurrent.getPlanUpX(), 
																																							orderCurrent.getPlanUpY(), 
																																							100, 
																																							100 ) )
		{
			log.Debug()<<"�г���δ���� ȡ�ϵ� ������false��"<<endl;
			ret=false;
			return ret;
		}

		log.Debug()<<"  �г��Ѿ�����ȡ�ϵ㣬���ڳ��Դ���ȡ���¼�ǯָ���·����г��� "<<endl;

		//׼���·��г��ƶ�ָ�ɨ���ƶ�ָ�
		//��ǰҪȡ������

		long matWeight = DB_INT_NULL;
		long matType = StringHelper::ToNumber<long>( orderCurrent.getMatType() );

		//ֻ����װ��ʱ��������Ҫ��
		if (orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_L3_YARD_TO_CAR_21 || 
			orderCurrent.getOrderType() == OrderQueueBase::ORDER_TYPE_EAF_YARD_TO_CAR_22 )
		{
			matWeight = orderCurrent.getMatReqWgt() - orderCurrent.getMatActWgt();//Ҫ������ - �ۼ���ҵ����
		}

		ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Coil_Up_Order_On_Spot(craneNO,
																																						orderCurrent.getOrderNO(),
																																						matWeight, 
																																						matType, 
																																						orderCurrent.getPlanUpX(),
																																						orderCurrent.getPlanUpY(),
																																						orderCurrent.getPlanUpZ(),
																																						orderCurrent.getUpRotateAngle() );

		log.Debug()<<"Mat Up Order�Ѿ��·����г�PLC���ȴ��г���ȡ�����....������ɣ�����false...."<<endl;
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


