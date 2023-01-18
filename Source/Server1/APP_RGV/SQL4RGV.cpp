#include <climits>
#include "SQL4RGV.h"

using namespace Monitor;



SQL4RGV::SQL4RGV(void)
{
}



SQL4RGV::~SQL4RGV(void)
{
}


bool SQL4RGV:: UpdRGVStatusArrive(string parkingNO, 
														string rgvNO, 
														string loadFlag, 
														string troughDir)
{
	bool ret=false;
	string functionName="SQL4RGV :: UpdRGVStatusArrive()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//获取指令号
		string strSql = "";		
		strSql = "UPDATE  UACS_PARKING_RGV_STATUS  SET ";
		strSql += " RGV_NO = :p_RGV_NO,  ";
		strSql += " LOAD_FLAG = :p_LOAD_FLAG, ";
		strSql += " TROUGH_DIR = :p_TROUGH_DIR, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  PARKING_NO  = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_RGV_NO") = rgvNO;
		cmd.Param("p_LOAD_FLAG") = loadFlag;
		cmd.Param("p_TROUGH_DIR") = troughDir;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();
		cmd.Param("p_PARKING_NO") = parkingNO;

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret = true;

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


bool SQL4RGV:: UpdRGVStatusLock(string rgvNO)
{
	bool ret=false;
	string functionName="SQL4RGV :: UpdRGVStatusLock()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//获取指令号
		string strSql = "";		
		strSql = "UPDATE  UACS_PARKING_RGV_STATUS  SET ";
		strSql += " LOCK_FLAG = :p_LOCK_FLAG, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  RGV_NO  = :p_RGV_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		string lockFlag = "1";
		cmd.Param("p_RGV_NO") = rgvNO;
		cmd.Param("p_LOCK_FLAG") = lockFlag;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret = true;

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

bool SQL4RGV:: InitRGVStatusUnlock(string rgvNO)
{
	bool ret=false;
	string functionName="SQL4RGV :: InitRGVStatusUnlock()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//获取指令号
		string strSql = "";		
		strSql = "UPDATE  UACS_PARKING_RGV_STATUS  SET ";
		strSql += " RGV_NO = NULL, ";
		strSql += " LOAD_FLAG = NULL, ";
		strSql += " TROUGH_DIR = NULL, ";
		strSql += " BAND_STEEL_NO = NULL, ";
		strSql += " LOCK_FLAG = NULL, ";
		strSql += " POINT_X_MIN = NULL, ";
		strSql += " POINT_X_MAX = NULL, ";
		strSql += " POINT_Y_MIN = NULL, ";
		strSql += " POINT_Y_MAX = NULL, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  RGV_NO  = :p_RGV_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		string lockFlag = "1";
		cmd.Param("p_RGV_NO") = rgvNO;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret = true;

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
