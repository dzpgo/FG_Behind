#include "CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA.h"



using namespace Monitor;



CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA :: CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA(void)
{


}



CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA :: ~CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA(void)
{



}




bool CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA ::judge(string craneNO, string movingDirection, long currentX , long targetX, CranePLCStatusBase  neightborCranePLCStatusBase)
{


	string functionName = "CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA :: judge()";
	LOG log(functionName, AUTO_CATCH_PID);

	//假设有人要要冲入区域
	bool ret=false;

	try
	{

		long neighborTargetX=CranePLCOrderBase::PLC_INT_NULL;

		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Debug()<<"相邻行车目前无卷，其目标位置为起卷X坐标：neightborCranePLCStatusBase.getPlanUpX()"<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getPlanUpX();
		}
		if(neightborCranePLCStatusBase.getHasCoil()==1)
		{
			log.Debug()<<"相邻行车目前有卷，其目标位置为落卷X坐标：neightborCranePLCStatusBase.getPlanDownX()"<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getPlanDownX();
		}

		//如果neighborTargetX 封9 那么以当前位置替代
		if(neighborTargetX==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"相邻行车的目标位置X坐标是封9，故其目标位置设定为当前X位置：neightborCranePLCStatusBase.getXAct()"<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getXAct();
		}

		//判断临车是否有意图要冲入本区
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			//2018.10.16 zhangyuhong add
			//情况1...........................
			//---Current---target---NeighborCrneTarget--->
			if ( neighborTargetX - targetX <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && neighborTargetX > targetX)
			{
				log.Debug()<<"移动方向为X增大方向，(-)---Current---target---NeighborCrneTarget--->(+)   NeighborCrneTarget与target间距小于安全距离，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			//情况2...........................
			//---Current---NeighborCrneTarget---target--->
			if ( neighborTargetX >= currentX && neighborTargetX <= targetX)
			{
				log.Debug()<<"移动方向为X增大方向，(-)---Current---NeighborCrneTarget---target--->(+)   NeighborCrneTarget位于currentX与targetX之间，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			//情况3...........................
			//---NeighborCrneTarget---Current---target--->
			if ( neighborTargetX < currentX)
			{
				log.Debug()<<"移动方向为X增大方向，(-)---NeighborCrneTarget---Current---target--->(+)   NeighborCrneTarget小于currentX，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"移动方向为X增大方向，行车可以移动，进程返回true......"<<endl;
			ret=true;
			return ret;			
		}
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			//2018.10.16 zhangyuhong add
			//情况1...........................
			//<---NeighborCraneTarget---target---Current---
			if (targetX - neighborTargetX <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && targetX > neighborTargetX)
			{
				log.Debug()<<"移动方向为X减小方向，(-)<---NeighborCraneTarget---target---Current---(+)   NeighborCrneTargetX与targetX间距小于安全距离，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			//情况2...........................
			//<---target---NeighborCraneTarget---Current---
			if (neighborTargetX >= targetX && neighborTargetX <= currentX)
			{
				log.Debug()<<"移动方向为X减小方向，(-)<---target---NeighborCraneTarget---Current---(+)   NeighborCrneTargetX位于targetX与currentX之间，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			//情况3...........................
			//<---target---Current---NeighborCraneTarget---
			if (neighborTargetX > currentX)
			{
				log.Debug()<<"移动方向为X减小方向，(-)<---target---Current---NeighborCraneTarget---(+)   NeighborCrneTargetX大于currentX，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"移动方向为X减小方向，行车可以移动，进程返回true......"<<endl;
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
