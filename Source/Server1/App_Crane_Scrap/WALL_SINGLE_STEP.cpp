#include "WALL_SINGLE_STEP.h"



using namespace Monitor;


const long WALL_SINGLE_STEP::WALL_DYNAMIC=1;
const long WALL_SINGLE_STEP::WALL_STATIC=2;

WALL_SINGLE_STEP :: WALL_SINGLE_STEP(void)
{


}



WALL_SINGLE_STEP :: ~WALL_SINGLE_STEP(void)
{



}





bool WALL_SINGLE_STEP ::getWall(string craneNO, string movingDirection,  CranePLCStatusBase  neightborCranePLCStatusBase, long& wallX, long& wallType)
{


	string functionName = "WALL_SINGLE_STEP :: getWall()";
	LOG log(functionName, AUTO_CATCH_PID);

	bool ret=false;
	
	try
	{
		log.Debug()<<"本车="<<craneNO<<"   移动方向="<<movingDirection<<endl;
		log.Debug()<<"邻车="<<neightborCranePLCStatusBase.getCraneNO()<<"  邻车当前大车X="<<neightborCranePLCStatusBase.getXAct()<<endl;

		ret=true;
		//面前行车的当前位置
		long neighborCurrentX=neightborCranePLCStatusBase.getXAct();
		log.Debug()<<"邻车当前X坐标 neighborCurrentX="<<neighborCurrentX<<endl;
		log.Debug()<<"邻车当前有卷标记 getHasCoil() ="<<neightborCranePLCStatusBase.getHasCoil()<<endl;

		//面前行车的目标位置
		long neighborTargetX=CranePLCOrderBase::PLC_INT_NULL;

		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			//空钩情况目标位置为起卷目标位置X
			neighborTargetX=neightborCranePLCStatusBase.getPlanUpX();
		}
		if(neightborCranePLCStatusBase.getHasCoil()==1)
		{
			//重钩情况目标位置为落卷目标位置X
			neighborTargetX=neightborCranePLCStatusBase.getPlanDownX();
		}

		log.Debug()<<"邻车的目标大车X坐标：targetX="<<neighborTargetX<<endl;

		//如果行车的目标位置封9 说明行车当前是自动并且行车行车停在原地
		if(neighborTargetX==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"邻车的目标大车X坐标 targetX=PLC_INT_NULL 封9，用当前坐标X currentX替换...."<<endl;
			neighborTargetX=neightborCranePLCStatusBase.getXAct();
			log.Debug()<<"邻车的目标大车X坐标（getXAct） targetX="<<neighborTargetX<<endl;
		}
		//前进方向为X大方向 
		if(movingDirection==MOVING_DIR::DIR_X_INC)
		{
			log.Debug()<<"本车的前进方向为X增大方向 movingDirection="<<movingDirection<<endl;
			//(-)------Current-----------------------------target-----------------NeighborCrane-->(+)
			//当前车向X大方向运动，面前车中当前位置  目标位置中比较小的是墙  是当前位置的 是动态墙，是目标位置的是静态墙
			

			if(abs(neighborCurrentX-neighborTargetX)<=100)
			{
				log.Debug()<<"邻车到位......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"墙类型 wallType is WALL_STATIC 静态的；单步墙坐标应为相邻行车的目标X位置坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}

			//情况一：------NeighborCrane------neighborTargetX----->
			if(  neighborCurrentX< neighborTargetX)
			{
				log.Debug()<<"邻车的当前X位置坐标 < 邻车的目标X位置坐标......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_DYNAMIC;
				log.Debug()<<"墙类型 wallType is WALL_DYNAMIC 动态的； 单步墙坐标应为邻车的当前X位置坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//情况二：------neighborTargetX------NeighborCrane----->
			else if(neighborCurrentX>neighborTargetX)
			{
				log.Debug()<<"邻车的当前X位置坐标 > 邻车的目标X位置坐标......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"墙类型 wallType is WALL_STATIC 静态的；单步墙坐标应为相邻行车的目标X位置坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//情况三：相等
			else if(neighborCurrentX==neighborTargetX)
			{
				log.Debug()<<"邻车的当前X位置坐标 = 邻车的目标X位置坐标......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"墙类型 wallType is WALL_STATIC 静态的；单步墙坐标应为相邻行车的当前X位置（=目标X位置）坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
		}
		//前进方向为X小方向  
		//当前车向X小方向运动，面前车中当前位置  目标位置中比较大的是墙   是当前位置的 是动态墙   是目标位置的是动态墙
		//  (-)<---NeighborCrane--------------target------------------Current-----------------(+)
		else if(movingDirection==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"本车的前进方向为X减小方向 movingDirection="<<movingDirection<<endl;

			if(abs(neighborCurrentX-neighborTargetX)<30)
			{
				log.Debug()<<"邻车到位......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"墙类型 wallType is WALL_STATIC 静态的；单步墙坐标应为相邻行车的目标X位置坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}

			//情况一：(-)<------neighborTargetX------NeighborCrane-----(+)
			if(neighborCurrentX> neighborTargetX)
			{
				log.Debug()<<"邻车的当前X位置坐标 > 相邻行车的目标X位置坐标......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_DYNAMIC;
				log.Debug()<<"墙类型 wallType is WALL_DYNAMIC 动态的； 单步墙坐标应为相邻行车的当前X位置坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//情况二：(-)<------NeighborCrane------neighborTargetX-----(+)
			else if(neighborCurrentX<neighborTargetX)
			{
				log.Debug()<<"相邻行车的当前X位置坐标 < 相邻行车的目标X位置坐标......"<<endl;
				wallX=neighborTargetX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"墙类型 wallType is WALL_STATIC 静态的； 单步墙坐标应为相邻行车的目标X位置坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
			//情况三：相等
			else if(neighborCurrentX==neighborTargetX)
			{
				log.Debug()<<"相邻行车的当前X位置坐标 = 相邻行车的目标X位置坐标......"<<endl;
				wallX=neighborCurrentX;
				wallType=WALL_SINGLE_STEP::WALL_STATIC;
				log.Debug()<<"墙类型 wallType is WALL_STATIC 静态的； 单步墙坐标应为相邻行车的当前X位置（=目标X位置）坐标 wallX= "<<wallX<<endl;
				ret=true;
				return ret;
			}
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
