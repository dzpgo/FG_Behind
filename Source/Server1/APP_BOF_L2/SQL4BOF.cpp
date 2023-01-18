#include <climits>
#include "SQL4BOF.h"

using namespace Monitor;



SQL4BOF::SQL4BOF(void)
{
}



SQL4BOF::~SQL4BOF(void)
{
}

bool SQL4BOF:: InsertBOFL2PlanMain(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4BOF :: insertBOFL2PlanMain()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string operID = "";
		if (false == SelOperID4LG(operID))
		{
			log.Info()<<"SelOperID4LG is error... return false....."<<endl;
			ret = false;
			return ret;
		}


		string planStatus = "1";
		string planValid= "1";

		string strSql="";
		strSql="INSERT INTO  UACS_BOF_L2_PLAN_MAIN( ";
		strSql += "OPER_ID, ";
		strSql += "STEEL_NO, ";
		strSql += "PLAN_TYPE, ";
		strSql += "PLAN_FLAG, ";
		strSql += "PLAN_STATUS, ";
		strSql += "PLAN_VALID, ";
		strSql += "REC_TIME )";
		

		strSql += " VALUES( ";
		strSql += " :p_OPER_ID,";
		strSql += " :p_STEEL_NO,";
		strSql += " :p_PLAN_TYPE, ";
		strSql += " :p_PLAN_FLAG, ";
		strSql += " :p_PLAN_STATUS, ";
		strSql += " :p_PLAN_VALID, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPER_ID") = operID;
		cmd.Param("p_STEEL_NO") = sd["STEEL_NO"].toString();
		cmd.Param("p_PLAN_TYPE") =sd["PLAN_TYPE"].toString();
		cmd.Param("p_PLAN_FLAG") =sd["PLAN_FLAG"].toString();
		cmd.Param("p_PLAN_STATUS") = planStatus;
		cmd.Param("p_PLAN_VALID") = planValid;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" insertBOFL2PlanMain Sucess! "<<endl;


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

bool SQL4BOF:: InsertBOFL2PlanDetail(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4BOF :: insertBOFL2PlanDetail()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string steelNO = sd["STEEL_NO"].toString();	//制造命令号
		int scrID;			//废钢ID
		int scrWeight;	//废钢量

		for (int index = 0; index < 20; index++)
		{
			scrID = sd["BU01_DETAIL"][index]["SCRAP_CODE"].toInt();
			if (scrID == INT_MIN)
			{
				log.Info()<<"BU01_DETAIL, index = "<<index<<", scrID = "<<scrID<<",  is not need to treat.........."<<endl;
				continue;
			}
			string strScrID = StringHelper::ToString(scrID);
			scrWeight = sd["BU01_DETAIL"][index]["REQ_WEIGHT"].toInt();
			if (scrWeight == INT_MIN)
			{
				log.Info()<<"BU01_DETAIL, index = "<<index<<", scrWeight = "<<scrWeight<<", ready to set scrWeight=0.........."<<endl;
				scrWeight = 0;
			}
			InsertBOFL2PlanDetailSingle( steelNO, strScrID, scrWeight);			
		}
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

bool SQL4BOF:: InsertBOFL2PlanDetailSingle(string steelNO, 
																			   string strScrID, 
																			   int scrWeight)			//装车状态 （1-未开始 2-已启动 3-已完成）
{

	bool ret=false;
	string functionName="SQL4BOF :: insertBOFL2PlanDetailSingle()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string planValid = "1";
		string strSql="";
		strSql="INSERT INTO  UACS_BOF_L2_PLAN_DETAIL( ";
		strSql += "STEEL_NO, ";
		strSql += "PLAN_VALID, ";
		strSql += "SCRAP_CODE, ";
		strSql += "REQ_WEIGHT, ";
		strSql += "REC_TIME )";

		strSql += " VALUES( :p_STEEL_NO,";//钢号
		strSql += " :p_PLAN_VALID, ";	//废钢号
		strSql += " :p_SCRAP_CODE, ";	//废钢号
		strSql += " :p_REQ_WEIGHT, ";			//废钢量
		strSql += " :p_REC_TIME )";		//记录时间

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STEEL_NO") =steelNO;
		cmd.Param("p_PLAN_VALID") =planValid;
		cmd.Param("p_SCRAP_CODE") =strScrID;
		cmd.Param("p_REQ_WEIGHT") =(long)scrWeight;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" insertBOFL2PlanDetailSingle Sucess! "<<endl;


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


bool SQL4BOF:: BOFL2PlanExist(string steelNO, string& planStatus)
{

	bool ret=false;
	string functionName="SQL4BOF :: BOFL2PlanExist()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_BOF_L2_PLAN_MAIN WHERE STEEL_NO =:p_STEEL_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STEEL_NO") = steelNO;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("PLAN_STATUS").IsNull())
			{
				planStatus = cmd.Field("PLAN_STATUS").AsString();
			}
		}
		if (nCount > 0)
		{
			ret = true;
		}
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


bool SQL4BOF:: UpdatePlanMain(string steelNO, string planType, string planFlag)//钢号
{

	bool ret=false;
	string functionName="SQL4BOF :: UpdatePlanMain()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_BOF_L2_PLAN_MAIN SET ";
		strSql += " PLAN_TYPE = :p_PLAN_TYPE, ";
		strSql += " PLAN_FLAG = :p_PLAN_FLAG,  ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE STEEL_NO = :p_STEEL_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_TYPE") = planType;
		cmd.Param("p_PLAN_FLAG") = planFlag;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();
		cmd.Param("p_STEEL_NO") = steelNO;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdatePlanMain Sucess! "<<endl;


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

bool SQL4BOF:: UpdatePlanDetailPlanValid(string steelNO)//钢号
{

	bool ret=false;
	string functionName="SQL4BOF :: UpdatePlanDetailPlanValid()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string planValid = "2";
		string strSql="";
		strSql = "UPDATE UACS_BOF_L2_PLAN_DETAIL SET ";
		strSql += " PLAN_VALID = :p_PLAN_VALID, ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE STEEL_NO = :p_STEEL_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("PLAN_VALID") = planValid;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();
		cmd.Param("p_STEEL_NO") = steelNO;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdatePlanDetailPlanValid Sucess! "<<endl;


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


bool SQL4BOF:: DelPlanDetail(string steelNO)//钢号
{

	bool ret=false;
	string functionName="SQL4BOF :: DelPlanDetail()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "DELETE  FROM  UACS_BOF_L2_PLAN_DETAIL  WHERE STEEL_NO = :p_STEEL_NO";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STEEL_NO") = steelNO;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" DelPlanDetail Sucess! "<<endl;


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


bool SQL4BOF:: UpdatePlanMainPlanValid(string steelNO, string planType, string planFlag)//钢号
{

	bool ret=false;
	string functionName="SQL4BOF :: UpdatePlanMainPlanValid()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string planValid = "2";
		string strSql="";
		strSql = "UPDATE UACS_BOF_L2_PLAN_MAIN SET ";
		strSql += " PLAN_TYPE = :p_PLAN_TYPE, ";
		strSql += " PLAN_FLAG = :p_PLAN_FLAG, ";
		strSql += " PLAN_VALID = :p_PLAN_VALID, ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE STEEL_NO = :p_STEEL_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("PLAN_VALID") = planValid;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();
		cmd.Param("p_STEEL_NO") = steelNO;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdatePlanMainPlanValid Sucess! "<<endl;


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


bool SQL4BOF:: SelectPlanDetailMatWgt(string steelNO, map<string, long>& matDetail)
{

	bool ret=false;
	string functionName="SQL4BOF :: SelectPlanDetailMatWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_BOF_L2_PLAN_DETAIL WHERE STEEL_NO =:p_STEEL_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STEEL_NO") = steelNO;
		cmd.Execute();

		string matCode = "";
		long matWgt = 0;
		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SCRAP_CODE").IsNull())
			{
				matCode = cmd.Field("SCRAP_CODE").AsString();
			}
			if(!cmd.Field("REQ_WEIGHT").IsNull())
			{
				matWgt = cmd.Field("REQ_WEIGHT").AsLong();
			}
			matDetail.insert(map<string, long>::value_type(matCode, matWgt));
		}
		if (nCount > 0)
		{
			ret = true;
		}
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

bool SQL4BOF:: SelOperID4LG(string& operID)
{

	bool ret=false;
	string functionName="SQL4BOF :: SelOperID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nOperID = 0;
		long nCount = 0;
		string strSql="";
		//采用db2中的序列来记录指令号
		strSql = " SELECT SEQ_OPER_ID.NEXTVAL AS SEQ FROM SYSIBM.SYSDUMMY1 ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SEQ").IsNull())
			{
				nOperID = cmd.Field("SEQ").AsLong();
			}
			break;
		}
		if (nCount > 0)
		{
			ret = true;
		}
		operID = "LG" + StringHelper::ToString(nOperID);
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