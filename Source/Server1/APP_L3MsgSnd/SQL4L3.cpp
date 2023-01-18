#include <climits>
#include "SQL4L3.h"

using namespace Monitor;



SQL4L3::SQL4L3(void)
{
}



SQL4L3::~SQL4L3(void)
{
}


bool SQL4L3:: UpdL3PLanStatus(string workSeqNO, string planStatus)
{

	bool ret=false;
	string functionName="SQL4L3 :: UpdL3PLanStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql=" UPDATE  UACS_L3_MAT_IN_OUT_INFO  SET  ";
		strSql += "PLAN_STATUS = :p_PLAN_STATUS, ";
		strSql += "UPD_TIME = :p_UPD_TIME ";
		strSql += "WHERE   WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_STATUS") = planStatus;
		cmd.Param("p_UPD_TIME") =iDA::DateTime::Now();
		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdL3PLanStatus Success! "<<endl;
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


bool SQL4L3:: UpdL3PlanCraneWgtZC(string workSeqNO, long craneWgtZC)
{

	bool ret=false;
	string functionName="SQL4L3 :: UpdL3PlanCraneWgtZC()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql=" UPDATE  UACS_L3_MAT_IN_OUT_INFO  SET  ";
		strSql += "CRANE_WGT_ZC = NVL(CRANE_WGT_ZC, 0) + :p_CRANE_WGT_ZC, ";
		strSql += "UPD_TIME = :p_UPD_TIME ";
		strSql += "WHERE   WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CRANE_WGT_ZC") = craneWgtZC;
		cmd.Param("p_UPD_TIME") =iDA::DateTime::Now();
		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdL3PlanCraneWgtZC Success! "<<endl;
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


bool SQL4L3:: UpdL3PlanCraneWgtXL(string workSeqNO, long craneWgtXL)
{

	bool ret=false;
	string functionName="SQL4L3 :: UpdL3PlanCraneWgtXL()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql=" UPDATE  UACS_L3_MAT_IN_OUT_INFO  SET  ";
		strSql += "CRANE_WGT_XL = NVL(CRANE_WGT_XL, 0) + :p_CRANE_WGT_XL, ";
		strSql += "UPD_TIME = :p_UPD_TIME ";
		strSql += "WHERE   WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CRANE_WGT_XL") = craneWgtXL;
		cmd.Param("p_UPD_TIME") =iDA::DateTime::Now();
		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdL3PlanCraneWgtXL Success! "<<endl;
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