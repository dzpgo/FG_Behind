#include "ACTION_MAT_DOWN.h"

using namespace Monitor;

ACTION_MAT_DOWN :: ACTION_MAT_DOWN(void)
{
}



ACTION_MAT_DOWN :: ~ACTION_MAT_DOWN(void)
{
}



//1 doAction
bool ACTION_MAT_DOWN :: doAction(string craneNO, 
															   string bayNO,
															   OrderCurrentBase orderCurrent, 
															   CranePLCStatusBase cranePLCStatus)
{
	bool ret=false;

	string functionName="ACTION_MAT_DOWN :: doAction()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{
		log.Debug()<<"--------------------------------------------------------------------------------------------------------------"<<endl;
		log.Debug()<<" ------------------------ACTION_MAT_DOWN-----------------------------------------------------------"<<endl;
		log.Debug()<<" ---------------------------------------------------------------------------------------------------------------"<<endl;

		if( ! ACTION_COMMON_FUNCTION::CustomOfficer_ForAllActions_1(craneNO,bayNO,orderCurrent,cranePLCStatus) )
		{
			ret=false;
			return ret;
		}

		log.Debug()<<"cranePLCStatus.getHasCoil()"<<cranePLCStatus.getHasCoil()<<endl;
		if( cranePLCStatus.getHasCoil() == 0 )
		{
			log.Debug()<<"�г���ǰ������ɣ��г�hascoil == 0������true��"<<endl;
			ret=true;
			return ret;
		}
		

		log.Debug()<<"orderCurrent.getPlanDownX()"<<orderCurrent.getPlanDownX()<<endl;
		log.Debug()<<"orderCurrent.getPlanDownY()"<<orderCurrent.getPlanDownY()<<endl;
		if ( orderCurrent.getPlanDownX() == DB_INT_NULL || orderCurrent.getPlanDownY() == DB_INT_NULL )//ȡ�ϵ������9
		{
			log.Debug()<<"���ϵ�XY�����9�� ���� false��"<<endl;
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getPlanDownZ()"<<orderCurrent.getPlanDownZ()<<endl;
		if ( orderCurrent.getPlanDownZ() == DB_INT_NULL )//ȡ�ϵ�߶�Z��9
		{
			log.Debug()<<"���ϵ�Z�����9�� ���� false��"<<endl;
			ret=false;
			return ret;
		}

		if (false == ACTION_COMMON_FUNCTION::Assistant_Is_PlaceArrived_By_Distance(cranePLCStatus.getXAct(), 
																																							cranePLCStatus.getYAct(), 
																																							orderCurrent.getPlanDownX(), 
																																							orderCurrent.getPlanDownY(), 
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
		

		ACTION_COMMON_FUNCTION :: Assistant_DownLoad_Coil_Down_Order_On_Spot(craneNO,
																																								orderCurrent.getOrderNO(),
																																								matWeight, 
																																								matType, 
																																								orderCurrent.getPlanDownX(),
																																								orderCurrent.getPlanDownY(),
																																								orderCurrent.getPlanDownZ(),
																																								orderCurrent.getDownRotateAngle() );

		log.Debug()<<"Mat Down Order�Ѿ��·����г�PLC���ȴ��г��������....������ɣ�����false...."<<endl;
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


