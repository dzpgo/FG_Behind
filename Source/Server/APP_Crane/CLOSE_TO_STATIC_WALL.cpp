#include "CLOSE_TO_STATIC_WALL.h"



using namespace Monitor;





CLOSE_TO_STATIC_WALL :: CLOSE_TO_STATIC_WALL(void)
{


}



CLOSE_TO_STATIC_WALL :: ~CLOSE_TO_STATIC_WALL(void)
{



}




bool CLOSE_TO_STATIC_WALL ::closeToWall(string craneNO, string direction,long currentX, long wallX, long& XlimitToTheWall)
{
	string functionName = "CLOSE_TO_STATIC_WALL :: getCraneNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	//假设是不能动车的
	bool  retCanMove=false;
	XlimitToTheWall=currentX;
	try
	{
		log.Info()<<"......................................................................................进入***静态墙***跟随逻辑处理........................................................................................................"<<endl;
		log.Debug()<<"本车="<<craneNO<<"  移动方向="<<direction<<"  当前大车X="<<currentX<<" 墙X wallX="<<wallX<<endl;
		if(direction==MOVING_DIR::DIR_X_INC)
		{
			log.Debug()<<"向静态墙靠近：我方行车移动方向为X增大......(-)------Current-----------target--------------------WALL--------------->(+)"<<endl;
			//前进方向为X大方向  
			//(-)------Current-----------target--------------------WALL--------------->(+)
			XlimitToTheWall=wallX 
							- RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES 
							- RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE;
			log.Debug()<<"获取靠墙的X极限位置 XlimitToTheWall="<<XlimitToTheWall<<endl;
			if(XlimitToTheWall>currentX)
			{
				log.Debug()<<"靠墙的X极限位置 > 本车的当前位置 ，此种情况下，行车可以移动，进程返回true......"<<endl;
				retCanMove=true;
			}
			else
			{
				log.Debug()<<"靠墙的X极限位置 < 本车的当前位置 ，此种情况下，行车不能移动，进程返回false， 并将 靠墙的X极限位置 设置为 本车的当前位置......"<<endl;
				XlimitToTheWall=currentX;
				retCanMove=false;
			}
		}
		else if(direction==MOVING_DIR::DIR_X_DES)
		{
			log.Debug()<<"向静态墙靠近：我方行车移动方向为X减小......(-)<-----WALL------------target------------------Current-----------------(+)"<<endl;
			//前进方向为X小方向  
			// (-)<-----WALL------------target------------------Current-----------------(+)
			XlimitToTheWall=wallX
							+RED_LINE_BASIC_DATA::LIMIT_DISTANCE_BETWEEN_CRANES
							+RED_LINE_BASIC_DATA::COMPENSATE_DISTANCE;
			log.Debug()<<"获取靠墙的X极限位置 XlimitToTheWall="<<XlimitToTheWall<<endl;
			if(XlimitToTheWall < currentX)
			{
				log.Debug()<<"靠墙的X极限位置 < 本车的当前位置 ，此种情况下，行车可以移动，进程返回true......"<<endl;
				retCanMove=true;
			}
			else
			{
				log.Debug()<<"靠墙的X极限位置 > 本车的当前位置 ，此种情况下，行车不能移动，进程返回false， XlimitToTheWall的值即为currentX"<<endl;
				XlimitToTheWall=currentX;
				retCanMove=false;
			}
		}
		log.Debug()<<"本车的移动方向 ="<<direction<<endl;
		log.Debug()<<"本车当前X位置坐标 ="<<currentX<<endl;
		log.Debug()<<"本车可以移动到的墙X坐标极限位置 ="<<XlimitToTheWall<<endl;
		log.Debug()<<"本车是否可以移动返回值 ="<<retCanMove<<"  returned"<<endl;
		return retCanMove;
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
