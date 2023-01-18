#include <climits>
#include "SQL4Order.h"

using namespace Monitor;



SQL4Order::SQL4Order(void)
{
}



SQL4Order::~SQL4Order(void)
{
}


bool SQL4Order:: SelOrderGroupNO(long& orderGroupNO)
{

	bool ret=false;
	string functionName="SQL4Order :: SelectOrderGroupNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		//采用db2中的序列来记录指令组号
		strSql = " SELECT SEQ_ORDER_GROUP_NO.NEXTVAL AS SEQ FROM SYSIBM.SYSDUMMY1 ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SEQ").IsNull())
			{
				orderGroupNO = cmd.Field("SEQ").AsLong();
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


bool SQL4Order:: SelOrderNO(long& orderNO)
{

	bool ret=false;
	string functionName="SQL4Order :: SelOrderNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		//采用db2中的序列来记录指令号
		strSql = " SELECT SEQ_ORDER_NO.NEXTVAL AS SEQ FROM SYSIBM.SYSDUMMY1 ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SEQ").IsNull())
			{
				orderNO = cmd.Field("SEQ").AsLong();
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


bool SQL4Order:: SelOrderPriority(string orderType, long& orderPriority)
{

	bool ret=false;
	string functionName="SQL4Order :: SelOrderPriority()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_ORDER_TYPE  WHERE ORDER_TYPE =:p_ORDER_TYPE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_TYPE") = orderType;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("ORDER_PRIORITY").IsNull())
			{
				orderPriority = cmd.Field("ORDER_PRIORITY").AsLong();
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



bool SQL4Order:: SelCarPlanBandInfo(string carNO, string workType, CarPlanBandInfo& carPlanBandInfoBase)
{

	bool ret=false;
	string functionName="SQL4Order :: SelCarPlanBandInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string carType = "";
		//string workType = "";
		string planNO = "";
		string planSrc = "";
		long planDetailID = 0;
		string enterFlag = "";
		string orderFlag = "";
		iDA::DateTime bandTime = DB_TIME_NULL;

		carPlanBandInfoBase.setCarNO(carNO);
		carPlanBandInfoBase.setWorkType(workType);

		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE ";
		strSql += " CAR_NO =:p_CAR_NO AND ";
		strSql += " WORK_TYPE =:p_WORK_TYPE ";
		strSql += " ORDER BY  BAND_TIME  ASC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_WORK_TYPE") = workType;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("CAR_TYPE").IsNull())
			{
				carType = cmd.Field("CAR_TYPE").AsString();
				carPlanBandInfoBase.setCarType(carType);
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


bool SQL4Order:: CarEnterYardExist(string carNO)
{
	bool ret=false;
	string functionName="SQL4Order :: CarEnterYardExist()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string enterFlag = CarPlanBandInfo::ENTER_YARD_2_YES;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE CAR_NO =:p_CAR_NO AND ";
		strSql += "  ENTER_FLAG = :p_ENTER_FLAG ";
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


bool SQL4Order:: CarOrderFlagExist(string carNO, string workType)
{
	bool ret=false;
	string functionName="SQL4Order :: CarOrderFlagExist()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string orderFlag = CarPlanBandInfo::ORDER_FLAG_2_HAVE_ORDER;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE ";
		strSql += " CAR_NO =:p_CAR_NO AND ";
		strSql += " WORK_TYPE =:p_WORK_TYPE AND ";
		strSql += " ORDER_FLAG = :p_ORDER_FLAG ";
		strSql += " ORDER BY  BAND_TIME  ASC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_ORDER_FLAG") = orderFlag;

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

bool SQL4Order:: SelScrapCodeReqWgtFormL3(string planNO, 
																					  string workType, //L3是卸料XL还是装车ZC
																					  string& locCode, 
																					  string& scrapCode, 
																					  string& compCode, 
																					  long& reqWgt)
{

	bool ret=false;
	string functionName="SQL4Order :: SelScrapCodeReqWgtFormL3()";
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


bool SQL4Order:: SelScrapCodeReqWgtFromEAF(string planNO, 
																						   long planDetailID, 
																						   string& scrapCode, 
																						   long& reqWgt)
{

	bool ret=false;
	string functionName="SQL4Order :: SelScrapCodeReqWgtFromEAF()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_EAF_L2_PLAN_DETAIL  WHERE ";
		strSql += " PONO =:p_PLAN_NO  AND  ";
		strSql += " DETAIL_ID = :p_DETAIL_ID ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_DETAIL_ID") = planDetailID;

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


bool SQL4Order:: SelScrapCodeReqWgtFromBOF(string planNO, 
																						   long planDetailID, 
																						   string& scrapCode, 
																						   long& reqWgt)
{

	bool ret=false;
	string functionName="SQL4Order :: SelScrapCodeReqWgtFromBOF()";
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

bool SQL4Order:: SelBayNOByParkingNO(string parkingNO,string& bayNO)
{

	bool ret=false;
	string functionName="SQL4Order :: SelBayNOByParkingNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_INFO_DEFINE  WHERE PARKING_NO =:p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PARKING_NO") = parkingNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("BAY_NO").IsNull())
			{
				bayNO = cmd.Field("BAY_NO").AsString();
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


bool SQL4Order:: SelMatStockInfoByGridNO(string gridNO, string&matCode, string& compCode, long& stockWgt)
{

	bool ret=false;
	string functionName="SQL4Order :: SelMatStockInfoByGridNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_YARDMAP_GRID_DEFINE  WHERE GRID_NO =:p_GRID_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_GRID_NO") = gridNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
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
				stockWgt = cmd.Field("MAT_WGT").AsLong();
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


bool SQL4Order:: SelBayXCenterByParkingNO(string parkingNO, string& bayNO, long& xCenter)
{

	bool ret=false;
	string functionName="SQL4Order :: SelBayXCenterByParkingNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_INFO_DEFINE  WHERE PARKING_NO =:p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_PARKING_NO") = parkingNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("BAY_NO").IsNull())
			{
				bayNO = cmd.Field("BAY_NO").AsString();
			}
			if(!cmd.Field("X_CENTER").IsNull())
			{
				xCenter = cmd.Field("X_CENTER").AsLong();
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



bool SQL4Order:: SelMapGMWEAFData(string scrapCode, 
																		long reqWgt, 
																		string bayNO, 
																		long xCenterParking,  
																		MapGridMatWgtEAF& mapGridMatWgtEAFBase )
{

	bool ret=false;
	string functionName="SQL4Order :: SelMapGMWEAFData()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		bool wgtEnough = false;

		string gridNO = "";
		string matCode = "";
		long calWgt = 0;

		long stockWgt = 0;//每个料格内的库存量
		long allWgt = 0;//所有料格库存量和

		vector<string> vecGridMatWgt;//单个料格信息

		string exterSystem = EventParkingHandler::EXTER_SYSTEM_EAF;
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_YARDMAP_GRID_DEFINE  WHERE MAT_CODE  IN  ";
		strSql += " ( ";
		strSql += " SELECT MAT_CODE FROM UACS_L3_MAT_RELATION_INFO WHERE EXTER_SYSTEM = :p_EXTER_SYSTEM AND MAT_CODE_RELATE = :p_MAT_CODE_RELATE ";
		strSql += " ) ";
		strSql += " AND BAY_NO = :p_BAY_NO ";
		strSql += " ORDER BY ABS(X_CENTER - :p_X_CENTER_PARKING)  ASC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_EXTER_SYSTEM") = exterSystem;
		cmd.Param("p_MAT_CODE_RELATE") = scrapCode;
		cmd.Param("p_BAY_NO") = bayNO;
		cmd.Param("p_X_CENTER_PARKING") = xCenterParking;

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
			allWgt = allWgt + stockWgt;


			//量还不够===============================================
			if ( allWgt < reqWgt )
			{
				//误差值 > MPE_WGT（常量100kg）  不够
				if (abs(allWgt - reqWgt) > EventParkingHandler::MPE_WGT)
				{
					vecGridMatWgt.push_back(gridNO);
					vecGridMatWgt.push_back(matCode);
					vecGridMatWgt.push_back(StringHelper::ToString(stockWgt));
					mapGridMatWgtEAFBase.insert(MapGridMatWgtEAF::value_type(nCount, vecGridMatWgt));
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
				if (abs(needWgt) > EventParkingHandler::MPE_WGT)//误差值 > MPE_WGT（常量100kg） 需要增加
				{
					vecGridMatWgt.push_back(gridNO);
					vecGridMatWgt.push_back(matCode);
					vecGridMatWgt.push_back(StringHelper::ToString(needWgt));
					mapGridMatWgtEAFBase.insert(MapGridMatWgtEAF::value_type(nCount, vecGridMatWgt));
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



bool SQL4Order:: InsOrderDataBase(OrderDataBase matOrderDataBase)
{

	bool ret=false;
	string functionName="SQL4Order :: InsOrderDataBase()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "INSERT INTO  UACS_ORDER_DATA( ";
		strSql += " ORDER_NO,  ";
		strSql += " ORDER_GROUP_NO,  ";
		strSql += " EXE_SEQ, ";
		strSql += " ORDER_TYPE, ";
		strSql += " ORDER_PRIORITY, ";
		strSql += " ORDER_STATUS, ";
		strSql += " ORDER_DEL_FLAG, ";
		strSql += " PLAN_SRC, ";
		strSql += " PLAN_NO, ";
		strSql += " PLAN_DETAIL_ID, ";
		strSql += " SCRAP_CODE, ";
		strSql += " REQ_WEIGHT, ";
		strSql += " CAR_NO, ";
		strSql += " CAR_TYPE, ";
		strSql += " BAY_NO, ";
		strSql += " MAT_CODE, ";
		strSql += " COMP_CODE, ";
		strSql += " CAL_WEIGHT, ";
		strSql += " ACT_WEIGHT, ";
		strSql += " FROM_STOCK_NO, ";
		strSql += " TO_STOCK_NO, ";
		strSql += " DOWN_POS_SEQ, ";
		strSql += " REC_TIME )";

		strSql +="	VALUES( ";
		strSql += " :p_ORDER_NO, ";
		strSql += " :p_ORDER_GROUP_NO, ";
		strSql += " :p_EXE_SEQ, ";
		strSql += " :p_ORDER_TYPE, ";
		strSql += " :p_ORDER_PRIORITY, ";
		strSql += " :p_ORDER_STATUS, ";
		strSql += " :p_ORDER_DEL_FLAG, ";
		strSql += " :p_PLAN_SRC, ";
		strSql += " :p_PLAN_NO, ";
		strSql += " :p_PLAN_DETAIL_ID, ";
		strSql += " :p_SCRAP_CODE, ";
		strSql += " :p_REQ_WEIGHT, ";
		strSql += " :p_CAR_NO, ";
		strSql += " :p_CAR_TYPE, ";
		strSql += " :p_BAY_NO, ";
		strSql += " :p_MAT_CODE, ";
		strSql += " :p_COMP_CODE, ";
		strSql += " :p_CAL_WEIGHT, ";
		strSql += " :p_ACT_WEIGHT, ";
		strSql += " :p_FROM_STOCK_NO, ";
		strSql += " :p_TO_STOCK_NO, ";
		strSql += " :p_DOWN_POS_SEQ, ";
		strSql += " :p_REC_TIMIE ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_NO") = matOrderDataBase.getOrderNO();
		cmd.Param("p_ORDER_GROUP_NO") = matOrderDataBase.getOrderGroupNO();
		cmd.Param("p_EXE_SEQ") = matOrderDataBase.getExeSeq();		
		cmd.Param("p_ORDER_TYPE") = matOrderDataBase.getOrderType();
		cmd.Param("p_ORDER_PRIORITY") = matOrderDataBase.getOrderPriority();
		cmd.Param("p_ORDER_STATUS") = matOrderDataBase.getOrderStatus();
		cmd.Param("p_ORDER_DEL_FLAG") = matOrderDataBase.getOrderDelFlag();
		cmd.Param("p_PLAN_SRC") = matOrderDataBase.getPlanSrc();
		cmd.Param("p_PLAN_NO") = matOrderDataBase.getPlanNO();
		cmd.Param("p_PLAN_DETAIL_ID") = matOrderDataBase.getPlanDetailID();
		cmd.Param("p_SCRAP_CODE") = matOrderDataBase.getScrapCode();
		cmd.Param("p_REQ_WEIGHT") = matOrderDataBase.getReqWeight();
		cmd.Param("p_CAR_NO") = matOrderDataBase.getCarNO();
		cmd.Param("p_CAR_TYPE") = matOrderDataBase.getCarType();
		cmd.Param("p_BAY_NO") = matOrderDataBase.getBayNO();
		cmd.Param("p_MAT_CODE") = matOrderDataBase.getMatCode();
		cmd.Param("p_COMP_CODE") = matOrderDataBase.getCompCode();
		cmd.Param("p_CAL_WEIGHT") = matOrderDataBase.getCalWeight();
		cmd.Param("p_ACT_WEIGHT") = matOrderDataBase.getActWeight();
		cmd.Param("p_FROM_STOCK_NO") = matOrderDataBase.getFromStockNO();
		cmd.Param("p_TO_STOCK_NO") = matOrderDataBase.getToStockNO();
		cmd.Param("p_DOWN_POS_SEQ") = matOrderDataBase.getDownPosSeq();
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


bool SQL4Order:: InsOrderQueueBase(OrderQueueBase matOrderQueueBase)
{

	bool ret=false;
	string functionName="SQL4Order :: InsOrderQueueBase()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = "INSERT INTO  UACS_ORDER_QUEUE( ";
		strSql += " ORDER_NO,  ";
		strSql += " ORDER_GROUP_NO,  ";
		strSql += " EXE_SEQ, ";
		strSql += " ORDER_TYPE, ";
		strSql += " ORDER_PRIORITY, ";

		strSql += " EXE_ENABLE, ";
		strSql += " CRANE_NO, ";
		strSql += " CMD_STATUS, ";
		strSql += " CMD_SEQ, ";
		
		strSql += " PLAN_SRC, ";
		strSql += " PLAN_NO, ";
		strSql += " PLAN_DETAIL_ID, ";
		strSql += " SCRAP_CODE, ";
		strSql += " REQ_WEIGHT, ";
		strSql += " CAR_NO, ";
		strSql += " CAR_TYPE, ";
		strSql += " BAY_NO, ";
		strSql += " MAT_CODE, ";
		strSql += " COMP_CODE, ";
		strSql += " CAL_WEIGHT, ";
		strSql += " ACT_WEIGHT, ";
		strSql += " FROM_STOCK_NO, ";
		strSql += " TO_STOCK_NO, ";
		strSql += " DOWN_POS_SEQ, ";
		strSql += " REC_TIME )";

		strSql +="	VALUES( ";
		strSql += " :p_ORDER_NO, ";
		strSql += " :p_ORDER_GROUP_NO, ";
		strSql += " :p_EXE_SEQ, ";
		strSql += " :p_ORDER_TYPE, ";
		strSql += " :p_ORDER_PRIORITY, ";

		strSql += " :p_EXE_ENABLE, ";
		strSql += " :p_CRANE_NO, ";
		strSql += " :p_CMD_STATUS, ";
		strSql += " :p_CMD_SEQ, ";
		
		strSql += " :p_PLAN_SRC, ";
		strSql += " :p_PLAN_NO, ";
		strSql += " :p_PLAN_DETAIL_ID, ";
		strSql += " :p_SCRAP_CODE, ";
		strSql += " :p_REQ_WEIGHT, ";
		strSql += " :p_CAR_NO, ";
		strSql += " :p_CAR_TYPE, ";
		strSql += " :p_BAY_NO, ";
		strSql += " :p_MAT_CODE, ";
		strSql += " :p_COMP_CODE, ";
		strSql += " :p_CAL_WEIGHT, ";
		strSql += " :p_ACT_WEIGHT, ";
		strSql += " :p_FROM_STOCK_NO, ";
		strSql += " :p_TO_STOCK_NO, ";
		strSql += " :p_DOWN_POS_SEQ, ";
		strSql += " :p_REC_TIMIE ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_NO") = matOrderQueueBase.getOrderNO();
		cmd.Param("p_ORDER_GROUP_NO") = matOrderQueueBase.getOrderGroupNO();
		cmd.Param("p_EXE_SEQ") = matOrderQueueBase.getExeSeq();		
		cmd.Param("p_ORDER_TYPE") = matOrderQueueBase.getOrderType();
		cmd.Param("p_ORDER_PRIORITY") = matOrderQueueBase.getOrderPriority();

		cmd.Param("p_EXE_ENABLE") = matOrderQueueBase.getExeEnable();
		cmd.Param("p_CRANE_NO") = matOrderQueueBase.getCraneNO();
		cmd.Param("p_CMD_STATUS") = matOrderQueueBase.getCmdStatus();
		cmd.Param("p_CMD_SEQ") = matOrderQueueBase.getCmdSeq();
		
		cmd.Param("p_PLAN_SRC") = matOrderQueueBase.getPlanSrc();
		cmd.Param("p_PLAN_NO") = matOrderQueueBase.getPlanNO();
		cmd.Param("p_PLAN_DETAIL_ID") = matOrderQueueBase.getPlanDetailID();
		cmd.Param("p_SCRAP_CODE") = matOrderQueueBase.getScrapCode();
		cmd.Param("p_REQ_WEIGHT") = matOrderQueueBase.getReqWeight();
		cmd.Param("p_CAR_NO") = matOrderQueueBase.getCarNO();
		cmd.Param("p_CAR_TYPE") = matOrderQueueBase.getCarType();
		cmd.Param("p_BAY_NO") = matOrderQueueBase.getBayNO();
		cmd.Param("p_MAT_CODE") = matOrderQueueBase.getMatCode();
		cmd.Param("p_COMP_CODE") = matOrderQueueBase.getCompCode();
		cmd.Param("p_CAL_WEIGHT") = matOrderQueueBase.getCalWeight();
		cmd.Param("p_ACT_WEIGHT") = matOrderQueueBase.getActWeight();
		cmd.Param("p_FROM_STOCK_NO") = matOrderQueueBase.getFromStockNO();
		cmd.Param("p_TO_STOCK_NO") = matOrderQueueBase.getToStockNO();
		cmd.Param("p_DOWN_POS_SEQ") = matOrderQueueBase.getDownPosSeq();
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


bool SQL4Order:: SelQCFlag(string planNO, string& qcFlag)
{

	bool ret=false;
	string functionName="SQL4Order :: SelQCFlag()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_L3_MAT_IN_OUT_INFO  WHERE WORK_SEQ_NO =:p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_SEQ_NO") = planNO;

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("QC_FLAG").IsNull())
			{
				qcFlag = cmd.Field("QC_FLAG").AsString();
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

bool SQL4Order:: SelLiftMode(string matCode, string compCode, string& liftMode)
{

	bool ret=false;
	string functionName="SQL4Order :: SelLiftMode()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_L3_MAT_RELATION_INFO  WHERE ";
		strSql += " MAT_CODE =:p_MAT_CODE  AND ";
		strSql += " COMP_CODE = :p_COMP_CODE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Param("p_COMP_CODE") = compCode;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("LIFT_MODE").IsNull())
			{
				liftMode = cmd.Field("LIFT_MODE").AsString();
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

bool SQL4Order:: SelCraneNOEAFBayByLfitMode(string bayNO, string liftMode, string& craneNO)
{

	bool ret=false;
	string functionName="SQL4Order :: SelCraneNOEAFBayByLfitMode()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_CRANE_DEFINE  WHERE ";
		strSql += " BAY_NO =:p_BAY_NO  AND ";
		strSql += " CLAMP_TYPE = :p_CLAMP_TYPE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_BAY_NO") = bayNO;
		cmd.Param("p_CLAMP_TYPE") = liftMode;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("CRANE_NO").IsNull())
			{
				craneNO = cmd.Field("CRANE_NO").AsString();
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


long SQL4Order:: SelBayLength(string bayNO)
{
	string functionName="SQL4Order :: SelBayLength()";
	LOG log(functionName, AUTO_CATCH_PID);
	long bayLength=0;
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_YARDMAP_YARD_DEFINE  WHERE ";
		strSql += " BAY_NO =:p_BAY_NO  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_BAY_NO") = bayNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("LENGTH").IsNull())
			{
				bayLength = cmd.Field("LENGTH").AsLong();
			}
			break;
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
	return bayLength;
}


long SQL4Order:: SelCraneNumInBay(string bayNO)
{
	string functionName="SQL4Order :: SelCraneNumInBay()";
	LOG log(functionName, AUTO_CATCH_PID);
	long craneNum=0;
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT COUNT(*)  AS  CRANE_NUM  FROM UACS_CRANE_DEFINE  WHERE ";
		strSql += " BAY_NO =:p_BAY_NO  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_BAY_NO") = bayNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("CRANE_NUM").IsNull())
			{
				craneNum = cmd.Field("CRANE_NUM").AsLong();
			}
			break;
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
	return craneNum;
}


long SQL4Order:: SelGridXCenter(string gridNO)
{
	string functionName="SQL4Order :: SelGridXCenter()";
	LOG log(functionName, AUTO_CATCH_PID);
	long xCenter=0;
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT X_CENTER  FROM UACS_YARDMAP_GRID_DEFINE  WHERE ";
		strSql += " GRID_NO =:p_GRID_NO  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_GRID_NO") = gridNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("X_CENTER").IsNull())
			{
				xCenter = cmd.Field("X_CENTER").AsLong();
			}
			break;
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
	return xCenter;
}


bool SQL4Order:: SelCraneNOByBaySeq(string bayNO, long seqNO, string& craneNO)
{
	bool ret=false;
	string functionName="SQL4Order :: SelCraneNOBaySeq()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_CRANE_DEFINE  WHERE ";
		strSql += " BAY_NO =:p_BAY_NO  AND ";
		strSql += " SEQ_NO = :p_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_BAY_NO") = bayNO;
		cmd.Param("p_SEQ_NO") = seqNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("CRANE_NO").IsNull())
			{
				craneNO = cmd.Field("CRANE_NO").AsString();
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


bool SQL4Order:: UpdOrderQueueCmdStatus(long orderNO, long cmdSeq, string cmdStauts, long curWgt)
{

	bool ret=false;
	string functionName="SQL4Order :: UpdOrderQueueCmdStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		
		strSql = " UPDATE UACS_ORDER_QUEUE SET ";
		strSql += " CMD_SEQ = :p_CMD_SEQ , ";
		strSql += " CMD_STATUS = :p_CMD_STATUS , ";
		strSql += " CUR_WEIGHT = :p_CUR_WEIGHT , ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ORDER_NO = :p_ORDER_NO ";		

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CMD_SEQ") = cmdSeq;
		cmd.Param("p_CMD_STATUS") = cmdStauts;
		cmd.Param("p_CUR_WEIGHT") = curWgt;		
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

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

bool SQL4Order:: UpdOrderQueueWgt(long orderNO, long curWgt)
{

	bool ret=false;
	string functionName="SQL4Order :: UpdOrderQueueWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";

		strSql = " UPDATE UACS_ORDER_QUEUE SET ";
		strSql += " ACT_WEIGHT = NVL(ACT_WEIGHT, 0) + :p_CUR_WEIGHT , ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ORDER_NO = :p_ORDER_NO ";		

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CUR_WEIGHT") = curWgt;		
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

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


bool SQL4Order:: UpdOrderDataWgt(long orderNO, long curWgt)
{

	bool ret=false;
	string functionName="SQL4Order :: UpdOrderDataWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";

		strSql = " UPDATE UACS_ORDER_DATA SET ";
		strSql += " ACT_WEIGHT = NVL(ACT_WEIGHT, 0) + :p_CUR_WEIGHT , ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ORDER_NO = :p_ORDER_NO ";		

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CUR_WEIGHT") = curWgt;		
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

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

bool SQL4Order:: UpdOrderDataStatus(long orderNO, string stauts)
{

	bool ret=false;
	string functionName="SQL4Order :: UpdOrderDataStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";

		strSql = " UPDATE UACS_ORDER_DATA SET ";
		strSql += " ORDER_STATUS = :p_ORDER_STATUS , ";
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ORDER_NO = :p_ORDER_NO ";		

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_STATUS") = stauts;		
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

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

bool SQL4Order:: SelOrderQueueWgt(long orderNO, long& reqWgt,  long& actWgt)
{
	bool ret=false;
	string functionName="SQL4Order :: SelOrderQueueWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_ORDER_QUEUE  WHERE ";
		strSql += " ORDER_NO =:p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("REQ_WEIGHT").IsNull())
			{
				reqWgt = cmd.Field("REQ_WEIGHT").AsLong();
			}
			if(!cmd.Field("ACT_WEIGHT").IsNull())
			{
				actWgt = cmd.Field("ACT_WEIGHT").AsLong();
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


bool SQL4Order:: SelOrderQueueInfo(long orderNO, OrderQueueBase& orderQueueInfo)
{
	bool ret=false;
	string functionName="SQL4Order :: SelOrderQueueInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_ORDER_QUEUE  WHERE ";
		strSql += " ORDER_NO =:p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_ORDER_NO") = orderNO;
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;

			//1
			if(!cmd.Field("ORDER_NO").IsNull())
			{
				orderQueueInfo.setOrderNO( cmd.Field("ORDER_NO").AsLong() ); 
			}
			//2
			if(!cmd.Field("ORDER_GROUP_NO").IsNull())
			{
				orderQueueInfo.setOrderGroupNO( cmd.Field("ORDER_GROUP_NO").AsLong() ); 
			}
			//3
			if(!cmd.Field("EXE_SEQ").IsNull())
			{
				orderQueueInfo.setExeSeq( cmd.Field("EXE_SEQ").AsLong() ); 
			}
			//4
			if(!cmd.Field("ORDER_TYPE").IsNull())
			{
				orderQueueInfo.setOrderType( cmd.Field("ORDER_TYPE").AsString() ); 
			}
			//5
			if(!cmd.Field("ORDER_PRIORITY").IsNull())
			{
				orderQueueInfo.setOrderPriority( cmd.Field("ORDER_PRIORITY").AsLong() ); 
			}
			//6
			if(!cmd.Field("EXE_ENABLE").IsNull())
			{
				orderQueueInfo.setExeEnable( cmd.Field("EXE_ENABLE").AsString() ); 
			}
			//7
			if(!cmd.Field("CRANE_NO").IsNull())
			{
				orderQueueInfo.setCraneNO( cmd.Field("CRANE_NO").AsString() ); 
			}
			//8
			if(!cmd.Field("CMD_STATUS").IsNull())
			{
				orderQueueInfo.setCmdStatus( cmd.Field("CMD_STATUS").AsString() ); 
			}
			//9
			if(!cmd.Field("CMD_SEQ").IsNull())
			{
				orderQueueInfo.setCmdSeq( cmd.Field("CMD_SEQ").AsLong() ); 
			}
			//10
			if(!cmd.Field("PLAN_SRC").IsNull())
			{
				orderQueueInfo.setPlanSrc( cmd.Field("PLAN_SRC").AsString() ); 
			}
			//11
			if(!cmd.Field("PLAN_NO").IsNull())
			{
				orderQueueInfo.setPlanNO( cmd.Field("PLAN_NO").AsString() ); 
			}
			//12
			if(!cmd.Field("PLAN_DETAIL_ID").IsNull())
			{
				orderQueueInfo.setPlanDetailID( cmd.Field("PLAN_DETAIL_ID").AsLong() ); 
			}
			//13
			if(!cmd.Field("SCRAP_CODE").IsNull())
			{
				orderQueueInfo.setScrapCode( cmd.Field("SCRAP_CODE").AsString() ); 
			}
			//14
			if(!cmd.Field("REQ_WEIGHT").IsNull())
			{
				orderQueueInfo.setReqWeight( cmd.Field("REQ_WEIGHT").AsLong() ); 
			}
			//15
			if(!cmd.Field("CAR_NO").IsNull())
			{
				orderQueueInfo.setCarNO( cmd.Field("CAR_NO").AsString() ); 
			}
			//16
			if(!cmd.Field("CAR_TYPE").IsNull())
			{
				orderQueueInfo.setCarType( cmd.Field("CAR_TYPE").AsString() ); 
			}
			//17
			if(!cmd.Field("BAY_NO").IsNull())
			{
				orderQueueInfo.setBayNO( cmd.Field("BAY_NO").AsString() ); 
			}
			//18
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				orderQueueInfo.setMatCode( cmd.Field("MAT_CODE").AsString() ); 
			}
			//19
			if(!cmd.Field("COMP_CODE").IsNull())
			{
				orderQueueInfo.setCompCode( cmd.Field("COMP_CODE").AsString() ); 
			}
			//20
			if(!cmd.Field("CAL_WEIGHT").IsNull())
			{
				orderQueueInfo.setCalWeight( cmd.Field("CAL_WEIGHT").AsLong() ); 
			}
			//21
			if(!cmd.Field("ACT_WEIGHT").IsNull())
			{
				orderQueueInfo.setActWeight( cmd.Field("ACT_WEIGHT").AsLong() ); 
			}
			//22
			if(!cmd.Field("CUR_WEIGHT").IsNull())
			{
				orderQueueInfo.setCurWeight( cmd.Field("CUR_WEIGHT").AsLong() ); 
			}
			//23
			if(!cmd.Field("FROM_STOCK_NO").IsNull())
			{
				orderQueueInfo.setFromStockNO( cmd.Field("FROM_STOCK_NO").AsString() ); 
			}
			//24
			if(!cmd.Field("TO_STOCK_NO").IsNull())
			{
				orderQueueInfo.setToStockNO( cmd.Field("TO_STOCK_NO").AsString() ); 
			}
			//25
			if(!cmd.Field("DOWN_POS_SEQ").IsNull())
			{
				orderQueueInfo.setDownPosSeq( cmd.Field("DOWN_POS_SEQ").AsLong() ); 
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


bool SQL4Order:: DelOrderQueue(long orderNO)
{

	bool ret=false;
	string functionName="SQL4Order :: DelOrderQueue()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";

		strSql = " DELETE  FROM  UACS_ORDER_QUEUE  WHERE  ";
		strSql += " ORDER_NO = :p_ORDER_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_ORDER_NO") = orderNO;	

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

bool SQL4Order:: UpdYardMapMatWgt(string gridNO, long matWgt, string calChar)
{

	bool ret=false;
	string functionName="SQL4Order :: UpdYardMapMatWgt()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSqlCal = "";
		if (calChar == "+")
		{
			strSqlCal = " MAT_WGT = NVL(MAT_WGT, 0) + :p_MAT_WGT , ";
		}
		else
		{
			strSqlCal = " MAT_WGT = NVL(MAT_WGT, 0) - :p_MAT_WGT , ";
		}


		string strSql="";

		strSql = " UPDATE UACS_YARDMAP_GRID_DEFINE  SET ";
		strSql += strSqlCal;
		strSql += " UPD_TIME = :p_UPD_TIME ";
		strSql += " WHERE ORDER_NO = :p_ORDER_NO ";		

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_WGT") = matWgt;		
		cmd.Param("p_UPD_TIME") = iDA::DateTime::Now();

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


bool SQL4Order:: DelParkingCarBandInfo(string planNO)
{

	bool ret=false;
	string functionName="SQL4Order :: DelParkingCarBandInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";

		strSql = " DELETE  FROM  UACS_PARKING_CAR_PLAN_INFO  WHERE  ";
		strSql += " PLAN_NO = :p_PLAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

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