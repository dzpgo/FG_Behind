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
			log.Debug()<<"行车当前放料完成，行车hascoil == 0！返回true！"<<endl;
			ret=true;
			return ret;
		}
		

		log.Debug()<<"orderCurrent.getPlanDownX()"<<orderCurrent.getPlanDownX()<<endl;
		log.Debug()<<"orderCurrent.getPlanDownY()"<<orderCurrent.getPlanDownY()<<endl;
		if ( orderCurrent.getPlanDownX() == DB_INT_NULL || orderCurrent.getPlanDownY() == DB_INT_NULL )//取料点坐标封9
		{
			log.Debug()<<"放料点XY坐标封9， 返回 false！"<<endl;
			ret=false;
			return ret;
		}

		log.Debug()<<"orderCurrent.getPlanDownZ()"<<orderCurrent.getPlanDownZ()<<endl;
		if ( orderCurrent.getPlanDownZ() == DB_INT_NULL )//取料点高度Z封9
		{
			log.Debug()<<"放料点Z坐标封9， 返回 false！"<<endl;
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
			log.Debug()<<"行车还未到达 取料点 ！返回false！"<<endl;
			ret=false;
			return ret;
		}

		log.Debug()<<"  行车已经到达取料点，现在尝试创建取料下夹钳指令下发至行车！ "<<endl;

		//准备下发行车移动指令（扫描移动指令）
		//当前要取料重量
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

		log.Debug()<<"Mat Down Order已经下发至行车PLC，等待行车放料完成....进程完成，返回false...."<<endl;
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


