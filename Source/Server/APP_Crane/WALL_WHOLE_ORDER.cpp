#include "WALL_WHOLE_ORDER.h"



using namespace Monitor;


WALL_WHOLE_ORDER :: WALL_WHOLE_ORDER(void)
{


}



WALL_WHOLE_ORDER :: ~WALL_WHOLE_ORDER(void)
{



}





bool WALL_WHOLE_ORDER ::getWall(string craneNO, string movingDirection, CranePLCStatusBase  neightborCranePLCStatusBase , long& wallX, long& wallType)
{
	string functionName = "WALL_WHOLE_STEP :: getWall()";
	LOG log(functionName, AUTO_CATCH_PID);

	//假设不能获得
	bool ret=false;

	try
	{
		log.Debug()<<"本车="<<craneNO<<"   本车方向="<<movingDirection<<endl;
		log.Debug()<<"邻车="<<neightborCranePLCStatusBase.getCraneNO()<<"  邻车当前X坐标="<<neightborCranePLCStatusBase.getXAct()<<endl;

		//面前行车的当前位置
		long neighborCurrentX=neightborCranePLCStatusBase.getXAct();

		//行车运动的目标位置
		long neighborMoveingTarget=CranePLCOrderBase::PLC_INT_NULL;
		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			neighborMoveingTarget=neightborCranePLCStatusBase.getPlanUpX();
		}
		else if(neightborCranePLCStatusBase.getHasCoil()==1)
		{
			neighborMoveingTarget=neightborCranePLCStatusBase.getPlanDownX();
		}


		log.Debug()<<"准备获取邻车的WMS指令....... "<<endl;

		long neighborX_Min;
		long wallType_X_Min;

		long neighborX_Max;
		long wallType_X_Max;

		OrderCurrentBase  neightborCraneOrderCurrent;
		neightborCraneOrderCurrent=Adapter_UACS_CRANE_ORDER_CURRENT::getData(neightborCranePLCStatusBase.getCraneNO());
		if(neightborCraneOrderCurrent.getOrderNO()==DB_INT_NULL)
		{
			log.Debug()<<"邻车当前指令表中的指令号=999999，用行车当前X替换指令中的planUpX 和 planDownX......"<<endl;
			neightborCraneOrderCurrent.setPlanUpX( neightborCranePLCStatusBase.getXAct() );
			neightborCraneOrderCurrent.setPlanDownX( neightborCranePLCStatusBase.getXAct() );
		}
		if(neightborCraneOrderCurrent.getCmdStatus()==OrderCurrentBase::CRANE_ORDER_CURRENT_STATUS_EMPTY)
		{
			log.Debug()<<"邻车当前指令表中的指令号=999999，用行车当前X替换指令中的planUpX 和 planDownX......"<<endl;
			neightborCraneOrderCurrent.setPlanUpX( neightborCranePLCStatusBase.getXAct() );
			neightborCraneOrderCurrent.setPlanDownX( neightborCranePLCStatusBase.getXAct() );
		}

		//******************************************************************************************************************************
		//*
		//								取得相邻行车当前位置  行车计划起吊位置  行车计划落关位置中 最大的与最小的
		//*
		//******************************************************************************************************************************
		

		neighborX_Min=neightborCranePLCStatusBase.getXAct();
		wallType_X_Min=WALL_SINGLE_STEP::WALL_DYNAMIC;

		if(neightborCranePLCStatusBase.getXDirectPositive()==1  || neightborCranePLCStatusBase.getXDirectNegative()==1)
		{
			wallType_X_Min=WALL_SINGLE_STEP::WALL_DYNAMIC;//20171117  车在动的是动墙
		}
		if(neightborCranePLCStatusBase.getXDirectPositive()==0  && neightborCranePLCStatusBase.getXDirectNegative()==0)
		{
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;//20171117  //车没有动的是静墙
		}

		if(neighborX_Min>neightborCraneOrderCurrent.getPlanUpX()  &&  neightborCraneOrderCurrent.getPlanUpX() !=CranePLCOrderBase::PLC_INT_NULL && neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Info()<<"1. 计算neighborX_Min：......比较planUpX"<<endl;
			neighborX_Min=neightborCraneOrderCurrent.getPlanUpX();
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Min>neightborCraneOrderCurrent.getPlanDownX()  && neightborCraneOrderCurrent.getPlanDownX() !=CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Info()<<"2. 计算neighborX_Min：......比较planDownX"<<endl;
			neighborX_Min=neightborCraneOrderCurrent.getPlanDownX();
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Min>neighborMoveingTarget &&neighborMoveingTarget !=CranePLCOrderBase::PLC_INT_NULL)
		{
			neighborX_Min=neighborMoveingTarget;
			wallType_X_Min=WALL_SINGLE_STEP::WALL_STATIC;
		}

		//--------------------------------------------------------------------------------------------------------------------------------

		neighborX_Max=neightborCranePLCStatusBase.getXAct();
		wallType_X_Max=WALL_SINGLE_STEP::WALL_DYNAMIC;

		if(neightborCranePLCStatusBase.getXDirectPositive()==1  || neightborCranePLCStatusBase.getXDirectNegative()==1)
		{
			wallType_X_Max=WALL_SINGLE_STEP::WALL_DYNAMIC;//20171117  车在动的是动墙
		}
		if(neightborCranePLCStatusBase.getXDirectPositive()==0  && neightborCranePLCStatusBase.getXDirectNegative()==0)
		{
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;//20171117  //车没有动的是静墙
		}

		if(neighborX_Max<neightborCraneOrderCurrent.getPlanUpX()  &&  neightborCraneOrderCurrent.getPlanUpX() !=CranePLCOrderBase::PLC_INT_NULL && neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Info()<<"1. 计算neighborX_Max：邻车空钩......"<<endl;
			neighborX_Max=neightborCraneOrderCurrent.getPlanUpX();
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Max<neightborCraneOrderCurrent.getPlanDownX()  && neightborCraneOrderCurrent.getPlanDownX() !=CranePLCOrderBase::PLC_INT_NULL )
		{
			log.Info()<<"2. 计算neighborX_Max：邻车重钩......"<<endl;
			neighborX_Max=neightborCraneOrderCurrent.getPlanDownX();
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;
		}
		if(neighborX_Max<neighborMoveingTarget  && neighborMoveingTarget !=CranePLCOrderBase::PLC_INT_NULL)
		{
			neighborX_Max=neighborMoveingTarget;
			wallType_X_Max=WALL_SINGLE_STEP::WALL_STATIC;
		}

		log.Debug()<<"neighborX_Min = "<<neighborX_Min<<"，wallType_X_Min = "<<getWallTypeString(wallType_X_Min)<<endl;
		log.Debug()<<"neighborX_Max = "<<neighborX_Max<<"，wallType_X_Max = "<<getWallTypeString(wallType_X_Max)<<endl;

		//前进方向为X大方向 
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			//(-)------Current-----------------------------target-----------------NeighborCrane---->(+)
			//当前车向X大方向运动，面前车中 最大X与最小X  中比较小的是墙  是当前位置的 是动态墙，是目标位置的是静态墙
			log.Debug()<<"本车方向为 X_INC，(-)----Current-----target----NeighborCrane---->(+)，取较小值 neighborX_Min 作为wallX"<<endl;
			wallX=neighborX_Min;
			wallType=wallType_X_Min;
			log.Debug()<<"wallX = "<<neighborX_Min<<"  wallType= "<<wallType_X_Min<<endl;
			log.Debug()<<"进程返回true......"<<endl;
			ret=true;
			return ret;

		}
		//前进方向为X小方向  
		//当前车向X小方向运动，面前车中当前位置  目标位置中比较大的是墙   是当前位置的 是动态墙   是目标位置的是动态墙
		//  (-)<---NeighborCrane--------------target------------------Current-----------------(+)
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"本车方向为 X_DES，(-)<---NeighborCrane-----target----Current-----(+)，取较大值 neighborX_Max 作为wallX"<<endl;
			wallX=neighborX_Max;
			wallType=wallType_X_Max;
			log.Debug()<<"wallX = "<<neighborX_Max<<"  wallType= "<<wallType_X_Max<<endl;
			log.Debug()<<"进程返回true......"<<endl;
			ret=true;
			return ret;

		}

		log.Debug()<<"ret="<<ret<<"  returned"<<endl;

		return ret;

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

	return ret;
}



//2019.3.24 zhangyuhong add
string WALL_WHOLE_ORDER::getWallTypeString(long wallType)
{
	string functionName = "WALL_WHOLE_ORDER :: getWallTypeString()";
	LOG log(functionName, AUTO_CATCH_PID);

	//假设不能获得
	string wallTypeString="";

	try
	{
		if (wallType == 1)
		{
			wallTypeString = "WALL_DYNAMIC";
		}
		else if (wallType == 2)
		{
			wallTypeString = "WALL_STATIC";
		}
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<functionName<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<functionName<<"   error:"<<endl;
	}
	return wallTypeString;
}
