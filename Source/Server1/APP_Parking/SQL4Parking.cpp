#include <climits>
#include "SQL4Parking.h"

using namespace Monitor;



SQL4Parking::SQL4Parking(void)
{
}



SQL4Parking::~SQL4Parking(void)
{
}



bool SQL4Parking:: SelCarPlanBandInfo(string carNO, CarPlanBandInfo& carPlanBandInfoBase)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelCarPlanBandInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string carType = "";
		string workType = "";
		string planNO = "";
		string planSrc = "";
		long planDetailID = 0;
		string enterFlag = "";
		string orderFlag = "";
		iDA::DateTime bandTime = DB_TIME_NULL;
		string gateNO = "";
		string targetGridNO = "";
		string recomParkingNO = "";

		carPlanBandInfoBase.setCarNO(carNO);

		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE CAR_NO =:p_CAR_NO ";
		strSql += " ORDER BY  BAND_TIME  ASC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("CAR_TYPE").IsNull())
			{
				carType = cmd.Field("CAR_TYPE").AsString();
				carPlanBandInfoBase.setCarType(carType);
			}
			if(!cmd.Field("WORK_TYPE").IsNull())
			{
				workType = cmd.Field("WORK_TYPE").AsString();
				carPlanBandInfoBase.setWorkType(workType);
			}
			if(!cmd.Field("PLAN_NO").IsNull())
			{
				planNO = cmd.Field("PLAN_NO").AsString();
				carPlanBandInfoBase.setPlanNO(planNO);
			}
			if(!cmd.Field("PLAN_SRC").IsNull())
			{
				planSrc = cmd.Field("PLAN_SRC").AsString();
				carPlanBandInfoBase.setPlanSrc(planSrc);
			}
			if(!cmd.Field("PLAN_DETAIL_ID").IsNull())
			{
				planDetailID = cmd.Field("PLAN_DETAIL_ID").AsLong();
				carPlanBandInfoBase.setPlanDetailID(planDetailID);
			}
			if(!cmd.Field("GATE_NO").IsNull())
			{
				gateNO = cmd.Field("GATE_NO").AsString();
				carPlanBandInfoBase.setGateNO(gateNO);
			}
			if(!cmd.Field("TARGET_GRID_NO").IsNull())
			{
				targetGridNO = cmd.Field("TARGET_GRID_NO").AsString();
				carPlanBandInfoBase.setTargetGridNO(targetGridNO);
			}
			if(!cmd.Field("TARGET_PARKING_NO").IsNull())
			{
				recomParkingNO = cmd.Field("TARGET_PARKING_NO").AsString();
				carPlanBandInfoBase.setTargetParkingNO(recomParkingNO);
			}
			if(!cmd.Field("ENTER_FLAG").IsNull())
			{
				enterFlag = cmd.Field("ENTER_FLAG").AsString();
				carPlanBandInfoBase.setEnterFlag(enterFlag);
			}
			if(!cmd.Field("ORDER_FLAG").IsNull())
			{
				orderFlag = cmd.Field("ORDER_FLAG").AsString();
				carPlanBandInfoBase.setOrderFlag(orderFlag);
			}
			if(!cmd.Field("BAND_TIME").IsNull())
			{
				bandTime = cmd.Field("BAND_TIME").AsDateTime();
				carPlanBandInfoBase.setBandTime(bandTime);
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


bool SQL4Parking:: CarEnterYardExist(string carNO)
{
	bool ret=false;
	string functionName="SQL4Parking :: CarEnterYardExist()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string enterFlag = CarPlanBandInfo::ENTER_YARD_2_YES;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE ";
		strSql += " CAR_NO =:p_CAR_NO AND ";
		strSql += " ENTER_FLAG = :p_ENTER_FLAG ";
		strSql += " ORDER BY  BAND_TIME  ASC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_ENTER_FLAG") = enterFlag;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
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


bool SQL4Parking:: SelScrapCodeReqWgtFormL3(string planNO, 
																					  string workType, //L3是卸料XL还是装车ZC
																					  string& locCode, 
																					  string& scrapCode,
																					  string& compCode, 
																					  long& reqWgt)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelScrapCodeReqWgtFormL3()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string srcLocCode = "";
		string srcMatCode = "";
		string srcCompCode = "";

		string dstLocCode = "";
		string dstMatCode = "";
		string dstCompCode = "";

		long estimateWgt = DF_INT_NULL;

		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_L3_MAT_IN_OUT_INFO WHERE WORK_SEQ_NO =:p_PLAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_NO") = planNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SRC_LOC_CODE").IsNull())
			{
				srcLocCode = cmd.Field("SRC_LOC_CODE").AsString();
			}

			if(!cmd.Field("SRC_MAT_CODE").IsNull())
			{
				srcMatCode = cmd.Field("SRC_MAT_CODE").AsString();
			}

			if(!cmd.Field("SRC_COMP_CODE").IsNull())
			{
				srcCompCode = cmd.Field("SRC_COMP_CODE").AsString();
			}

			if(!cmd.Field("DST_LOC_CODE").IsNull())
			{
				dstLocCode = cmd.Field("DST_LOC_CODE").AsString();
			}

			if(!cmd.Field("DST_MAT_CODE").IsNull())
			{
				dstMatCode = cmd.Field("DST_MAT_CODE").AsString();
			}

			if(!cmd.Field("DST_COMP_CODE").IsNull())
			{
				dstCompCode = cmd.Field("DST_COMP_CODE").AsString();
			}

			if(!cmd.Field("ESTIMATE_WGT").IsNull())
			{
				estimateWgt = cmd.Field("ESTIMATE_WGT").AsLong();
			}
			break;
		}

		//如果是卸料XL 无需求重量
		if (workType == CarPlanBandInfo::WORK_TYPE_XL)
		{
			locCode = dstLocCode;
			scrapCode = dstMatCode;
			compCode = dstCompCode;
			reqWgt = DF_INT_NULL;
		}
		//如果是装车ZC 需求重量是estimateWgt
		if (workType == CarPlanBandInfo::WORK_TYPE_ZC)
		{
			locCode = srcLocCode;
			scrapCode = srcMatCode;
			compCode = srcCompCode;
			reqWgt = estimateWgt;
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


bool SQL4Parking:: SelScrapCodeReqWgtFromEAF(string planNO, 
																						   long planDetailID, 
																						   string& scrapCode, 
																						   long& reqWgt)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelScrapCodeReqWgtFromEAF()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_EAF_L2_PLAN_DETAIL  WHERE PONO =:p_PLAN_NO  AND   ID = :p_PLAN_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_PLAN_DETAIL_ID") = planDetailID;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SCR_ID").IsNull())
			{
				scrapCode = cmd.Field("SCR_ID").AsString();
			}
			if(!cmd.Field("SCR_WEIGHT").IsNull())
			{
				reqWgt = cmd.Field("SCR_WEIGHT").AsLong();
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


bool SQL4Parking:: SelScrapCodeReqWgtFromBOF(string planNO, 
																						   long planDetailID, 
																						   string& scrapCode, 
																						   long& reqWgt)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelScrapCodeReqWgtFromBOF()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_BOF_L2_PLAN_DETAIL  WHERE PONO =:p_PLAN_NO  AND   ID = :p_PLAN_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_PLAN_DETAIL_ID") = planDetailID;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SCRAP_CODE").IsNull())
			{
				scrapCode = cmd.Field("SCRAP_CODE").AsString();
			}
			if(!cmd.Field("REQ_WEIGHT").IsNull())
			{
				reqWgt = cmd.Field("REQ_WEIGHT").AsLong();
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



bool SQL4Parking:: SelBayNOGateNOByGridNO(string gridNO, string& bayNO, string& gateNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelBayNOGateNOByGridNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT A.BAY_NO, B.GATE_NO  FROM UACS_YARDMAP_GRID_DEFINE A,   UACS_PARKING_GATE_INFO B  ";
		strSql +="	WHERE A.GRID_NO =:p_GRID_NO AND B.BAY_NO = A.BAY_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GRID_NO") = gridNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("BAY_NO").IsNull())
			{
				bayNO = cmd.Field("BAY_NO").AsString();
			}
			if(!cmd.Field("GATE_NO").IsNull())
			{
				gateNO = cmd.Field("GATE_NO").AsString();
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


bool SQL4Parking:: InitGateGridParking(string carNO, string planNO )
{

	bool ret=false;
	string functionName="SQL4Parking :: InitGateGridParking()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "UPDATE UACS_PARKING_CAR_PLAN_INFO SET ";
		strSql += " GATE_NO = NULL, ";
		strSql += " TARGET_GRID_NO = NULL,  ";
		strSql += " TARGET_PARKING_NO = NULL  ";
		strSql +="	WHERE CAR_NO =:p_CAR_NO  AND ";
		strSql += " PLAN_NO = :p_PLAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = planNO;

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


bool SQL4Parking:: UpdGridGateByCarNOPlanNOPlanDetailID(string carNO, 
																												string planNO, 
																												long planDetailID, 
																												string targetGridNO, 
																												string gateNO, 
																												string targetParkingNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: UpdGridGateByCarNOPlanNOPlanDetailID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "UPDATE UACS_PARKING_CAR_PLAN_INFO SET ";
		strSql += " GATE_NO = :p_GATE_NO , ";
		strSql += " TARGET_GRID_NO = :p_TARGET_GRID_NO, ";
		strSql += " TARGET_PARKING_NO = :p_TARGET_PARKING_NO ";
		strSql +="	WHERE CAR_NO =:p_CAR_NO  AND ";
		strSql += " PLAN_NO = :p_PLAN_NO AND ";
		strSql += " PLAN_DETAIL_ID = :p_PLAN_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GATE_NO") = gateNO;
		cmd.Param("p_TARGET_GRID_NO") = targetGridNO;
		cmd.Param("p_TARGET_PARKING_NO") = targetParkingNO;
		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_PLAN_DETAIL_ID") = planDetailID;		

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





bool SQL4Parking:: SelGridNOMatchScrapCode(string bayNO, string scrapCode, long reqWgt, string scrapType, string& maxStockGridNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelGridNOMatchScrapCode()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		bool wgtEnough = false;

		string gridNO = "";
		string matCode = "";
		long calWgt = 0;

		long stockWgt = 0;//每个料格内的库存量
		long allWgt = 0;//所有料格库存量和

		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_YARDMAP_GRID_DEFINE  WHERE MAT_CODE  IN  ";
		strSql += " ( ";
		strSql += " SELECT MAT_CODE FROM UACS_L3_MAT_RELATION_INFO WHERE EXTER_SYSTEM = :p_EXTER_SYSTEM AND MAT_CODE_RELATE = :p_MAT_CODE_RELATE ";
		strSql += " ) ";
		strSql += " AND BAY_NO = :p_BAY_NO ";
		strSql += " ORDER BY MAT_WGT  DESC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_EXTER_SYSTEM") = scrapType;
		cmd.Param("p_MAT_CODE_RELATE") = scrapCode;
		cmd.Param("p_BAY_NO") = bayNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{			
			if(!cmd.Field("GRID_NO").IsNull())
			{
				gridNO = cmd.Field("GRID_NO").AsString();
			}
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				matCode = cmd.Field("MAT_CODE").AsString();
			}
			if(!cmd.Field("MAT_WGT").IsNull())
			{
				stockWgt = cmd.Field("MAT_WGT").AsLong();
			}
			nCount ++;
			if (nCount == 1)
			{
				maxStockGridNO = gridNO;//记录最大库存量的料格号
			}
			allWgt = allWgt + stockWgt;


			//量还不够===============================================
			if ( allWgt < reqWgt )
			{
				//误差值 > MPE_WGT（常量100kg）  不够
				if (abs(allWgt - reqWgt) > EventGateHandler::MPE_WGT)
				{
				}
				//误差值 < MPE_WGT（常量100kg）  够了
				else
				{
					wgtEnough = true;
					break;
				}
			}

			//量够了================================================
			if ( allWgt >= reqWgt )
			{
				long needWgt = reqWgt - (allWgt - stockWgt);//本次实际需要量
				if (abs(needWgt) > EventGateHandler::MPE_WGT)//误差值 > MPE_WGT（常量100kg） 需要增加
				{
				}
				else
				{					
				}
				wgtEnough = true;
				break;
			}

		}
		if (nCount > 0 && wgtEnough == true)
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


bool SQL4Parking:: SelGridNOMatchScrapCode2(string bayNO, 
																						string scrapCode, 
																						long reqWgt,
																						string scrapType,
																						string& targetGridNO, 
																						string& parkingNO, 
																						long& falseReason)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelGridNOMatchScrapCode2()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		bool wgtEnough = false;

		string gridNO = "";
		string matCode = "";
		string compCode = "";
		long matWgt = 0;//每个料格内的库存量

		string workStatus = "100";//停车位空闲状态：100

		long nCount = 0;
		string strSql="";
		strSql = " SELECT A.GRID_NO, A.MAT_CODE, A.COMP_CODE,  A.MAT_WGT, A.PARKING_NO  FROM ";
		strSql += " UACS_YARDMAP_GRID_DEFINE A, ";
		strSql += " UACS_L3_MAT_RELATION_INFO B, ";
		strSql += " UACS_PARKING_WORK_STATUS C  ";
		strSql += " WHERE  ";
		strSql += " A.BAY_NO = :p_BAY_NO AND ";
		strSql += " A.MAT_CODE = B.MAT_CODE AND ";
		strSql += " A.COMP_CODE = B.COMP_CODE AND  ";
		strSql += " B.MAT_CODE_RELATE = :p_MAT_CODE_RELATE AND ";
		strSql += " B.EXTER_SYSTEM = :p_EXTER_SYSTEM AND ";
		strSql += " A.PARKING_NO = C.PARKING_NO AND ";
		strSql += " C.WORK_STATUS = :p_WORK_STATUS ";
		strSql += " ORDER BY A.MAT_WGT  DESC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_EXTER_SYSTEM") = scrapType;
		cmd.Param("p_MAT_CODE_RELATE") = scrapCode;
		cmd.Param("p_BAY_NO") = bayNO;
		cmd.Param("p_WORK_STATUS") = workStatus;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
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
			if(!cmd.Field("MAT_WGT").IsNull())
			{
				matWgt = cmd.Field("MAT_WGT").AsLong();
			}
			if(!cmd.Field("PARKING_NO").IsNull())
			{
				parkingNO = cmd.Field("PARKING_NO").AsString();
			}
			//存量>需求量,满足条件
			if (matWgt > reqWgt)
			{
				wgtEnough = true;
				break;
			}
			//存量<需求量，但是误差<100kg，满足条件
			if (matWgt < reqWgt && abs(matWgt - reqWgt) < EventGateHandler::MPE_WGT)
			{
				wgtEnough = true;
				break;
			}
			//按照存量大到小排，第一个不满足条件，后续一定都不满足
			if (nCount == 1)
			{
				break;
			}
		}
		if (nCount == 0)
		{
			//无空闲停车位
			falseReason = 1;
		}
		else if (nCount == 1 && wgtEnough == false)
		{
			//库存量不满足需求
			falseReason = 2;
		}
		
		if (wgtEnough == true)
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




bool SQL4Parking:: SelBayNOByGateNO(string gateNO, string& bayNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelBayNOByGateNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_GATE_INFO  WHERE GATE_NO  = :p_GATE_NO ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GATE_NO") = gateNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("BAY_NO").IsNull())
			{
				bayNO = cmd.Field("BAY_NO").AsString();
			}
			if (nCount > 0)
			{
				break;
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


bool SQL4Parking:: SelTargetGridNO(string carNO, 
																   string gateNO, 
																   string& carType, 
																   string& targetGridNO, 
																   string& targetParkingNO, 
																   string& workType,
																   string& planNO, 
																   string& planSrc, 
																   long& planDetailID)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelTargetGridNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string enterFlag = CarPlanBandInfo::ENTER_YARD_1_NO;

		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO  WHERE ";
		strSql += " CAR_NO  = :p_CAR_NO  AND ";
		strSql += " GATE_NO = :p_GATE_NO AND ";
		strSql += " ENTER_FLAG = :p_ENTER_FLAG ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_GATE_NO") = gateNO;
		cmd.Param("p_ENTER_FLAG") = enterFlag;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("CAR_TYPE").IsNull())
			{
				carType = cmd.Field("CAR_TYPE").AsString();
			}
			if(!cmd.Field("TARGET_GRID_NO").IsNull())
			{
				targetGridNO = cmd.Field("TARGET_GRID_NO").AsString();
			}
			if(!cmd.Field("TARGET_PARKING_NO").IsNull())
			{
				targetParkingNO = cmd.Field("TARGET_PARKING_NO").AsString();
			}
			if(!cmd.Field("WORK_TYPE").IsNull())
			{
				workType = cmd.Field("WORK_TYPE").AsString();
			}
			if(!cmd.Field("PLAN_NO").IsNull())
			{
				planNO = cmd.Field("PLAN_NO").AsString();
			}
			if(!cmd.Field("PLAN_SRC").IsNull())
			{
				planSrc = cmd.Field("PLAN_SRC").AsString();
			}
			if(!cmd.Field("PLAN_DETAIL_ID").IsNull())
			{
				planDetailID = cmd.Field("PLAN_DETAIL_ID").AsLong();
			}
			if (nCount > 0)
			{
				break;
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


bool SQL4Parking:: UpdEnterFlag2Enter(string carNO, string gateNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: UpdEnterFlag2Enter()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "UPDATE UACS_PARKING_CAR_PLAN_INFO ";
		strSql += " SET ENTER_FLAG = :p_ENTER_FLAG  ";
		strSql +="	WHERE CAR_NO =:p_CAR_NO  ";
		strSql += " AND GATE_NO = :p_GATE_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		string enterFlag = CarPlanBandInfo::ENTER_YARD_2_YES;

		cmd.Param("p_ENTER_FLAG") = enterFlag;
		cmd.Param("p_GATE_NO") = gateNO;
		cmd.Param("p_CAR_NO") = carNO;

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


bool SQL4Parking:: SelParkingNOByCarNOFlag(string carNO, 
																					string enterFlag, 
																					string& parkingNO, 
																					string& workType, 
																					string& carType,
																					string& planSrc, 
																					string& planNO, 
																					long& planDetailID)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelParkingNOByCarNOFlag()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO  WHERE ";
		strSql += " CAR_NO  = :p_CAR_NO  AND  ";
		strSql += " ENTER_FLAG = :p_ENTER_FLAG ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_ENTER_FLAG") = enterFlag;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("TARGET_PARKING_NO").IsNull())
			{
				parkingNO = cmd.Field("TARGET_PARKING_NO").AsString();
			}
			if(!cmd.Field("WORK_TYPE").IsNull())
			{
				workType = cmd.Field("WORK_TYPE").AsString();
			}
			if(!cmd.Field("CAR_TYPE").IsNull())
			{
				carType = cmd.Field("CAR_TYPE").AsString();
			}
			if(!cmd.Field("PLAN_SRC").IsNull())
			{
				planSrc = cmd.Field("PLAN_SRC").AsString();
			}
			if(!cmd.Field("PLAN_NO").IsNull())
			{
				planNO = cmd.Field("PLAN_NO").AsString();
			}
			if(!cmd.Field("PLAN_DETAIL_ID").IsNull())
			{
				planDetailID = cmd.Field("PLAN_DETAIL_ID").AsLong();
			}
			if (nCount > 0)
			{
				break;
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


bool SQL4Parking:: SelStatusByParkingNO(string parkingNO, string& workStatus, string& workType, string& carNO)
{
	bool ret=false;
	string functionName="SQL4Parking :: SelStatusByParkingNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_WORK_STATUS  WHERE PARKING_NO  = :p_PARKING_NO ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PARKING_NO") = parkingNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("WORK_STATUS").IsNull())
			{
				workStatus = cmd.Field("WORK_STATUS").AsString();
			}
			if(!cmd.Field("WORK_TYPE").IsNull())
			{
				workType = cmd.Field("WORK_TYPE").AsString();
			}
			if(!cmd.Field("CAR_NO").IsNull())
			{
				carNO = cmd.Field("CAR_NO").AsString();
			}
			if (nCount > 0)
			{
				break;
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

bool SQL4Parking:: SelCarNOByParkingNO(string parkingNO, string& carNO)
{
	bool ret=false;
	string functionName="SQL4Parking :: SelCarNOByParkingNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_WORK_STATUS  WHERE PARKING_NO  = :p_PARKING_NO ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PARKING_NO") = parkingNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("CAR_NO").IsNull())
			{
				carNO = cmd.Field("CAR_NO").AsString();
			}
			if (nCount > 0)
			{
				break;
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


bool SQL4Parking:: UpdParkingStatus(string parkingNO, string workStatus)
{

	bool ret=false;
	string functionName="SQL4Parking :: UpdParkingStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "UPDATE UACS_PARKING_WORK_STATUS SET WORK_STATUS = :p_WORK_STATUS  ";
		strSql +="	WHERE PARKING_NO =:p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_STATUS") = workStatus;
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

bool SQL4Parking:: SelGridInfoByGridNO(string gridNO, string& matCode, string& compCode, long& matWgt)
{
	bool ret=false;
	string functionName="SQL4Parking :: SelMatCompCodeByGridNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_YARDMAP_GRID_DEFINE  WHERE GRID_NO  = :p_GRID_NO ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GRID_NO") = gridNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				matCode = cmd.Field("MAT_CODE").AsString();
			}
			if(!cmd.Field("COMP_CODE").IsNull())
			{
				compCode = cmd.Field("COMP_CODE").AsString();
			}
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				matCode = cmd.Field("MAT_CODE").AsString();
			}
			if(!cmd.Field("MAT_WGT").IsNull())
			{
				matWgt = cmd.Field("MAT_WGT").AsLong();
			}
			if (nCount > 0)
			{
				break;
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


bool SQL4Parking:: SelPKStatusByGridNO(string gridNO, string& parkingNO, string& workStatus)
{
	bool ret=false;
	string functionName="SQL4Parking :: SelPKStatusByGridNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		long nCount = 0;
		string strSql="";
		strSql = "SELECT A.WORK_STATUS , A.PARKING_NO  FROM UACS_PARKING_WORK_STATUS A,   UACS_YARDMAP_GRID_DEFINE B  WHERE ";
		strSql += " A.PARKING_NO = B.PARKING_NO AND ";
		strSql += " B.GRID_NO  = :p_GRID_NO ";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GRID_NO") = gridNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("WORK_STATUS").IsNull())
			{
				workStatus = cmd.Field("WORK_STATUS").AsString();
			}
			if(!cmd.Field("PARKING_NO").IsNull())
			{
				parkingNO = cmd.Field("PARKING_NO").AsString();
			}
			if (nCount > 0)
			{
				break;
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


bool SQL4Parking:: UpdGateGridPKByCarPlan(string carNO, string planNO, string gateNO, string gridNO, string parkingNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: UpdGateGridPKByCarPlan()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE  UACS_PARKING_CAR_PLAN_INFO  SET ";
		strSql += " GATE_NO = :p_GATE_NO,  ";
		strSql += " TARGET_GRID_NO = :p_TARGET_GRID_NO,  ";
		strSql += " TARGET_PARKING_NO = :p_TARGET_PARKING_NO,  ";
		strSql += " REC_TIME = :p_REC_TIME  ";
		strSql +="	WHERE CAR_NO =:p_CAR_NO  AND ";
		strSql +="	PLAN_NO =:p_PLAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GATE_NO") = gateNO;
		cmd.Param("p_TARGET_GRID_NO") = gridNO;
		cmd.Param("p_TARGET_PARKING_NO") = parkingNO;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();
		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = planNO;

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


bool SQL4Parking:: SelParkingTM(long& parkingTM)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelParkingTM()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		//采用db2中的序列来记录指令组号
		//此序列从 100000  开始，建序列时注意
		strSql = " SELECT SEQ_PARKING_TREATMENT_NO.NEXTVAL AS SEQ FROM SYSIBM.SYSDUMMY1 ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SEQ").IsNull())
			{
				parkingTM = cmd.Field("SEQ").AsLong();
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


bool SQL4Parking:: UpdParkingWorkStautsInfo(string parkingNO, string treatmentNO, string workStatus, string workType, string carNO, string carType)
{
	bool ret=false;
	string functionName="SQL4Parking :: UpdParkingWorkStautsInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE  UACS_PARKING_WORK_STATUS  SET ";
		strSql += " TREATMENT_NO = :p_TREATMENT_NO,  ";
		strSql += " WORK_STATUS = :p_WORK_STATUS,  ";
		strSql += " WORK_TYPE = :p_WORK_TYPE, ";
		strSql += " CAR_NO = :p_CAR_NO,   ";
		strSql += " CAR_TYPE = :p_CAR_TYPE,   ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE PARKING_NO = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_TREATMENT_NO") = treatmentNO;
		cmd.Param("p_WORK_STATUS") = workStatus;		
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_CAR_TYPE") = carType;
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


bool SQL4Parking:: InsParkingMatInfo(string treatmentNO, 
																	 string parkingNO, 
																	 string carNO, 
																	 string planSrc, 
																	 string planNO, 
																	 long planDetailID, 
																	 string matCode, 
																	 string compCode, 
																	 string workType, 
																	 string fromPlace, 
																	 string toPlace, 
																	 string finishFlag)
{
	bool ret=false;
	string functionName="SQL4Parking :: InsParkingMatInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "INSERT INTO  UACS_PARKING_MAT_INFO( ";
		strSql += " TREATMENT_NO,  ";
		strSql += " PARKING_NO, ";
		strSql += " CAR_NO, ";
		strSql += " PLAN_SRC, ";
		strSql += " PLAN_NO, ";
		strSql += " PLAN_DETAIL_ID, ";
		strSql += " MAT_CODE, ";
		strSql += " COMP_CODE, ";
		strSql += " WORK_TYPE, ";
		strSql += " FROM_PLACE, ";
		strSql += " TO_PLACE, ";
		strSql += " FINISH_FLAG, ";
		strSql += " REC_TIME ) ";

		strSql +="	VALUES( ";
		strSql += " :p_TREATMENT_NO, ";
		strSql += " :p_PARKING_NO, ";
		strSql += " :p_CAR_NO, ";
		strSql += " :p_PLAN_SRC, ";
		strSql += " :p_PLAN_NO, ";
		strSql += " :p_PLAN_DETAIL_ID, ";
		strSql += " :p_MAT_CODE, ";
		strSql += " :p_COMP_CODE, ";
		strSql += " :p_WORK_TYPE, ";
		strSql += " :p_FROM_PLACE, ";
		strSql += " :p_TO_PLACE, ";
		strSql += " :p_FINISH_FLAG, ";
		strSql += " :p_REC_TIME ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_TREATMENT_NO") = treatmentNO;
		cmd.Param("p_PARKING_NO") = parkingNO;		
		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_SRC") = planSrc;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_PLAN_DETAIL_ID") = planDetailID;
		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Param("p_COMP_CODE") = compCode;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_FROM_PLACE") = fromPlace;
		cmd.Param("p_TO_PLACE") = toPlace;
		cmd.Param("p_FINISH_FLAG") = finishFlag;
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


bool SQL4Parking:: SelAllFromParkingWorkStatus(string parkingNO, 
																						   string& treatmentNO, 
																						   string& workStauts, 
																						   string& workType, 
																						   string& carNO, 
																						   string& carType )
{
	bool ret=false;
	string functionName="SQL4Parking :: SelAllFromParkingWorkStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_WORK_STATUS  WHERE ";
		strSql += " PARKING_NO  = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PARKING_NO") = parkingNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount ++;
			if(!cmd.Field("TREATMENT_NO").IsNull())
			{
				treatmentNO = cmd.Field("TREATMENT_NO").AsString();
			}
			if(!cmd.Field("WORK_STATUS").IsNull())
			{
				workStauts = cmd.Field("WORK_STATUS").AsString();
			}
			if(!cmd.Field("WORK_TYPE").IsNull())
			{
				workType = cmd.Field("WORK_TYPE").AsString();
			}
			if(!cmd.Field("CAR_NO").IsNull())
			{
				carNO = cmd.Field("CAR_NO").AsString();
			}
			if(!cmd.Field("CAR_TYPE").IsNull())
			{
				carType = cmd.Field("CAR_TYPE").AsString();
			}
			if (nCount > 0)
			{
				break;
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


bool SQL4Parking:: InitParkingWorkStauts(string parkingNO)
{
	bool ret=false;
	string functionName="SQL4Parking :: InitParkingWorkStauts()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string workStatus = "100";

		string strSql="";
		strSql = "UPDATE  UACS_PARKING_WORK_STATUS  SET ";
		strSql += " TREATMENT_NO = NULL,  ";
		strSql += " WORK_STATUS = :p_WORK_STATUS,  ";
		strSql += " WORK_TYPE = NULL, ";
		strSql += " CAR_NO = NULL,   ";
		strSql += " CAR_TYPE = NULL,   ";
		strSql += " REC_TIME = NULL ";
		strSql +="	WHERE PARKING_NO = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_STATUS") = workStatus;
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

bool SQL4Parking:: DelCarPlanInfoByCarNO(string carNO, string carType, string workType)
{
	bool ret=false;
	string functionName="SQL4Parking :: DelCarPlanInfoByCarNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string enterFlag = "2";

		string strSql="";
		strSql = "DELETE   FROM   UACS_PARKING_CAR_PLAN_INFO  WHERE ";
		strSql += " CAR_NO = :p_CAR_NO AND ";
		strSql += " CAR_TYPE = :p_CAR_TYPE AND  ";
		strSql += " WORK_TYPE = :p_WORK_TYPE AND ";
		strSql += " ENTER_FLAG = :p_ENTER_FLAG   ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_CAR_TYPE") = carType;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_ENTER_FLAG") = enterFlag;

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


bool SQL4Parking:: UpdParkingMatInfoFinish(string treatmentNO)
{
	bool ret=false;
	string functionName="SQL4Parking :: UpdParkingMatInfoFinish()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string finishFlag = "2";

		string strSql="";
		strSql = "UPDATE  UACS_PARKING_MAT_INFO  SET ";
		strSql += " FINISH_FLAG = :p_FINISH_FLAG,  ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE TREATMENT_NO = :p_TREATMENT_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_FINISH_FLAG") = finishFlag;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();
		cmd.Param("p_TREATMENT_NO") = treatmentNO;

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


bool SQL4Parking:: UpdParkingStatusByValue(string pakringNO, string workStatus)
{
	bool ret=false;
	string functionName="SQL4Parking :: UpdParkingStatusByValue()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE  UACS_PARKING_WORK_STATUS  SET ";
		strSql += " WORK_STATUS = :p_WORK_STATUS,  ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  PARKING_NO = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_STATUS") = workStatus;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();
		cmd.Param("p_PARKING_NO") = pakringNO;

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


bool SQL4Parking:: UpdEnterFlag2XLLeave(string carNO, 
																			   string carType, 
																			   string workType, 
																			   string lastEnterFlag, 
																			   string nowEnterFlag)
{
	bool ret=false;
	string functionName="SQL4Parking :: UpdEnterFlagByCarNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "UPDATE  UACS_PARKING_CAR_PLAN_INFO  SET ";
		strSql += " ENTER_FLAG = :p_NOW_ENTER_FLAG,  ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  CAR_NO = :p_CAR_NO AND ";
		strSql += " CAR_TYPE = :p_CAR_TYPE AND ";
		strSql += " WORK_TYPE = :p_WORK_TYPE AND ";
		strSql += " ENTER_FLAG = :p_LAST_ENTER_FLAG ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_NOW_ENTER_FLAG") = nowEnterFlag;
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now();
		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_CAR_TYPE") = carType;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_LAST_ENTER_FLAG") = lastEnterFlag;

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


bool SQL4Parking:: SelScanNO4Mat(string& scanNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelScanNO4Mat()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nOperID = 0;
		long nCount = 0;
		string strSql="";
		//采用db2中的序列来记录指令号
		strSql = " SELECT SEQ_SCAN_NO.NEXTVAL AS SEQ FROM SYSIBM.SYSDUMMY1 ";

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
		scanNO = "MAT" + StringHelper::ToString(nOperID);
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


bool SQL4Parking:: SelScanNO4Car(string& scanNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelScanNO4Car()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nOperID = 0;
		long nCount = 0;
		string strSql="";
		//采用db2中的序列来记录指令号
		strSql = " SELECT SEQ_SCAN_NO.NEXTVAL AS SEQ FROM SYSIBM.SYSDUMMY1 ";

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
		scanNO = "CAR" + StringHelper::ToString(nOperID);
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


bool SQL4Parking:: SelComLineNO(string module, int& lineNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelComLineNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " SELECT LINE_NO FROM UACS_COM_LINE_CONFIG WHERE  ";
		strSql += " MODULE  = :p_MODULE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_MODULE") = module;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("LINE_NO").IsNull())
			{
				lineNO = (int)cmd.Field("LINE_NO").AsLong();
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


bool SQL4Parking:: InsParkingSRSMatInfo(string scanNO, //扫描处理号
																			string areaType, //被扫区域类型
																			string areaNO, //被扫区域名称
																			long orderNO, //当前指令号
																			string scanMessageNO, //扫描事件号
																			string scanCraneNO, //扫描行车号
																			string scanType, //扫描类型 0-取料 1-放料
																			long startX, //扫描区域起始X
																			long endX, //扫描区域结束X
																			long startY, //扫描区域起始Y
																			long endY, //扫描区域结束Y
																			long actX, //行车当前X
																			long actY)//行车当前Y
{
	bool ret=false;
	string functionName="SQL4Parking :: InsParkingSRSMatInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "INSERT INTO  UACS_PARKING_SRS_MAT_INFO( ";
		strSql += " SCAN_NO,  ";
		strSql += " AREA_TYPE, ";
		strSql += " AREA_NO, ";
		strSql += " ORDER_NO, ";
		strSql += " SCAN_MESSAGE_NO, ";
		strSql += " SCAN_CRANE_NO, ";
		strSql += " SCAN_TYPE, ";
		strSql += " START_X, ";
		strSql += " END_X, ";
		strSql += " START_Y, ";
		strSql += " END_Y, ";
		strSql += " ACT_X, ";
		strSql += " ACT_Y, ";
		strSql += " REC_TIME ) ";

		strSql +="	VALUES( ";
		strSql += " :p_SCAN_NO, ";
		strSql += " :p_AREA_TYPE, ";
		strSql += " :p_AREA_NO, ";
		strSql += " :p_ORDER_NO, ";
		strSql += " :p_SCAN_MESSAGE_NO, ";
		strSql += " :p_SCAN_CRANE_NO, ";
		strSql += " :p_SCAN_TYPE, ";
		strSql += " :p_START_X, ";
		strSql += " :p_END_X, ";
		strSql += " :p_START_Y, ";
		strSql += " :p_END_Y, ";
		strSql += " :p_ACT_X, ";
		strSql += " :p_ACT_Y, ";
		strSql += " :p_REC_TIMIE ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SCAN_NO") = scanNO;
		cmd.Param("p_AREA_TYPE") = areaType;		
		cmd.Param("p_AREA_NO") = areaNO;
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Param("p_SCAN_MESSAGE_NO") = scanMessageNO;
		cmd.Param("p_SCAN_CRANE_NO") = scanCraneNO;
		cmd.Param("p_SCAN_TYPE") = scanType;
		cmd.Param("p_START_X") = startX;
		cmd.Param("p_END_X") = endX;
		cmd.Param("p_START_Y") = startY;
		cmd.Param("p_END_Y") = endY;
		cmd.Param("p_ACT_X") = actX;
		cmd.Param("p_ACT_Y") = actY;
		cmd.Param("p_REC_TIMIE") = iDA::DateTime::Now();

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

bool SQL4Parking:: InsParkingSRSMatInfo2(string scanNO, //扫描处理号
																				 string areaType, //被扫区域类型
																				 string areaNO, //被扫区域名称
																				 long orderNO, //当前指令号
																				 string scanMessageNO, //扫描事件号
																				 string scanCraneNO, //扫描行车号
																				 string scanType, //扫描类型 0-取料 1-放料
																				 long carPointX1, //车辆框架X1
																				 long carPointY1, //车辆框架X1
																				 long carPointZ1, //车辆框架X1
																				 long carPointX2, //车辆框架X1
																				 long carPointY2, //车辆框架X1
																				 long carPointZ2, //车辆框架X1
																				 long carPointX3, //车辆框架X1
																				 long carPointY3, //车辆框架X1
																				 long carPointZ3, //车辆框架X1
																				 long carPointX4, //车辆框架X1
																				 long carPointY4, //车辆框架X1
																				 long carPointZ4, //车辆框架X1	
																				 long actX, //行车当前X
																				 long actY)//行车当前Y
{
	bool ret=false;
	string functionName="SQL4Parking :: InsParkingSRSMatInfo2()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "INSERT INTO  UACS_PARKING_SRS_MAT_INFO( ";
		strSql += " SCAN_NO,  ";
		strSql += " AREA_TYPE, ";
		strSql += " AREA_NO, ";
		strSql += " ORDER_NO, ";
		strSql += " SCAN_MESSAGE_NO, ";
		strSql += " SCAN_CRANE_NO, ";
		strSql += " SCAN_TYPE, ";
		strSql += " CAR_POINT_X1, ";
		strSql += " CAR_POINT_Y1, ";
		strSql += " CAR_POINT_Z1, ";
		strSql += " CAR_POINT_X2, ";
		strSql += " CAR_POINT_Y2, ";
		strSql += " CAR_POINT_Z2, ";
		strSql += " CAR_POINT_X3, ";
		strSql += " CAR_POINT_Y3, ";
		strSql += " CAR_POINT_Z3, ";
		strSql += " CAR_POINT_X4, ";
		strSql += " CAR_POINT_Y4, ";
		strSql += " CAR_POINT_Z4, ";
		strSql += " ACT_X, ";
		strSql += " ACT_Y, ";
		strSql += " REC_TIME ) ";

		strSql +="	VALUES( ";
		strSql += " :p_SCAN_NO, ";
		strSql += " :p_AREA_TYPE, ";
		strSql += " :p_AREA_NO, ";
		strSql += " :p_ORDER_NO, ";
		strSql += " :p_SCAN_MESSAGE_NO, ";
		strSql += " :p_SCAN_CRANE_NO, ";
		strSql += " :p_SCAN_TYPE, ";
		strSql += " :p_CAR_POINT_X1, ";
		strSql += " :p_CAR_POINT_Y1, ";
		strSql += " :p_CAR_POINT_Z1, ";
		strSql += " :p_CAR_POINT_X2, ";
		strSql += " :p_CAR_POINT_Y2, ";
		strSql += " :p_CAR_POINT_Z2, ";
		strSql += " :p_CAR_POINT_X3, ";
		strSql += " :p_CAR_POINT_Y3, ";
		strSql += " :p_CAR_POINT_Z3, ";
		strSql += " :p_CAR_POINT_X4, ";
		strSql += " :p_CAR_POINT_Y4, ";
		strSql += " :p_CAR_POINT_Z4, ";
		strSql += " :p_ACT_X, ";
		strSql += " :p_ACT_Y, ";
		strSql += " :p_REC_TIMIE ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SCAN_NO") = scanNO;
		cmd.Param("p_AREA_TYPE") = areaType;		
		cmd.Param("p_AREA_NO") = areaNO;
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Param("p_SCAN_MESSAGE_NO") = scanMessageNO;
		cmd.Param("p_SCAN_CRANE_NO") = scanCraneNO;
		cmd.Param("p_SCAN_TYPE") = scanType;
		cmd.Param("p_CAR_POINT_X1") = carPointX1;
		cmd.Param("p_CAR_POINT_Y1") = carPointY1;
		cmd.Param("p_CAR_POINT_Z1") = carPointZ1;
		cmd.Param("p_CAR_POINT_X2") = carPointX2;
		cmd.Param("p_CAR_POINT_Y2") = carPointY2;
		cmd.Param("p_CAR_POINT_Z2") = carPointZ2;
		cmd.Param("p_CAR_POINT_X3") = carPointX3;
		cmd.Param("p_CAR_POINT_Y3") = carPointY3;
		cmd.Param("p_CAR_POINT_Z3") = carPointZ3;
		cmd.Param("p_CAR_POINT_X4") = carPointX4;
		cmd.Param("p_CAR_POINT_Y4") = carPointY4;
		cmd.Param("p_CAR_POINT_Z4") = carPointZ4;
		cmd.Param("p_ACT_X") = actX;
		cmd.Param("p_ACT_Y") = actY;
		cmd.Param("p_REC_TIMIE") = iDA::DateTime::Now();

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


bool SQL4Parking:: UpdParkingSRSMatInfo(string scanNO, 
																				string scanResult, 
																				long pointX, 
																				long pointY, 
																				long pointZ, 
																				long& orderNO)
{
	bool ret=false;
	string functionName="SQL4Parking :: UpdParkingSRSMatInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//获取指令号
		string strSql = "";
		strSql = " SELECT ORDER_NO  FROM UACS_PARKING_SRS_MAT_INFO WHERE  ";
		strSql += " SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_NO") = scanNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("ORDER_NO").IsNull())
			{
				orderNO = cmd.Field("ORDER_NO").AsLong();
			}
		}

		//更新激光扫描结果
		strSql = "";
		strSql = "UPDATE  UACS_PARKING_SRS_MAT_INFO  SET ";
		strSql += " SCAN_RESULT = :p_SCAN_RESULT,  ";
		strSql += " POINT_X = :p_POINT_X, ";
		strSql += " POINT_Y = :p_POINT_Y, ";
		strSql += " POINT_Z = :p_POINT_Z, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd2(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd2.Param("p_SCAN_RESULT") = scanResult;
		cmd2.Param("p_POINT_X") = pointX;
		cmd2.Param("p_POINT_Y") = pointY;
		cmd2.Param("p_POINT_Z") = pointZ;
		cmd2.Param("p_SCAN_NO") = scanNO;
		cmd2.Param("p_REC_TIME") = iDA::DateTime::Now();

		cmd2.Execute();
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

bool SQL4Parking:: InsParkingSRSCarInfo(string scanNO, 
																			string treatmentNO, 
																			string parkingNO, 
																			string carNO, 
																			string carType, 
																			string matType, 
																			string loadFlag, 
																			string scanMode, 
																			long orderNO, 
																			string scanMessageNO, 
																			string scanCraneNO, 
																			long startPoint, 
																			long endPoint, 
																			long scanCount, 
																			string scanIP, 
																			string scanRGVFlag)
{
	bool ret=false;
	string functionName="SQL4Parking :: InsParkingSRSCarInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "INSERT INTO  UACS_PARKING_SRS_CAR_INFO( ";
		strSql += " SCAN_NO,  ";
		strSql += " TREATMENT_NO, ";
		strSql += " PARKING_NO, ";
		strSql += " CAR_NO, ";
		strSql += " CAR_TYPE, ";
		strSql += " MAT_TYPE, ";
		strSql += " LOAD_FLAG, ";
		strSql += " SCAN_MODE, ";
		strSql += " ORDER_NO, ";
		strSql += " SCAN_MESSAGE_NO, ";
		strSql += " SCAN_CRANE_NO, ";
		strSql += " START_POINT, ";
		strSql += " END_POINT, ";
		strSql += " SCAN_COUNT, ";
		strSql += " SCAN_IP, ";
		strSql += " SCAN_RGV_FLAG, ";
		strSql += " REC_TIME ) ";

		strSql +="	VALUES( ";
		strSql += " :p_SCAN_NO, ";
		strSql += " :p_TREATMENT_NO, ";
		strSql += " :p_PARKING_NO, ";
		strSql += " :p_CAR_NO, ";
		strSql += " :p_CAR_TYPE, ";
		strSql += " :p_MAT_TYPE, ";
		strSql += " :p_LOAD_FLAG, ";
		strSql += " :p_SCAN_MODE, ";
		strSql += " :p_ORDER_NO, ";
		strSql += " :p_SCAN_MESSAGE_NO, ";
		strSql += " :p_SCAN_CRANE_NO, ";
		strSql += " :p_START_POINT, ";
		strSql += " :p_END_POINT, ";
		strSql += " :p_SCAN_COUNT, ";
		strSql += " :p_SCAN_IP, ";
		strSql += " :p_SCAN_RGV_FLAG, ";
		strSql += " :p_REC_TIMIE ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SCAN_NO") = scanNO;
		cmd.Param("p_TREATMENT_NO") = treatmentNO;		
		cmd.Param("p_PARKING_NO") = parkingNO;
		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_CAR_TYPE") = carType;
		cmd.Param("p_MAT_TYPE") = matType;
		cmd.Param("p_LOAD_FLAG") = loadFlag;
		cmd.Param("p_SCAN_MODE") = scanMode;
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Param("p_SCAN_MESSAGE_NO") = scanMessageNO;
		cmd.Param("p_SCAN_CRANE_NO") = scanCraneNO;
		cmd.Param("p_START_POINT") = startPoint;
		cmd.Param("p_END_POINT") = endPoint;
		cmd.Param("p_SCAN_COUNT") = scanCount;
		cmd.Param("p_SCAN_IP") = scanIP;
		cmd.Param("p_SCAN_RGV_FLAG") = scanRGVFlag;
		cmd.Param("p_REC_TIMIE") = iDA::DateTime::Now();

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

bool SQL4Parking:: SelParkingTreatmentNOCarNO(string parkingNO, string& parkingTreatmentNO, string& carNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelParkingTreatmentNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " SELECT  TREATMENT_NO, CAR_NO  FROM UACS_PARKING_WORK_STATUS  WHERE  ";
		strSql += " PARKING_NO  = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_PARKING_NO") = parkingNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("TREATMENT_NO").IsNull())
			{
				parkingTreatmentNO = cmd.Field("TREATMENT_NO").AsString();
			}
			if(!cmd.Field("CAR_NO").IsNull())
			{
				carNO = cmd.Field("CAR_NO").AsString();
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


bool SQL4Parking:: SelRGVNO(string parkingNO, string& rgvNO)
{

	bool ret=false;
	string functionName="SQL4Parking :: SelRGVCarNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " SELECT  RGV_NO  FROM UACS_PARKING_RGV_STATUS  WHERE  ";
		strSql += " PARKING_NO  = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_PARKING_NO") = parkingNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("RGV_NO").IsNull())
			{
				rgvNO = cmd.Field("RGV_NO").AsString();
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


bool SQL4Parking:: UpdParkingSRSCarInfo(string scanNO, 
																				string scanResult, 
																				long pointX1, 
																				long pointY1, 
																				long pointZ1, 
																				long pointX2, 
																				long pointY2, 
																				long pointZ2, 
																				long pointX3, 
																				long pointY3, 
																				long pointZ3, 
																				long pointX4, 
																				long pointY4, 
																				long pointZ4, 
																				long pointX, 
																				long pointY, 
																				long pointZ, 
																				long& orderNO,
																				string& scanRGVFlag,
																				string& parkingNO)
{
	bool ret=false;
	string functionName="SQL4Parking :: UpdParkingSRSCarInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//获取指令号
		string strSql = "";
		strSql = " SELECT ORDER_NO, SCAN_RGV_FLAG, PARKING_NO  FROM UACS_PARKING_SRS_CAR_INFO WHERE  ";
		strSql += " SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_NO") = scanNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("ORDER_NO").IsNull())
			{
				orderNO = cmd.Field("ORDER_NO").AsLong();
			}
			if(!cmd.Field("SCAN_RGV_FLAG").IsNull())
			{
				scanRGVFlag = cmd.Field("SCAN_RGV_FLAG").AsString();
			}
			if(!cmd.Field("PARKING_NO").IsNull())
			{
				parkingNO = cmd.Field("PARKING_NO").AsString();
			}
		}

		//更新激光扫描结果
		strSql = "";
		strSql = "UPDATE  UACS_PARKING_SRS_CAR_INFO  SET ";
		strSql += " SCAN_RESULT = :p_SCAN_RESULT,  ";
		strSql += " POINT_X_1 = :p_POINT_X_1, ";
		strSql += " POINT_Y_1 = :p_POINT_Y_1, ";
		strSql += " POINT_Z_1 = :p_POINT_Z_1, ";
		strSql += " POINT_X_2 = :p_POINT_X_2, ";
		strSql += " POINT_Y_2 = :p_POINT_Y_2, ";
		strSql += " POINT_Z_2 = :p_POINT_Z_2, ";
		strSql += " POINT_X_3 = :p_POINT_X_3, ";
		strSql += " POINT_Y_3 = :p_POINT_Y_3, ";
		strSql += " POINT_Z_3 = :p_POINT_Z_3, ";
		strSql += " POINT_X_4 = :p_POINT_X_4, ";
		strSql += " POINT_Y_4 = :p_POINT_Y_4, ";
		strSql += " POINT_Z_4 = :p_POINT_Z_4, ";
		strSql += " POINT_X = :p_POINT_X, ";
		strSql += " POINT_Y = :p_POINT_Y, ";
		strSql += " POINT_Z = :p_POINT_Z, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd2(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd2.Param("p_SCAN_RESULT") = scanResult;
		cmd2.Param("p_POINT_X_1") = pointX1;
		cmd2.Param("p_POINT_Y_1") = pointY1;
		cmd2.Param("p_POINT_Z_1") = pointZ1;
		cmd2.Param("p_POINT_X_2") = pointX2;
		cmd2.Param("p_POINT_Y_2") = pointY2;
		cmd2.Param("p_POINT_Z_2") = pointZ2;
		cmd2.Param("p_POINT_X_3") = pointX3;
		cmd2.Param("p_POINT_Y_3") = pointY3;
		cmd2.Param("p_POINT_Z_3") = pointZ3;
		cmd2.Param("p_POINT_X_4") = pointX4;
		cmd2.Param("p_POINT_Y_4") = pointY4;
		cmd2.Param("p_POINT_Z_4") = pointZ4;		
		cmd2.Param("p_POINT_X") = pointX;
		cmd2.Param("p_POINT_Y") = pointY;
		cmd2.Param("p_POINT_Z") = pointZ;
		cmd2.Param("p_SCAN_NO") = scanNO;
		cmd2.Param("p_REC_TIME") = iDA::DateTime::Now();

		cmd2.Execute();
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


bool SQL4Parking:: UpdParkingRGVStatusSRS(string parkingNO, 
																					  long pointXMin, 
																					  long pointXMax, 
																					  long pointYMin, 
																					  long pointYMax)
{
	bool ret=false;
	string functionName="SQL4Parking :: UpdParkingRGVStatusSRS()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//获取指令号
		string strSql = "";		
		strSql = "UPDATE  UACS_PARKING_RGV_STATUS  SET ";
		strSql += " POINT_X_MIN = :p_POINT_X_MIN,  ";
		strSql += " POINT_X_MAX = :p_POINT_X_MAX, ";
		strSql += " POINT_Y_MIN = :p_POINT_Y_MIN, ";
		strSql += " POINT_Y_MAX = :p_POINT_Y_MAX, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  PARKING_NO  = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_POINT_X_MIN") = pointXMin;
		cmd.Param("p_POINT_X_MAX") = pointXMax;
		cmd.Param("p_POINT_Y_MIN") = pointYMin;
		cmd.Param("p_POINT_Y_MAX") = pointYMax;
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