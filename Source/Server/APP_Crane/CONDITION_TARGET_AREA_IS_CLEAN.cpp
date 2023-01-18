#include "CONDITION_TARGET_AREA_IS_CLEAN.h"



using namespace Monitor;



CONDITION_TARGET_AREA_IS_CLEAN :: CONDITION_TARGET_AREA_IS_CLEAN(void)
{


}



CONDITION_TARGET_AREA_IS_CLEAN :: ~CONDITION_TARGET_AREA_IS_CLEAN(void)
{



}




bool CONDITION_TARGET_AREA_IS_CLEAN ::judge(string craneNO, string movingDirection, long currentX , long targetX, CranePLCStatusBase  neightborCranePLCStatusBase)
{


	string functionName = "CONDITION_TARGET_AREA_IS_CLEAN :: judge()";
	LOG log(functionName, AUTO_CATCH_PID);
	
	//假设区域内有人
	bool ret=false;

	try
	{

		//判断临近行车是否在本车作业范围内
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			//2018.10.16 zhangyuhong add
			//情况1.........................
			//---Current---target----NeighborCrane--->
			if( neightborCranePLCStatusBase.getXAct() - targetX <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && neightborCranePLCStatusBase.getXAct() > targetX)
			{
				log.Debug()<<"移动方向为X增大方向，(-)---Current---target----NeighborCrane--->(+)  NeighborCrane与target间距小于安全距离，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			//情况2.........................
			//---Current---NeighborCrane---target--->
			if (neightborCranePLCStatusBase.getXAct() >= currentX && neightborCranePLCStatusBase.getXAct() <= targetX)
			{
				log.Debug()<<"移动方向为X增大方向，(-)---Current---NeighborCrane---target--->(+)  NeighborCrane位于currentX与targetX之间，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"移动方向为X增大方向，邻车不在本车作业范围内，进程返回true......"<<endl;
			ret=true;
			return ret;
		}
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			//2018.10.16 zhangyuhong add
			//情况1.........................
			//<---NeighborCrane---target---Current---
			if ( targetX - neightborCranePLCStatusBase.getXAct() <= RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES && neightborCranePLCStatusBase.getXAct() < targetX )
			{
				log.Debug()<<"移动方向为X减小方向，(-)<---NeighborCrane---target---Current---(+)  NeighborCrane与target间距小于安全距离，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			//情况2.........................
			//<---target---NeighborCrane---Current---
			if ( neightborCranePLCStatusBase.getXAct() >= targetX && neightborCranePLCStatusBase.getXAct() <= currentX)
			{
				log.Debug()<<"移动方向为X减小方向，(-)<---target---NeighborCrane---Current---(+)  NeighborCrane位于currentX与targetX之间，进程返回false......"<<endl;
				ret=false;
				return ret;
			}
			log.Debug()<<"移动方向为X减小方向，(-)<---NeighborCrane---target---Current---(+)  邻车不在本车作业范围内，进程返回true......"<<endl;
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
