#include "CLOSE_TO_DYNAMIC_WALL.h"



using namespace Monitor;





CLOSE_TO_DYNAMIC_WALL :: CLOSE_TO_DYNAMIC_WALL(void)
{


}



CLOSE_TO_DYNAMIC_WALL :: ~CLOSE_TO_DYNAMIC_WALL(void)
{



}



//如果是动态的墙壁，如果满足对方正在远去，并且对方的目标远于我的目标 并且已经拉开了一定的距离，那么跟上去，去目标位置
//如果是动态的墙壁，如果满足对方正在远去，并且对方的目标近于我的目标，并且已经来开了一定的距离，那么跟上去，跟在前车后面
bool CLOSE_TO_DYNAMIC_WALL ::closeToWall(string craneNO, string direction, long targetX,CranePLCStatusBase  cranePLCStatusBase, CranePLCStatusBase  neightborCranePLCStatusBase , long& XWallLimit)
{
	string functionName = "CLOSE_TO_DYNAMIC_WALL :: closeToWall()";
	LOG log(functionName, AUTO_CATCH_PID);

	//按照最差情况来，不能动车，能去的地方是原地
	XWallLimit=cranePLCStatusBase.getXAct();
	bool  retCanMove=false;

	try
	{
		log.Info()<<"......................................................................................进入***动态墙***跟随逻辑处理........................................................................................................"<<endl;
		string neighborCraneNO = neightborCranePLCStatusBase.getCraneNO();
		//**************************************************************************************************************************************************************
		//*
		//*												step1. 判断本车与邻车距离是否拉开  判断标准：最小跟随距离暂设定为 22米
		//*
		//**************************************************************************************************************************************************************
		long distanceBetweenCranes=abs(cranePLCStatusBase.getXAct()-neightborCranePLCStatusBase.getXAct());
		log.Debug()<<"step 1 判断两车距离是否拉开......"<<endl;
		log.Debug()<<"本车="<<craneNO<<"与邻车="<<neighborCraneNO<<" 当前距离 ="<<distanceBetweenCranes<<endl;

		if(distanceBetweenCranes < RED_LINE_BASIC_DATA::FOLLOW_MIN_DISTANCE)
		{
			log.Debug()<<"目前此距离 <  追随最小拉开距离（27000）   进程返回false，行车不能移动！"<<endl;
			retCanMove=false;
			return retCanMove;
		}
		else
		{
			log.Debug()<<"目前此距离 >  追随最小拉开距离（27000）   继续！"<<endl;
		}

		//**************************************************************************************************************************************************************
		//*
		//*												step2. 判断本车方向与邻车方向是否一致
		//*
		//**************************************************************************************************************************************************************
		log.Debug()<<"step 2 判断本车方向与邻车方向是否一致......"<<endl;
		if( direction==MOVING_DIR::DIR_X_INC  && neightborCranePLCStatusBase.getXDirectPositive()==1 )
		{
			log.Debug()<<"本车="<<craneNO<<" 方向为正向，邻车="<<neighborCraneNO<<" 方向为正向！本车与邻车运动方向同为：X增大方向 DIR_X_INC....."<<endl;
		}
		else if( direction==MOVING_DIR::DIR_X_DES  && neightborCranePLCStatusBase.getXDirectNegative()==1 )
		{
			log.Debug()<<"本车="<<craneNO<<" 方向为正向，邻车="<<neighborCraneNO<<" 方向为负向！本车与邻车运动方向同为：X减小方向 DIR_X_DES....."<<endl;
		}
		else
		{
			//这里其实已经排除了2车背向的情况，只能可能是同向的情况，所以本车不能动
			log.Debug()<<"本车="<<craneNO<<"，邻车="<<neighborCraneNO<<"  2车方向不一致，进程返回false！本车可靠近的极限墙位置设置为当前行车位置！"<<endl;
			log.Debug()<<"XWallLimit="<<XWallLimit<<endl;
			retCanMove=false;
			return retCanMove;
		}

		//**************************************************************************************************************************************************************
		//*
		//*												step3. 判断前车的目标是否远于本车的目标
		//*
		//**************************************************************************************************************************************************************
		log.Debug()<<"step 3 判断邻车的目标是否远于本车的目标......"<<endl;
		log.Debug()<<"邻车的是否有卷标记 HasCoil="<<neightborCranePLCStatusBase.getHasCoil()<<endl;

		//设置邻车的当前X坐标为邻车的目标X坐标初始值
		long targetXNeighbor=neightborCranePLCStatusBase.getXAct();
		if(neightborCranePLCStatusBase.getHasCoil()==0)
		{
			log.Info()<<"邻车="<<neighborCraneNO<<" 空钩...................."<<endl;
			targetXNeighbor=neightborCranePLCStatusBase.getPlanUpX();
		}
		else if(neightborCranePLCStatusBase.getHasCoil()==1)
		{	
			log.Info()<<"邻车="<<neighborCraneNO<<" 重钩...................."<<endl;
			targetXNeighbor=neightborCranePLCStatusBase.getPlanDownX();
		}
		log.Debug()<<"获得邻车="<<neighborCraneNO<<" 的目标X坐标 targetXNeighbor="<<targetXNeighbor<<endl;

		if(targetXNeighbor==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"邻车的目标位置X坐标 targetXNeighbor==PLC_INT_NULL 封9！准备用currentX 坐标 替换 targetXNeighbor"<<endl;
			targetXNeighbor=neightborCranePLCStatusBase.getXAct();
			log.Debug()<<"用currentX 坐标 替换后的 targetXNeighbor="<<targetXNeighbor<<endl;
		}


		//**************************************************************************************************************************************************************
		//*
		//*												step3. 判断前车的目标是否远于本车的目标
		//*												情况一：(-)-------------mytarget-----------------neighborTarget---->(+)
		//*
		//**************************************************************************************************************************************************************
		if(direction==MOVING_DIR::DIR_X_INC)
		{
			log.Debug()<<"情况一：(-)------myTarget-------neighborTarget---->(+)，正向移动：X_INC"<<endl;
			if(targetXNeighbor - targetX > RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES + RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE  )
			{
				log.Debug()<<"本车="<<craneNO<<"的目标X="<<targetX<<"，邻车="<<neighborCraneNO<<"的目标X="<<targetXNeighbor<<"，2者距离>安全距离（25000+100）......"<<endl;
				log.Debug()<<"本车="<<craneNO<<"可以开始移动，进程处理返回 true，可以直接移动至我方目标位置......墙极限位置XWallLimit即为本车目标targetX"<<endl;
				log.Debug()<<"XWallLimit=targetX"<<endl;
				XWallLimit=targetX;
				log.Debug()<<"XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
			else
			{
				log.Debug()<<"本车="<<craneNO<<"的目标X="<<targetX<<"，邻车="<<neighborCraneNO<<"的目标X="<<targetXNeighbor<<"，2者距离<安全距离（25000+100）......"<<endl;
				log.Debug()<<"本车可以开始移动，进程处理返回true，但不能直接移动至我方目标位置，需要移动到......XWallLimit"<<endl;
				log.Debug()<<"XWallLimit=邻车的目标X坐标 - 安全距离（25000+100）"<<endl;
				XWallLimit=targetXNeighbor  -  (RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES + RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE);
				log.Debug()<<"计算后得到，XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
		}

		//**************************************************************************************************************************************************************
		//*
		//*												step3. 判断前车的目标是否远于本车的目标
		//*												情况二：(-)<---------neighborTarget--------------------mytarget---(+)
		//*
		//**************************************************************************************************************************************************************
		if(direction==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"情况二：(-)<-------neighborTarget---------mytarget---(+)，负向移动：X_DES"<<endl;
			if(targetX - targetXNeighbor>RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES  +  RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE  )
			{
				log.Debug()<<"本车="<<craneNO<<"的目标X="<<targetX<<"，邻车="<<neighborCraneNO<<"的目标X="<<targetXNeighbor<<"，2者距离>安全距离（25000+100）......"<<endl;
				log.Debug()<<"本车="<<craneNO<<"可以开始移动，进程处理返回 true，可以直接移动至我方目标位置......墙极限位置XWallLimit即为本车目标targetX"<<endl;
				log.Debug()<<"XWallLimit=targetX"<<endl;
				XWallLimit=targetX;
				log.Debug()<<"XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
			else
			{
				log.Debug()<<"本车="<<craneNO<<"的目标X="<<targetX<<"，邻车="<<neighborCraneNO<<"的目标X="<<targetXNeighbor<<"，2者距离<安全距离（25000+100）......"<<endl;
				log.Debug()<<"本车可以开始移动，进程处理返回true，但不能直接移动至我方目标位置，需要移动到......XWallLimit"<<endl;
				log.Debug()<<"XWallLimit=邻车的目标X坐标 + 安全距离（25000+100）"<<endl;
				XWallLimit=targetXNeighbor  +  (RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES + RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE);
				log.Debug()<<"计算后得到，XWallLimit="<<XWallLimit<<endl;
				retCanMove=true;
				return retCanMove;
			}
		}	
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
	return retCanMove;
}
