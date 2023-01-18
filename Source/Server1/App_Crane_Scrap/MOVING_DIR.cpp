#include "MOVING_DIR.h"



using namespace Monitor;

const string MOVING_DIR::DIR_X_INC = "X_INC";

const string MOVING_DIR::DIR_X_DES = "X_DES";

const string MOVING_DIR::DIR_X_ON_SPOT = "X_ON_SPOT";


MOVING_DIR :: MOVING_DIR(void)
{


}



MOVING_DIR :: ~MOVING_DIR(void)
{



}



//1 getDirection
string MOVING_DIR ::getDirection(string craneNO, long currentX , long targetX)
{


	string functionName = "MOVING_DIR :: getDirection()";
	LOG log(functionName, AUTO_CATCH_PID);

	string dir=MOVING_DIR::DIR_X_ON_SPOT;

	try
	{
		//如果目标X封9 那么方向是原地
		if(targetX==CranePLCOrderBase::PLC_INT_NULL)
		{
			log.Debug()<<"targetX==PLC_INT_NULL   the direction=DIR_X_ON_SPOT "<<endl;
			dir=MOVING_DIR::DIR_X_ON_SPOT;
			log.Info()<<"targetX = "<<targetX<<endl;			
		}

		//方向为X增加
		if(currentX<targetX)
		{
			log.Debug()<<"currentX<targetX   the direction=DIR_X_INC  "<<endl;
			dir=MOVING_DIR::DIR_X_INC;
			log.Info()<<"targetX = "<<targetX<<"currentX = "<<currentX<<endl;			
		}

		//方向为X减少
		if(currentX>targetX)
		{
			log.Debug()<<"currentX>targetX   the direction=DIR_X_DES  "<<endl;
			dir=MOVING_DIR::DIR_X_DES;
			log.Info()<<"targetX = "<<targetX<<"currentX = "<<currentX<<endl;		
		}

		//方向为原地不动
		if(currentX==targetX)
		{
			log.Debug()<<"currentX==targetX   the direction=DIR_X_ON_SPOT  "<<endl;
			dir=MOVING_DIR::DIR_X_ON_SPOT;
			log.Info()<<"targetX = "<<targetX<<"currentX = "<<currentX<<endl;		
		}

	
		return dir;

	
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

	return dir;
}
