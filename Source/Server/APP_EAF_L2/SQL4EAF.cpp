#include "SQL4EAF.h"


using namespace Monitor;



SQL4EAF::SQL4EAF(void)
{
}



SQL4EAF::~SQL4EAF(void)
{
}

bool SQL4EAF:: InsEAFL2PlanMain(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4EAF :: insertEAFL2PlanMain()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_EAF_L2_PLAN_MAIN( ";
		strSql += "PONO, ";
		strSql += "HTNO, ";
		strSql += "RECIPE_TYPE, ";
		strSql += "STEELGRADE, ";
		strSql += "TAP_TIME, ";
		strSql += "PLAN_SRC, ";
		strSql += "REC_TIME )";		

		strSql += " VALUES( :p_PONO,";
		strSql += " :p_HTNO, ";
		strSql += " :p_RECIPE_TYPE, ";
		strSql += " :p_STEELGRADE, ";
		strSql += " :p_TAP_TIME, ";
		strSql += " :p_PLAN_SRC, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PONO") = sd["PONO"].toString();
		cmd.Param("p_HTNO") =sd["HTNO"].toString();
		cmd.Param("p_RECIPE_TYPE") =sd["RECIPE_TYPE"].toString();
		cmd.Param("p_STEELGRADE") =sd["STEELGRADE"].toString();

		string strDate = sd["TAP_TIME"].toString();		
		cmd.Param("p_TAP_TIME") =iDA::DateTime(strDate);

		cmd.Param("p_PLAN_SRC") =sd["PLAN_SRC"].toString();

		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" insertEAFL2PlanMain Sucess! "<<endl;


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

bool SQL4EAF:: InsEAFL2PlanDetailSingle(string pono,			//制造命令号
																			   string basketID,	//料篮号
																			   string pitNO,			//坑位号
																			   long layNO,			//层号
																			   string scrID,			//废钢ID
																			   long scrWeight,	//废钢量
																			   string layValid, //层号合法性
																			   string status)			//装车状态 （1-未开始 2-已启动 3-已完成）
{

	bool ret=false;
	string functionName="SQL4EAF :: insertEAFL2PlanDetailSingle()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//20220707 获取OPER_ID
		string operID = "";
		if (false == SelOperID4DL(operID))
		{
			log.Info()<<"SelOperID4DL is error... return false....."<<endl;
			ret = false;
			return ret;
		}
		


		string strSql="";
		strSql="INSERT INTO  UACS_EAF_L2_PLAN_DETAIL( ";
		strSql += "OPER_ID, ";
		strSql += "PONO, ";
		strSql += "B_SEQ_NUM, ";
		strSql += "PIT_NUM, ";
		strSql += "LAY_NO, ";
		strSql += "SCR_ID, ";
		strSql += "SCR_WEIGHT,";
		strSql += "LAY_VALID, ";
		strSql += "STATUS,";
		strSql += "REC_TIME )";

		strSql += " VALUES( :p_OPER_ID,";//实绩流水号
		strSql += " :p_PONO, ";	//制造命令号
		strSql += " :p_B_SEQ_NUM, ";	//料篮号
		strSql += " :p_PIT_NUM, ";			//坑位号
		strSql += " :p_LAY_NO, ";			//层号
		strSql += " :p_SCR_ID, ";				//废钢号
		strSql += " :p_SCR_WEIGHT,";	//废钢量
		strSql += " :p_LAY_VALID, ";			//
		strSql += " :p_STATUS, ";			//装车状态
		strSql += " :p_REC_TIME )";		//记录时间

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPER_ID") =operID;
		cmd.Param("p_PONO") =pono;
		cmd.Param("p_B_SEQ_NUM") =basketID;
		cmd.Param("p_PIT_NUM") =pitNO;
		cmd.Param("p_LAY_NO") =layNO;
		cmd.Param("p_SCR_ID") =scrID;
		cmd.Param("p_SCR_WEIGHT") =scrWeight;
		cmd.Param("p_LAY_VALID") =layValid;
		cmd.Param("p_STATUS") =status;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" insertEAFL2PlanDetailSingle Sucess! "<<endl;


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


bool SQL4EAF:: SelEAFPlanInfoMain(string pono, EAFPlanInfoMain& planInfoMain)
{

	bool ret=false;
	string functionName="SQL4EAF :: SelEAFPlanInfoMain()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		planInfoMain.setPono(pono);

		long nCount = 0;
		string strSql="";
		strSql = "SELECT *  FROM UACS_EAF_L2_PLAN_MAIN WHERE PONO =:p_PONO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PONO") = pono;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;

			if(!cmd.Field("HTNO").IsNull())
			{
				string htno = cmd.Field("HTNO").AsString();
				planInfoMain.setHtno(htno);
			}

			if(!cmd.Field("RECIPE_TYPE").IsNull())
			{
				string recipeType = cmd.Field("RECIPE_TYPE").AsString();
				planInfoMain.setRecipeType(recipeType);
			}

			if(!cmd.Field("STEELGRADE").IsNull())
			{
				string steelGrade = cmd.Field("STEELGRADE").AsString();
				planInfoMain.setSteelGrade(steelGrade);
			}

			if(!cmd.Field("TAP_TIME").IsNull())
			{
				iDA::DateTime tapTime = cmd.Field("TAP_TIME").AsDateTime();
				planInfoMain.setTapTime(tapTime);
			}

			if(!cmd.Field("PLAN_SRC").IsNull())
			{
				string planSrc = cmd.Field("PLAN_SRC").AsString();
				planInfoMain.setPlanSrc(planSrc);
			}

		}
		if (nCount > 0)
		{
			ret = true;
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


bool SQL4EAF:: SelEAFPlanInfoDetail(string pono, vector<EAFPlanInfoDetail>& vecEAFPlanInfoDetail)
{

	bool ret=false;
	string functionName="SQL4EAF :: SelEAFPlanInfoDetail()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		EAFPlanInfoDetail planInfoDetail;
		planInfoDetail.setPono(pono);

		long nCount = 0;
		string strSql="";
		strSql = "SELECT *  FROM UACS_EAF_L2_PLAN_DETAIL WHERE ";
		strSql += " PONO =:p_PONO  AND ";
		strSql += " LAY_VALID =:p_LAY_VALID  ";
		strSql += " ORDER BY  B_SEQ_NUM , LAY_NO";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		
		cmd.Param("p_LAY_VALID") = EAFPlanInfoDetail::LAY_VALID_YES;
		cmd.Param("p_PONO") = pono;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;

			//0
			if(!cmd.Field("OPER_ID").IsNull())
			{
				string operID = cmd.Field("OPER_ID").AsString();
				planInfoDetail.setOperID(operID);
			}

			//1
			if(!cmd.Field("DETAIL_ID").IsNull())
			{
				long detailID = cmd.Field("DETAIL_ID").AsLong();
				planInfoDetail.setDetailID(detailID);
			}

			//2
			if(!cmd.Field("PONO").IsNull())
			{
				string pono = cmd.Field("PONO").AsString();
				planInfoDetail.setPono(pono);
			}

			//3
			if(!cmd.Field("B_SEQ_NUM").IsNull())
			{
				string bSeqNum = cmd.Field("B_SEQ_NUM").AsString();
				planInfoDetail.setBSeqNum(bSeqNum);
			}

			//4
			if(!cmd.Field("PIT_NUM").IsNull())
			{
				string pitNum = cmd.Field("PIT_NUM").AsString();
				planInfoDetail.setPitNum(pitNum);
			}

			//5
			if(!cmd.Field("LAY_NO").IsNull())
			{
				long layNO = cmd.Field("LAY_NO").AsLong();
				planInfoDetail.setLayNO(layNO);
			}

			//6
			if(!cmd.Field("SCR_ID").IsNull())
			{
				string scrID = cmd.Field("SCR_ID").AsString();
				planInfoDetail.setScrID(scrID);
			}

			//7
			if(!cmd.Field("SCR_WEIGHT").IsNull())
			{
				long scrWeight = cmd.Field("SCR_WEIGHT").AsLong();
				planInfoDetail.setScrWeight(scrWeight);
			}

			//8
			if(!cmd.Field("CRANE_WEIGHT").IsNull())
			{
				long craneWeight = cmd.Field("CRANE_WEIGHT").AsLong();
				planInfoDetail.setCraneWeight(craneWeight);
			}

			//9
			if(!cmd.Field("SCL_WEIGHT").IsNull())
			{
				long sclWeight = cmd.Field("SCL_WEIGHT").AsLong();
				planInfoDetail.setSclWeight(sclWeight);
			}

			//10
			if(!cmd.Field("CAR_NO").IsNull())
			{
				string carNO = cmd.Field("CAR_NO").AsString();
				planInfoDetail.setCarNO(carNO);
			}

			//11
			if(!cmd.Field("GRID_NO").IsNull())
			{
				string gridNO = cmd.Field("GRID_NO").AsString();
				planInfoDetail.setGridNO(gridNO);
			}

			//12
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				string matCode = cmd.Field("MAT_CODE").AsString();
				planInfoDetail.setMatCode(matCode);
			}

			//13
			if(!cmd.Field("COMP_CODE").IsNull())
			{
				string compCode = cmd.Field("COMP_CODE").AsString();
				planInfoDetail.setCompCode(compCode);
			}

			//14
			if(!cmd.Field("LAY_VALID").IsNull())
			{
				string layValid = cmd.Field("LAY_VALID").AsString();
				planInfoDetail.setLayValid(layValid);
			}

			//15
			if(!cmd.Field("STATUS").IsNull())
			{
				string status = cmd.Field("STATUS").AsString();
				planInfoDetail.setStatus(status);
			}

			vecEAFPlanInfoDetail.push_back(planInfoDetail);

		}
		if (nCount > 0)
		{
			ret = true;
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


bool SQL4EAF:: SelEAFPlanInfoDetailByDetailID(long planDetailID, EAFPlanInfoDetail& planInfoDetail)
{

	bool ret=false;
	string functionName="SQL4EAF :: SelEAFPlanInfoDetailByDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT *  FROM UACS_EAF_L2_PLAN_DETAIL WHERE ";
		strSql += " DETAIL_ID =:p_DETAIL_ID  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_DETAIL_ID") = planDetailID;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;

			//0
			if(!cmd.Field("OPER_ID").IsNull())
			{
				string operID = cmd.Field("OPER_ID").AsString();
				planInfoDetail.setOperID(operID);
			}

			//1
			if(!cmd.Field("DETAIL_ID").IsNull())
			{
				long detailID = cmd.Field("DETAIL_ID").AsLong();
				planInfoDetail.setDetailID(detailID);
			}

			//2
			if(!cmd.Field("PONO").IsNull())
			{
				string pono = cmd.Field("PONO").AsString();
				planInfoDetail.setPono(pono);
			}

			//3
			if(!cmd.Field("B_SEQ_NUM").IsNull())
			{
				string bSeqNum = cmd.Field("B_SEQ_NUM").AsString();
				planInfoDetail.setBSeqNum(bSeqNum);
			}

			//4
			if(!cmd.Field("PIT_NUM").IsNull())
			{
				string pitNum = cmd.Field("PIT_NUM").AsString();
				planInfoDetail.setPitNum(pitNum);
			}

			//5
			if(!cmd.Field("LAY_NO").IsNull())
			{
				long layNO = cmd.Field("LAY_NO").AsLong();
				planInfoDetail.setLayNO(layNO);
			}

			//6
			if(!cmd.Field("SCR_ID").IsNull())
			{
				string scrID = cmd.Field("SCR_ID").AsString();
				planInfoDetail.setScrID(scrID);
			}

			//7
			if(!cmd.Field("SCR_WEIGHT").IsNull())
			{
				long scrWeight = cmd.Field("SCR_WEIGHT").AsLong();
				planInfoDetail.setScrWeight(scrWeight);
			}

			//8
			if(!cmd.Field("CRANE_WEIGHT").IsNull())
			{
				long craneWeight = cmd.Field("CRANE_WEIGHT").AsLong();
				planInfoDetail.setCraneWeight(craneWeight);
			}

			//9
			if(!cmd.Field("SCL_WEIGHT").IsNull())
			{
				long sclWeight = cmd.Field("SCL_WEIGHT").AsLong();
				planInfoDetail.setSclWeight(sclWeight);
			}

			//10
			if(!cmd.Field("CAR_NO").IsNull())
			{
				string carNO = cmd.Field("CAR_NO").AsString();
				planInfoDetail.setCarNO(carNO);
			}

			//11
			if(!cmd.Field("GRID_NO").IsNull())
			{
				string gridNO = cmd.Field("GRID_NO").AsString();
				planInfoDetail.setGridNO(gridNO);
			}

			//12
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				string matCode = cmd.Field("MAT_CODE").AsString();
				planInfoDetail.setMatCode(matCode);
			}

			//13
			if(!cmd.Field("COMP_CODE").IsNull())
			{
				string compCode = cmd.Field("COMP_CODE").AsString();
				planInfoDetail.setCompCode(compCode);
			}

			//14
			if(!cmd.Field("LAY_VALID").IsNull())
			{
				string layValid = cmd.Field("LAY_VALID").AsString();
				planInfoDetail.setLayValid(layValid);
			}

			//15
			if(!cmd.Field("STATUS").IsNull())
			{
				string status = cmd.Field("STATUS").AsString();
				planInfoDetail.setStatus(status);
			}
		}
		if (nCount > 0)
		{
			ret = true;
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




bool SQL4EAF:: UpdatePlanMain(string pono, 
														  string htno, 
														  string recipeType, 
														  string steelGrade, 
														  string tapTime,
														  string planSrc)		
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdatePlanMain()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_MAIN SET ";
		strSql += " HTNO = :p_HTNO, ";
		strSql += " RECIPE_TYPE = :p_RECIPE_TYPE,  ";
		strSql += " STEELGRADE = :p_STEELGRADE,";
		strSql += " TAP_TIME = :p_TAP_TIME,  ";
		strSql += " PLAN_SRC = :p_PLAN_SRC, ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE PONO = :p_PONO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_HTNO") =htno;
		cmd.Param("p_RECIPE_TYPE") = recipeType;
		cmd.Param("p_STEELGRADE") = steelGrade;
		cmd.Param("p_TAP_TIME") = iDA::DateTime(tapTime);
		cmd.Param("p_PLAN_SRC") = planSrc;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();
		cmd.Param("p_PONO") =pono;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdatePlanMain Sucess! "<<endl;


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

bool SQL4EAF:: SelMainPlanInfo(string planNO, string& recipeType)
{

	bool ret=false;
	string functionName="SQL4EAF :: SelMainPlanInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT *  FROM UACS_EAF_L2_PLAN_MAIN  WHERE  PONO =:p_PONO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PONO") = planNO;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount++;
			if(!cmd.Field("RECIPE_TYPE").IsNull())
			{
				recipeType = cmd.Field("RECIPE_TYPE").AsString();
			}
		}
		if (nCount > 0)
		{
			ret = true;
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

bool SQL4EAF:: SelDetailPlanInfo(string planNO, 
															 long planDetailID, 
															 string& status,
															 string& layValid)
{

	bool ret=false;
	string functionName="SQL4EAF :: SelDetailPlanInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT *  FROM UACS_EAF_L2_PLAN_DETAIL  WHERE  PONO =:p_PONO AND DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PONO") = planNO;
		cmd.Param("p_DETAIL_ID") = planDetailID;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount++;
			if(!cmd.Field("STATUS").IsNull())
			{
				status = cmd.Field("STATUS").AsString();				
			}
			if(!cmd.Field("LAY_VALID").IsNull())
			{
				layValid = cmd.Field("LAY_VALID").AsString();				
			}
			break;
		}
		if (nCount > 0)
		{
			ret = true;
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



bool SQL4EAF:: UpdCarNOInPlanDetail(string planNO, 
																		long planDetailID, 
																		string carNO)
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdCarNOInPlanDetail()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_DETAIL SET  ";
		strSql += " CAR_NO = :p_CAR_NO  WHERE  ";
		strSql += " DETAIL_ID = :p_DETAIL_ID AND ";
		strSql += " PONO = :p_PONO ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_DETAIL_ID") = planDetailID;
		cmd.Param("p_PONO") = planNO;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdCarNOInPlanDetail Sucess! "<<endl;


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


bool SQL4EAF:: SelCarPlanBand(string planNO, 
														  long planDetailID, 
														  string& enterFlag, 
														  string& orderFlag)
{

	bool ret=false;
	string functionName="SQL4EAF :: SelCarPlanBand()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT *  FROM UACS_PARKING_CAR_PLAN_INFO  WHERE  ";
		//strSql += " CAR_NO = :p_CAR_NO AND  ";
		strSql += " PLAN_NO = :p_PLAN_NO  AND  ";
		strSql += " PLAN_DETAIL_ID = :p_PLAN_DETAIL_ID AND  ";
		strSql += " PLAN_SRC = :p_PLAN_SRC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		string planSrc = "EAF";
		//cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_PLAN_DETAIL_ID") = planDetailID;
		cmd.Param("p_PLAN_SRC") = planSrc;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount++;
			if(!cmd.Field("ENTER_FLAG").IsNull())
			{
				enterFlag = cmd.Field("ENTER_FLAG").AsString();
			}
			if(!cmd.Field("ORDER_FLAG").IsNull())
			{
				orderFlag = cmd.Field("ORDER_FLAG").AsString();
			}
			break;
		}
		if (nCount > 0)
		{
			ret = true;
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


bool SQL4EAF:: InsCarPlanBand(string carNO, 
														  string carType, 
														  string workType, 
														  string planNO, 
														  string planSrc, 
														  long planDetailID, 
														  string enterFlag, 
														  string orderFlag,
														  iDA::DateTime bandTime )
{

	bool ret=false;
	string functionName="SQL4EAF :: InsCarPlanBand()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "INSERT INTO  UACS_PARKING_CAR_PLAN_INFO(  ";
		strSql += " CAR_NO, ";
		strSql += " CAR_TYPE, ";
		strSql += " WORK_TYPE, ";
		strSql += " PLAN_NO, ";
		strSql += " PLAN_SRC, ";
		strSql += " PLAN_DETAIL_ID, ";
		strSql += " ENTER_FLAG, ";
		strSql += " ORDER_FLAG, ";
		strSql += " BAND_TIME )  ";

		strSql += " VALUES( ";
		strSql += " :p_CAR_NO, ";
		strSql += " :p_CAR_TYPE, ";
		strSql += " :p_WORK_TYPE, ";
		strSql += " :p_PLAN_NO, ";
		strSql += " :p_PLAN_SRC, ";
		strSql += " :p_PLAN_DETAIL_ID, ";
		strSql += " :p_ENTER_FLAG, ";
		strSql += " :p_ORDER_FLAG, ";
		strSql += " :p_BAND_TIME)";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_CAR_TYPE") = carType;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_PLAN_SRC") = planSrc;
		cmd.Param("p_PLAN_DETAIL_ID") = planDetailID;
		cmd.Param("p_ENTER_FLAG") = enterFlag;
		cmd.Param("p_ORDER_FLAG") = orderFlag;
		cmd.Param("p_BAND_TIME") = bandTime;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" InsCarPlanBand Success! "<<endl;


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


bool SQL4EAF:: UpdCarPlanBand(string carNO, 
															   string planNO, 
															   long planDetailID )
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdCarPlanBand()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE  UACS_PARKING_CAR_PLAN_INFO  SET  ";
		strSql += " CAR_NO = :p_CAR_NO WHERE  ";
		strSql += " PLAN_NO = :p_PLAN_NO  AND  ";
		strSql += " PLAN_DETAIL_ID = :p_PLAN_DETAIL_ID  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_PLAN_DETAIL_ID") = planDetailID;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdCarPlanBand Success! "<<endl;


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


bool SQL4EAF:: DelCarPlanBandByDetailID(long detailID)
{

	bool ret=false;
	string functionName="SQL4EAF :: DelCarPlanBandByPonoDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "DELETE  FROM UACS_PARKING_CAR_PLAN_INFO  ";
		strSql += " WHERE  ";
		strSql += " PLAN_DETAIL_ID = :p_PLAN_DETAIL_ID AND ";
		strSql += " PLAN_SRC = 'EAF'  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_DETAIL_ID") = detailID;

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;
		log.Debug()<<" DelCarPlanBandByPonoDetailID Success! "<<endl;

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


bool SQL4EAF:: UpdDetailInvalidByDetailID(long detailID)
{
	bool ret=false;
	string functionName="SQL4EAF :: UpdDetailInvalidByPonoDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE  UACS_EAF_L2_PLAN_DETAIL  SET  ";
		strSql += " LAY_VALID = :p_LAY_VALID  WHERE  ";
		strSql += " DETAIL_ID = :p_DETAIL_ID  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_LAY_VALID") = EAFPlanInfoDetail::LAY_VALID_NO;
		cmd.Param("p_DETAIL_ID") = detailID;

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;
		log.Debug()<<" UpdDetailInvalidByPonoDetailID Success! "<<endl;
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


bool SQL4EAF:: UpdPlanDetailByDetailID(long detailID, string scrID, long scrWeight)
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdPlanDetailByDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_DETAIL SET ";
		strSql += " SCR_ID = :p_SCR_ID, ";
		strSql += " SCR_WEIGHT = :p_SCR_WEIGHT,  ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ";
		strSql += " DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SCR_ID") = scrID;
		cmd.Param("p_SCR_WEIGHT") = scrWeight;
		cmd.Param("p_DETAIL_ID") = detailID;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdPlanDetailByDetailID Success! "<<endl;


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


bool SQL4EAF:: UpdPlanDetailInvalidByDetailID(long detailID)
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdPlanDetailInvalidByDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_DETAIL SET ";
		strSql += " LAY_VALID = :p_LAY_VALID, ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ";
		strSql += " DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_LAY_VALID") = EAFPlanInfoDetail::LAY_VALID_NO;
		cmd.Param("p_DETAIL_ID") = detailID;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdPlanDetailInvalidByDetailID Success! "<<endl;


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


bool SQL4EAF:: UpdPlanDetailStatusByDetailID(long detailID, string stauts)
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdPlanDetailStatusByDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_DETAIL SET ";
		strSql += " STATUS = :p_STATUS, ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ";
		strSql += " DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STATUS") = stauts;
		cmd.Param("p_DETAIL_ID") = detailID;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdPlanDetailStatusByDetailID Success! "<<endl;


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

bool SQL4EAF:: SelOperID4DL(string& operID)
{

	bool ret=false;
	string functionName="SQL4BOF :: SelOperID4DL()";
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
		operID = "DL" + StringHelper::ToString(nOperID);
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


bool SQL4EAF:: DelEAFPlanDetailByID(long detailID)
{

	bool ret=false;
	string functionName="SQL4EAF :: DelEAFPlanDetailByID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "DELETE  FROM UACS_EAF_L2_PLAN_DETAIL  ";
		strSql += " WHERE  ";
		strSql += " DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_DETAIL_ID") = detailID;

		cmd.Execute();
		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;
		log.Debug()<<" DelEAFPlanDetailByID Success! "<<endl;

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


bool SQL4EAF:: UpdEAFPlanDetailMatInfo(string pono, 
																			   long detailID, 
																			   string gridNO, 
																			   string matCode, 
																			   string compCode, 
																			   long matWgt)
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdEAFPlanDetailMatInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_DETAIL SET ";
		strSql += " GRID_NO = :p_GRID_NO, ";
		strSql += " MAT_CODE = :p_MAT_CODE, ";
		strSql += " COMP_CODE = :p_COMP_CODE, ";
		strSql += " CRANE_WEIGHT = NVL(CRANE_WEIGHT,0) + :p_CRANE_WEIGHT, ";//累加重量
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ";
		strSql += " PONO = :p_PONO  AND ";
		strSql += " DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GRID_NO") = gridNO;
		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Param("p_COMP_CODE") = compCode;
		cmd.Param("p_CRANE_WEIGHT") = matWgt;
		cmd.Param("p_PONO") = pono;
		cmd.Param("p_DETAIL_ID") = detailID;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdEAFPlanDetailMatInfo Success! "<<endl;


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


bool SQL4EAF:: UpdEAFPlanDetailSclWgt(string operID, long sclWgt)
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdEAFPlanDetailSclWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_DETAIL SET ";
		strSql += " SCL_WEIGHT = :p_SCL_WEIGHT, ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ";
		strSql += " OPER_ID = :p_OPER_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SCL_WEIGHT") = sclWgt;
		cmd.Param("p_OPER_ID") = operID;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdEAFPlanDetailSclWgt Success! "<<endl;


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


bool SQL4EAF:: SelGridMatCompCraneWgt(string operID, 
																			  string& gridNO,
																			  string& matCode, 
																			  string& compCode, 
																			  long& craneWgt)
{
	bool ret=false;
	string functionName="SQL4BOF :: SelGridMatCompCraneWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " SELECT NVL(CRANE_WEIGHT, 0)  AS  CRANE_WEIGHT, ";
		strSql += " GRID_NO, MAT_CODE, COMP_CODE  FROM UACS_EAF_L2_PLAN_DETAIL  WHERE  ";
		strSql += " OPER_ID = :p_OPER_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPER_ID") = operID;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("CRANE_WEIGHT").IsNull())
			{
				craneWgt = cmd.Field("CRANE_WEIGHT").AsLong();
			}
			if(!cmd.Field("GRID_NO").IsNull())
			{
				gridNO = cmd.Field("GRID_NO").AsString();
			}
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				matCode = cmd.Field("MAT_CODE").AsString();
			}
			if(!cmd.Field("COMP_CODE").IsNull())
			{
				compCode = cmd.Field("COMP_CODE").AsString();
			}
			break;
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


bool SQL4EAF:: SelPlanNOByOperID(string operID, string& planNO, long& detailID)
{
	bool ret=false;
	string functionName="SQL4BOF :: SelPlanNOByOperID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " SELECT * FROM  UACS_EAF_L2_PLAN_DETAIL  WHERE ";
		strSql += " OPER_ID = :p_OPER_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPER_ID") = operID;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("DETAIL_ID").IsNull())
			{
				detailID = cmd.Field("DETAIL_ID").AsLong();
			}
			if(!cmd.Field("PONO").IsNull())
			{
				planNO = cmd.Field("PONO").AsString();
			}
			break;
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


bool SQL4EAF:: UpdEAFPlanDetailStatus(long planDetailID, string status)
{

	bool ret=false;
	string functionName="SQL4EAF :: UpdEAFPlanDetailStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE UACS_EAF_L2_PLAN_DETAIL SET ";
		strSql += " STATUS = :p_STATUS,  ";
		strSql += " UPD_TIME = :p_UPD_TIME  ";
		strSql += " WHERE ";
		strSql += " DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STATUS") = status;
		cmd.Param("p_DETAIL_ID") = planDetailID;
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdEAFPlanDetailStatus Success! "<<endl;


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
