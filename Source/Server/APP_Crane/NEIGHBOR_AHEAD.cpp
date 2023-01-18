#include "NEIGHBOR_AHEAD.h"



using namespace Monitor;

const string NEIGHBOR_AHEAD::NOBODY = "NOBODY";

const string NEIGHBOR_AHEAD::UNKNOW = "UNKNOW";



NEIGHBOR_AHEAD :: NEIGHBOR_AHEAD(void)
{


}



NEIGHBOR_AHEAD :: ~NEIGHBOR_AHEAD(void)
{



}




string NEIGHBOR_AHEAD ::getCraneNO(string craneNO, string direction)
{


	string functionName = "NEIGHBOR_AHEAD :: getCraneNO()";
	LOG log(functionName, AUTO_CATCH_PID);

	string neighborCraneNO=NEIGHBOR_AHEAD::UNKNOW;

	try
	{
		if( direction==MOVING_DIR::DIR_X_INC )
		{
			if (craneNO == "4_4")
			{
				neighborCraneNO = NEIGHBOR_AHEAD::NOBODY;
			}
			else if (craneNO == "4_5")
			{
				neighborCraneNO = "4_4";
			}
			else if (craneNO == "4_6")
			{
				neighborCraneNO = "4_5";
			}
			else if (craneNO == "4_7")
			{
				neighborCraneNO = "4_6";
			}
		}
		else if(  direction==MOVING_DIR::DIR_X_DES  )
		{
			if (craneNO == "4_4")
			{
				neighborCraneNO = "4_5";
			}
			else if (craneNO == "4_5")
			{
				neighborCraneNO = "4_6";
			}
			else if (craneNO == "4_6")
			{
				neighborCraneNO = "4_7";
			}
			else if (craneNO == "4_7")
			{
				neighborCraneNO = NEIGHBOR_AHEAD::NOBODY;
			}
		}
		log.Debug()<<"本车车号="<<craneNO<<"    本车运动方向="<<direction<<"  故得出本车的运动方向上邻车车号="<<neighborCraneNO<<endl;
		return neighborCraneNO;
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

	return neighborCraneNO;
}
