#include <climits>
#include "SQL4L3.h"

using namespace Monitor;



SQL4L3::SQL4L3(void)
{
}



SQL4L3::~SQL4L3(void)
{
}

bool SQL4L3:: DelMatInfo(string matCode)
{

	bool ret=false;
	string functionName="SQL4L3 :: DelMatInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="DELETE FROM UACS_L3_MAT_INFO WHERE MAT_CODE = :p_MAT_CODE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" DelMatInfo Sucess! "<<endl;


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


bool SQL4L3:: InsertMatInfo(string baseResource, string matCode, string matCName, string matType)
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_L3_MAT_INFO( ";
		strSql += "MAT_CODE, ";
		strSql += "BASE_RESOURCE, ";
		strSql += "MAT_CNAME, ";
		strSql += "MAT_TYPE, ";
		strSql += "REC_TIME )";


		strSql += " VALUES( :p_MAT_CODE,";
		strSql += " :p_BASE_RESOURCE, ";
		strSql += " :p_MAT_CNAME, ";
		strSql += " :p_MAT_TYPE, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Param("p_BASE_RESOURCE") =baseResource;
		cmd.Param("p_MAT_CNAME") =matCName;
		cmd.Param("p_MAT_TYPE") =matType;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" InsertMatInfo Sucess! "<<endl;


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


bool SQL4L3:: DelMatRelationInfo(string matCode, string compCode, string matCodeRelate)
{
	bool ret=false;
	string functionName="SQL4L3 :: DelMatRelationInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql = "";
		strSql = " DELETE  FROM UACS_L3_MAT_RELATION_INFO WHERE ";
		strSql += " MAT_CODE = :p_MAT_CODE AND ";
		strSql += " COMP_CODE = :p_COMP_CODE AND ";
		strSql += " MAT_CODE_RELATE = :p_MAT_CODE_RELATE";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Param("p_COMP_CODE") = compCode;
		cmd.Param("p_MAT_CODE_RELATE") = matCodeRelate;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" DelMatRelationInfo Sucess! "<<endl;
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


bool SQL4L3:: InsertMatRelationInfo(string exterSystem, string matCode, string compCode, string matCodeRelate)
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatRelationInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_L3_MAT_RELATION_INFO( ";
		strSql += "EXTER_SYSTEM, ";
		strSql += "MAT_CODE, ";
		strSql += "COMP_CODE, ";
		strSql += "MAT_CODE_RELATE, ";
		strSql += "REC_TIME )";


		strSql += " VALUES( ";
		strSql += " :p_EXTER_SYSTEM, ";
		strSql += " :p_MAT_CODE, ";
		strSql += " :p_COMP_CODE, ";
		strSql += " :p_MAT_CODE_RELATE, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_EXTER_SYSTEM") = exterSystem;
		cmd.Param("p_MAT_CODE") =matCode;
		cmd.Param("p_COMP_CODE") =compCode;
		cmd.Param("p_MAT_CODE_RELATE") =matCodeRelate;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" InsertMatRelationInfo Sucess! "<<endl;
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

bool SQL4L3:: DelMatGridInfo(string stockPlaceCode)
{

	bool ret=false;
	string functionName="SQL4L3 :: DelMatGridInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="DELETE FROM UACS_L3_MAT_GRID_INFO WHERE STOCK_PLACE_CODE = :p_STOCK_PLACE_CODE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STOCK_PLACE_CODE") = stockPlaceCode;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" DelMatGridInfo Sucess! "<<endl;


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



bool SQL4L3:: InsertMatGridInfo(string stockCode, //库区代码
															string stockPlaceCode, //料格代码
															string stockLocCode, //料条/跨跨代码
															long storermAddrMin, //料条/跨起点地址
															long storermAddrMax, //料条跨终点地址
															string matCode, //物料代码
															string compCode, //废钢钢制码
															string startTime)//开始时刻
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatGridInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_L3_MAT_GRID_INFO( ";
		strSql += "STOCK_CODE, ";
		strSql += "STOCK_PLACE_CODE, ";
		strSql += "STOCK_LOC_CODE, ";
		strSql += "STORERM_ADDR_MIN, ";
		strSql += "STORERM_ADDR_MAX, ";
		strSql += "MAT_CODE, ";
		strSql += "COMP_CODE, ";
		strSql += "START_TIME, ";
		strSql += "REC_TIME )";


		strSql += " VALUES( :p_STOCK_CODE,";
		strSql += " :p_STOCK_PLACE_CODE, ";
		strSql += " :p_STOCK_LOC_CODE, ";
		strSql += " :p_STORERM_ADDR_MIN, ";
		strSql += " :p_STORERM_ADDR_MAX, ";
		strSql += " :p_MAT_CODE, ";
		strSql += " :p_COMP_CODE, ";
		strSql += " :p_START_TIME, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_STOCK_CODE") = stockCode;
		cmd.Param("p_STOCK_PLACE_CODE") =stockPlaceCode;
		cmd.Param("p_STOCK_LOC_CODE") =stockLocCode;
		cmd.Param("p_STORERM_ADDR_MIN") =storermAddrMin;
		cmd.Param("p_STORERM_ADDR_MAX") =storermAddrMax;
		cmd.Param("p_MAT_CODE") =matCode;
		cmd.Param("p_COMP_CODE") =compCode;
		cmd.Param("p_START_TIME") =iDA::DateTime(startTime);
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" InsertMatGridInfo Sucess! "<<endl;


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


bool SQL4L3:: UpdYardMapGridInfo(string gridNO, string matCode, string compCode)
{

	bool ret=false;
	string functionName="SQL4L3 :: UpdYardMapGridInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql=" UPDATE  UACS_YARDMAP_GRID_DEFINE  SET  ";
		strSql += "MAT_CODE = :p_MAT_CODE, ";
		strSql += "COMP_CODE = :p_COMP_CODE, ";
		strSql += "MAT_WGT = 0, ";
		strSql += "L3_UPD_TIME = :p_L3_UPD_TIME ";
		strSql += "WHERE   GRID_NO = :p_GRID_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_MAT_CODE") = matCode;
		cmd.Param("p_COMP_CODE") = compCode;
		cmd.Param("p_L3_UPD_TIME") =iDA::DateTime::Now();
		cmd.Param("p_GRID_NO") = gridNO;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdYardMapGridInfo Sucess! "<<endl;
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


bool SQL4L3:: InitYardMapGridInfo(string gridNO)
{

	bool ret=false;
	string functionName="SQL4L3 :: InitYardMapGridInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql=" UPDATE  UACS_YARDMAP_GRID_DEFINE  SET  ";
		strSql += "MAT_CODE = NULL,  ";
		strSql += "COMP_CODE = NULL, ";
		strSql += "MAT_WGT = 0, ";
		strSql += "L3_UPD_TIME = :p_L3_UPD_TIME ";
		strSql += "WHERE   GRID_NO = :p_GRID_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_L3_UPD_TIME") =iDA::DateTime::Now();
		cmd.Param("p_GRID_NO") = gridNO;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" InitYardMapGridInfo Sucess! "<<endl;
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



bool SQL4L3:: DelMatInOutInfo(string workSeqNO)
{

	bool ret=false;
	string functionName="SQL4L3 :: DelMatInOutInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="DELETE FROM UACS_L3_MAT_IN_OUT_INFO WHERE WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" DelMatInOutInfo Sucess! "<<endl;


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


bool SQL4L3:: SelL3PlanInfo(string workSeqNO, L3PlanInfo& planInfo)
{

	bool ret=false;
	string functionName="SQL4L3 :: SelL3PlanInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		planInfo.setWorkSeqNO(workSeqNO);

		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_L3_MAT_IN_OUT_INFO WHERE WORK_SEQ_NO =:p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("OPERATE_FLAG").IsNull())
			{
				string operateFlag = cmd.Field("OPERATE_FLAG").AsString();
				planInfo.setOperateFlag(operateFlag);
			}
			if(!cmd.Field("CAR_NO").IsNull())
			{
				string carNO = cmd.Field("CAR_NO").AsString();
				planInfo.setCarNO(carNO);
			}
			if(!cmd.Field("WEIGH_APP_NO").IsNull())
			{
				string weighAppNO = cmd.Field("WEIGH_APP_NO").AsString();
				planInfo.setWeighAppNO(weighAppNO);
			}
			if(!cmd.Field("WEIGH_APP_TIME").IsNull())
			{
				iDA::DateTime weightAppTime = cmd.Field("WEIGH_APP_TIME").AsDateTime();
				planInfo.setWeighAppTime(weightAppTime);
			}
			if(!cmd.Field("REC_CREATOR").IsNull())
			{
				string recCreator = cmd.Field("REC_CREATOR").AsString();
				planInfo.setRecCreator(recCreator);
			}
			if(!cmd.Field("SRC_STOCK_CODE").IsNull())
			{
				string srcStockCode = cmd.Field("SRC_STOCK_CODE").AsString();
				planInfo.setSrcStockCode(srcStockCode);
			}
			if(!cmd.Field("SRC_LOC_CODE").IsNull())
			{
				string srcLocCode = cmd.Field("SRC_LOC_CODE").AsString();
				planInfo.setSrcLocCode(srcLocCode);
			}
			if(!cmd.Field("SRC_MAT_CODE").IsNull())
			{
				string srcMatCode = cmd.Field("SRC_MAT_CODE").AsString();
				planInfo.setSrcMatCode(srcMatCode);
			}
			if(!cmd.Field("SRC_COMP_CODE").IsNull())
			{
				string srcCompCode = cmd.Field("SRC_COMP_CODE").AsString();
				planInfo.setSrcCompCode(srcCompCode);
			}
			if(!cmd.Field("DST_STOCK_CODE").IsNull())
			{
			string dstStockCode = cmd.Field("DST_STOCK_CODE").AsString();
				planInfo.setDstStockCode(dstStockCode);
			}
			if(!cmd.Field("DST_LOC_CODE").IsNull())
			{
				string dstLocCode = cmd.Field("DST_LOC_CODE").AsString();
				planInfo.setDstLocCode(dstLocCode);
			}
			if(!cmd.Field("DST_MAT_CODE").IsNull())
			{
				string dstMatCode = cmd.Field("DST_MAT_CODE").AsString();
				planInfo.setDstMatCode(dstMatCode);
			}
			if(!cmd.Field("DST_COMP_CODE").IsNull())
			{
				string dstCompCode = cmd.Field("DST_COMP_CODE").AsString();
				planInfo.setDstCompCode(dstCompCode);
			}
			if(!cmd.Field("ESTIMATE_WGT").IsNull())
			{
				long estimateWgt = cmd.Field("ESTIMATE_WGT").AsLong();
				planInfo.setEstimateWgt(estimateWgt);
			}
			if(!cmd.Field("START_FLAG").IsNull())
			{
				string startFlag = cmd.Field("START_FLAG").AsString();
				planInfo.setStartFlag(startFlag);
			}
			if(!cmd.Field("QC_FLAG").IsNull())
			{
				string qcFlag = cmd.Field("QC_FLAG").AsString();
				planInfo.setQCFlag(qcFlag);
			}
			if(!cmd.Field("PLAN_TYPE").IsNull())
			{
				string planType = cmd.Field("PLAN_TYPE").AsString();
				planInfo.setPlanType(planType);
			}
			if(!cmd.Field("PLAN_STATUS").IsNull())
			{
				string planStatus = cmd.Field("PLAN_STATUS").AsString();
				planInfo.setPlanStatus(planStatus);
			}
			if(!cmd.Field("PLAN_VALID").IsNull())
			{
				string planValid = cmd.Field("PLAN_VALID").AsString();
				planInfo.setPlanValid(planValid);
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

bool SQL4L3:: InsertMatInOutInfo(SmartData sd, string planType)
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatInOutInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//流水号
		string carNO = sd["CAR_NO"].toString();//车号
		string weighAppNo = sd["WEIGH_APP_NO"].toString();//计量申请号
		string weighAppTime = sd["WEIGH_APP_TIME"].toString();//计量申请时刻
		string recCreator = sd["REC_CREATOR"].toString();//操作者
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源库位代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//发方物料代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//发方钢制代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的库位代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//收方物料代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//收方钢制代码
		int  intEstimateWgt = sd["ESTIMATE_WGT"].toInt();//估计重量
		long estimateWgt = (long)intEstimateWgt;
		string startFlag = sd["START_FLAG"].toString();//建议归堆标志  G:建议   C:取消建议
		string qcFlag = sd["QC_FLAG"].toString();//是否需要质检标记  1：需要  0：不需要

		string planStatus = "1";
		string planValid = "1";

		string strSql="";
		strSql="INSERT INTO  UACS_L3_MAT_IN_OUT_INFO( ";
		strSql += "OPERATE_FLAG, ";
		strSql += "WORK_SEQ_NO, ";
		strSql += "CAR_NO, ";
		strSql += "WEIGH_APP_NO, ";
		strSql += "WEIGH_APP_TIME, ";
		strSql += "REC_CREATOR, ";
		strSql += "SRC_STOCK_CODE, ";
		strSql += "SRC_LOC_CODE, ";
		strSql += "SRC_MAT_CODE, ";
		strSql += "SRC_COMP_CODE, ";
		strSql += "DST_STOCK_CODE, ";
		strSql += "DST_LOC_CODE, ";
		strSql += "DST_MAT_CODE, ";
		strSql += "DST_COMP_CODE, ";
		strSql += "ESTIMATE_WGT, ";
		strSql += "START_FLAG, ";
		strSql += "QC_FLAG, ";
		strSql += "PLAN_TYPE, ";
		strSql += "PLAN_STATUS, ";
		strSql += "PLAN_VALID, ";
		strSql += "REC_TIME )";

		strSql += " VALUES( :p_OPERATE_FLAG, ";
		strSql += " :p_WORK_SEQ_NO, ";
		strSql += " :p_CAR_NO, ";
		strSql += " :p_WEIGH_APP_NO, ";
		strSql += " :p_WEIGH_APP_TIME, ";
		strSql += " :p_REC_CREATOR, ";
		strSql += " :p_SRC_STOCK_CODE, ";
		strSql += " :p_SRC_LOC_CODE, ";
		strSql += " :p_SRC_MAT_CODE, ";
		strSql += " :p_SRC_COMP_CODE, ";
		strSql += " :p_DST_STOCK_CODE, ";
		strSql += " :p_DST_LOC_CODE, ";
		strSql += " :p_DST_MAT_CODE, ";
		strSql += " :p_DST_COMP_CODE, ";
		strSql += " :p_ESTIMATE_WGT, ";
		strSql += " :p_START_FLAG, ";
		strSql += " :p_QC_FLAG, ";
		strSql += " :p_PLAN_TYPE, ";
		strSql += " :p_PLAN_STATUS, ";
		strSql += " :p_PLAN_VALID, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPERATE_FLAG") = operateFlag;
		cmd.Param("p_WORK_SEQ_NO") =workSeqNO;
		cmd.Param("p_CAR_NO") =carNO;
		cmd.Param("p_WEIGH_APP_NO") =weighAppNo;
		cmd.Param("p_WEIGH_APP_TIME") =iDA::DateTime(weighAppTime);
		cmd.Param("p_REC_CREATOR") =recCreator;
		cmd.Param("p_SRC_STOCK_CODE") =srcStockCode;
		cmd.Param("p_SRC_LOC_CODE") =srcLocCode;
		cmd.Param("p_SRC_MAT_CODE") =srcMatCode;
		cmd.Param("p_SRC_COMP_CODE") =srcCompCode;
		cmd.Param("p_DST_STOCK_CODE") =dstStockCode;
		cmd.Param("p_DST_LOC_CODE") =dstLocCode;
		cmd.Param("p_DST_MAT_CODE") =dstMatCode;
		cmd.Param("p_DST_COMP_CODE") =dstCompCode;
		cmd.Param("p_ESTIMATE_WGT") =estimateWgt;
		cmd.Param("p_START_FLAG") =startFlag;
		cmd.Param("p_QC_FLAG") =qcFlag;
		cmd.Param("p_PLAN_TYPE") =planType;
		cmd.Param("p_PLAN_STATUS") =planStatus;
		cmd.Param("p_PLAN_VALID") =planValid;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" InsertMatInOutInfo Sucess! "<<endl;
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


bool SQL4L3:: UpdateMatInOutInfo(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4L3 :: UpdateMatInOutInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//流水号
		string carNO = sd["CAR_NO"].toString();//车号
		string weighAppNo = sd["WEIGH_APP_NO"].toString();//计量申请号
		string weighAppTime = sd["WEIGH_APP_TIME"].toString();//计量申请时刻
		string recCreator = sd["REC_CREATOR"].toString();//操作者
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源库位代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//发方物料代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//发方钢制代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的库位代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//收方物料代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//收方钢制代码
		int  estimateWgt = sd["ESTIMATE_WGT"].toInt();//估计重量

		string strSql="";
		strSql="UPDATE  UACS_L3_MAT_IN_OUT_INFO  SET  ";
		strSql += "OPERATE_FLAG = :p_OPERATE_FLAG, ";
		strSql += "CAR_NO = :p_CAR_NO, ";
		strSql += "WEIGH_APP_NO = :p_WEIGH_APP_NO, ";
		strSql += "WEIGH_APP_TIME = :p_WEIGH_APP_TIME, ";
		strSql += "REC_CREATOR = :p_REC_CREATOR, ";
		strSql += "SRC_STOCK_CODE = :p_SRC_STOCK_CODE,  ";
		strSql += "SRC_LOC_CODE = :p_SRC_LOC_CODE,  ";
		strSql += "SRC_MAT_CODE = :p_SRC_MAT_CODE,  ";
		strSql += "SRC_COMP_CODE = :p_SRC_COMP_CODE,  ";
		strSql += "DST_STOCK_CODE = :p_DST_STOCK_CODE,  ";
		strSql += "DST_LOC_CODE = :p_DST_LOC_CODE,  ";
		strSql += "DST_MAT_CODE = :p_DST_MAT_CODE,  ";
		strSql += "DST_COMP_CODE = :p_DST_COMP_CODE,  ";
		strSql += "ESTIMATE_WGT = :p_ESTIMATE_WGT, ";		
		strSql += "UPD_TIME = :p_UPD_TIME ";
		strSql += "WHERE   WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPERATE_FLAG") = operateFlag;
		cmd.Param("p_WORK_SEQ_NO") =workSeqNO;
		cmd.Param("p_CAR_NO") =carNO;
		cmd.Param("p_WEIGH_APP_NO") =weighAppNo;
		cmd.Param("p_WEIGH_APP_TIME") =iDA::DateTime(weighAppTime);
		cmd.Param("p_REC_CREATOR") =recCreator;
		cmd.Param("p_SRC_STOCK_CODE") =srcStockCode;
		cmd.Param("p_SRC_LOC_CODE") =srcLocCode;
		cmd.Param("p_SRC_MAT_CODE") =srcMatCode;
		cmd.Param("p_SRC_COMP_CODE") =srcCompCode;
		cmd.Param("p_DST_STOCK_CODE") =dstStockCode;
		cmd.Param("p_DST_LOC_CODE") =dstLocCode;
		cmd.Param("p_DST_MAT_CODE") =dstMatCode;
		cmd.Param("p_DST_COMP_CODE") =dstCompCode;
		cmd.Param("p_ESTIMATE_WGT") =(long)estimateWgt;
		cmd.Param("p_UPD_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdateMatInOutInfo Sucess! "<<endl;


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


bool SQL4L3:: UpdateMatInOutInfoValid(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4L3 :: UpdateMatInOutInfoValid()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//流水号
		string carNO = sd["CAR_NO"].toString();//车号
		string weighAppNo = sd["WEIGH_APP_NO"].toString();//计量申请号
		string weighAppTime = sd["WEIGH_APP_TIME"].toString();//计量申请时刻
		string recCreator = sd["REC_CREATOR"].toString();//操作者
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源库位代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//发方物料代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//发方钢制代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的库位代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//收方物料代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//收方钢制代码
		int  estimateWgt = sd["ESTIMATE_WGT"].toInt();//估计重量

		string planValid = "2";

		string strSql="";
		strSql="UPDATE  UACS_L3_MAT_IN_OUT_INFO  SET  ";
		strSql += "OPERATE_FLAG = :p_OPERATE_FLAG, ";
		strSql += "CAR_NO = :p_CAR_NO, ";
		strSql += "WEIGH_APP_NO = :p_WEIGH_APP_NO, ";
		strSql += "WEIGH_APP_TIME = :p_WEIGH_APP_TIME, ";
		strSql += "REC_CREATOR = :p_REC_CREATOR, ";
		strSql += "SRC_STOCK_CODE = :p_SRC_STOCK_CODE,  ";
		strSql += "SRC_LOC_CODE = :p_SRC_LOC_CODE,  ";
		strSql += "SRC_MAT_CODE = :p_SRC_MAT_CODE,  ";
		strSql += "SRC_COMP_CODE = :p_SRC_COMP_CODE,  ";
		strSql += "DST_STOCK_CODE = :p_DST_STOCK_CODE,  ";
		strSql += "DST_LOC_CODE = :p_DST_LOC_CODE,  ";
		strSql += "DST_MAT_CODE = :p_DST_MAT_CODE,  ";
		strSql += "DST_COMP_CODE = :p_DST_COMP_CODE,  ";
		strSql += "ESTIMATE_WGT = :p_ESTIMATE_WGT, ";
		strSql += "PLAN_VALID = :p_PLAN_VALID, ";
		strSql += "UPD_TIME = :p_UPD_TIME ";
		strSql += "WHERE   WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPERATE_FLAG") = operateFlag;
		cmd.Param("p_WORK_SEQ_NO") =workSeqNO;
		cmd.Param("p_CAR_NO") =carNO;
		cmd.Param("p_WEIGH_APP_NO") =weighAppNo;
		cmd.Param("p_WEIGH_APP_TIME") =iDA::DateTime(weighAppTime);
		cmd.Param("p_REC_CREATOR") =recCreator;
		cmd.Param("p_SRC_STOCK_CODE") =srcStockCode;
		cmd.Param("p_SRC_LOC_CODE") =srcLocCode;
		cmd.Param("p_SRC_MAT_CODE") =srcMatCode;
		cmd.Param("p_SRC_COMP_CODE") =srcCompCode;
		cmd.Param("p_DST_STOCK_CODE") =dstStockCode;
		cmd.Param("p_DST_LOC_CODE") =dstLocCode;
		cmd.Param("p_DST_MAT_CODE") =dstMatCode;
		cmd.Param("p_DST_COMP_CODE") =dstCompCode;
		cmd.Param("p_ESTIMATE_WGT") =(long)estimateWgt;
		cmd.Param("p_PLAN_VALID") =planValid;
		cmd.Param("p_UPD_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" UpdateMatInOutInfoValid Sucess! "<<endl;


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


bool SQL4L3:: UpdL3PlanInfoPlanVlaid(string workSeqNO, string planValid)
{
	bool ret=false;
	string functionName="SQL4L3 :: UpdL3PlanInfoPlanVlaid()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{		
		string strSql="";
		strSql="UPDATE  UACS_L3_MAT_IN_OUT_INFO  SET  ";
		strSql += "PLAN_VALID = :p_PLAN_VALID, ";
		strSql += "UPD_TIME = :p_UPD_TIME ";
		strSql += "WHERE   WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_SEQ_NO") =workSeqNO;
		cmd.Param("p_PLAN_VALID") =planValid;
		cmd.Param("p_UPD_TIME") =iDA::DateTime::Now();
		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdL3PlanInfoPlanVlaid Sucess! "<<endl;


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




bool SQL4L3:: MatWeightInfoExist(string workSeqNO)
{

	bool ret=false;
	string functionName="SQL4L3 :: MatWeightInfoExist()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_L3_MAT_WEIGHT_INFO  WHERE WORK_SEQ_NO =:p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;
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



bool SQL4L3:: InsertMatWeightInfo(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatWeightInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//流水号
		string hcWorkSeqNO= sd["HC_WORK_SEQ_NO"].toString();//智能行车流水号
		string carNO = sd["CAR_NO"].toString();//车号
		string weighAppNo = sd["WEIGH_APP_NO"].toString();//计量申请号
		string weighAppTime = sd["WEIGH_APP_TIME"].toString();//计量申请时刻
		string recCreator = sd["REC_CREATOR"].toString();//操作者
		string weighNO = sd["WEIGH_NO"].toString();//磅单号
		int grossWgt = sd["GROSS_WGT"].toInt();//毛重
		int tareWgt = sd["TARE_WGT"].toInt();//皮重
		int netWgt = sd["NET_WGT"].toInt();//净重
		string grossTime = sd["GROSS_TIME"].toString();//毛重时刻
		string tareTime = sd["TARE_TIME"].toString();//皮重时刻
		string weighTime = sd["WEIGH_TIME"].toString();//称重时刻
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源库位代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//发方物料代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//发方钢制代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的库位代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//收方物料代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//收方钢制代码

		int loopCount = sd["LOOP_COUNT"].toInt();//rgv车辆装料循环次数

		string strSql="";
		strSql="INSERT INTO  UACS_L3_MAT_WEIGHT_INFO( ";
		strSql += "OPERATE_FLAG, ";
		strSql += "WORK_SEQ_NO, ";
		strSql += "HC_WORK_SEQ_NO, ";
		strSql += "CAR_NO, ";
		strSql += "WEIGH_APP_NO, ";
		strSql += "WEIGH_APP_TIME, ";
		strSql += "REC_CREATOR, ";
		strSql += "WEIGH_NO, ";
		strSql += "GROSS_WGT, ";
		strSql += "TARE_WGT, ";
		strSql += "NET_WGT, ";
		strSql += "GROSS_TIME, ";
		strSql += "TARE_TIME, ";
		strSql += "WEIGH_TIME, ";
		strSql += "SRC_STOCK_CODE, ";
		strSql += "SRC_LOC_CODE, ";
		strSql += "SRC_MAT_CODE, ";
		strSql += "SRC_COMP_CODE, ";
		strSql += "DST_STOCK_CODE, ";
		strSql += "DST_LOC_CODE, ";
		strSql += "DST_MAT_CODE, ";
		strSql += "DST_COMP_CODE, ";
		strSql += "LOOP_COUNT, ";
		strSql += "REC_TIME )";

		strSql += " VALUES( :p_OPERATE_FLAG, ";
		strSql += " :p_WORK_SEQ_NO, ";
		strSql += " :p_HC_WORK_SEQ_NO, ";
		strSql += " :p_CAR_NO, ";
		strSql += " :p_WEIGH_APP_NO, ";
		strSql += " :p_WEIGH_APP_TIME, ";
		strSql += " :p_REC_CREATOR, ";
		strSql += " :p_WEIGH_NO, ";
		strSql += " :p_GROSS_WGT, ";
		strSql += " :p_TARE_WGT, ";
		strSql += " :p_NET_WGT, ";
		strSql += " :p_GROSS_TIME, ";
		strSql += " :p_TARE_TIME, ";
		strSql += " :p_WEIGH_TIME, ";
		strSql += " :p_SRC_STOCK_CODE, ";
		strSql += " :p_SRC_LOC_CODE, ";
		strSql += " :p_SRC_MAT_CODE, ";
		strSql += " :p_SRC_COMP_CODE, ";
		strSql += " :p_DST_STOCK_CODE, ";
		strSql += " :p_DST_LOC_CODE, ";
		strSql += " :p_DST_MAT_CODE, ";
		strSql += " :p_DST_COMP_CODE, ";
		strSql += " :p_LOOP_COUNT, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPERATE_FLAG") = operateFlag;
		cmd.Param("p_WORK_SEQ_NO") =workSeqNO;
		cmd.Param("p_HC_WORK_SEQ_NO") =hcWorkSeqNO;
		cmd.Param("p_CAR_NO") =carNO;
		cmd.Param("p_WEIGH_APP_NO") =weighAppNo;

		if (weighAppTime.empty())
		{
			cmd.Param("p_WEIGH_APP_TIME") =weighAppTime;
		}
		else
		{
			cmd.Param("p_WEIGH_APP_TIME") =iDA::DateTime(weighAppTime);
		}		

		cmd.Param("p_REC_CREATOR") =recCreator;
		cmd.Param("p_WEIGH_NO") =weighNO;
		cmd.Param("p_GROSS_WGT") =(long)grossWgt;
		cmd.Param("p_TARE_WGT") =(long)tareWgt;
		cmd.Param("p_NET_WGT") = (long)netWgt;

		if (grossTime.empty())
		{
			cmd.Param("p_GROSS_TIME") =grossTime;
		}
		else
		{
			cmd.Param("p_GROSS_TIME") =iDA::DateTime(grossTime);
		}		

		if (tareTime.empty())
		{
			cmd.Param("p_TARE_TIME") =tareTime;
		}
		else
		{
			cmd.Param("p_TARE_TIME") =iDA::DateTime(tareTime);
		}		

		if (weighTime.empty())
		{
			cmd.Param("p_WEIGH_TIME") =weighTime;
		}
		else
		{
			cmd.Param("p_WEIGH_TIME") =iDA::DateTime(weighTime);
		}		

		cmd.Param("p_SRC_STOCK_CODE") =srcStockCode;
		cmd.Param("p_SRC_LOC_CODE") =srcLocCode;
		cmd.Param("p_SRC_MAT_CODE") =srcMatCode;
		cmd.Param("p_SRC_COMP_CODE") =srcCompCode;
		cmd.Param("p_DST_STOCK_CODE") =dstStockCode;
		cmd.Param("p_DST_LOC_CODE") =dstLocCode;
		cmd.Param("p_DST_MAT_CODE") =dstMatCode;
		cmd.Param("p_DST_COMP_CODE") =dstCompCode;
		cmd.Param("p_LOOP_COUNT") =(long)loopCount;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" InsertMatWeightInfo Sucess! "<<endl;


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

bool SQL4L3:: InsertMatWeightTable(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatWeightTable()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//插入主表
		InsertMatWeightInfo(sd);

		//若loopCount不为0 则有rgv称重数据 插入rgv表
		int loopCount  = sd["LOOP_COUNT"].toInt();
		if (loopCount > 0)
		{
			InsertMatWeightRGVInfo(sd);
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


bool SQL4L3:: InsertMatWeightRGVInfo(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatWeightRGVInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string workSeqNO = sd["WORK_SEQ_NO"].toString();
		string stockPlaceCode = "";
		string matCode = "";
		string compCode = "";
		int wgt = 0;

		int loopCount = sd["LOOP_COUNT"].toInt();//rgv车辆装料循环次数

		for (int i = 0; i < loopCount; ++i)
		{			
			//库位/料格号
			stockPlaceCode = sd["P4HC12_DETAIL"][i]["STOCK_PLACE_CODE"].toString();	
			//物料代码
			matCode = sd["P4HC12_DETAIL"][i]["MAT_CODE"].toString();
			//钢制代码
			compCode = sd["P4HC12_DETAIL"][i]["COMP_CODE"].toString();
			//分摊重量
			wgt = sd["P4HC12_DETAIL"][i]["WGT"].toInt();

			log.Info()<<"\n\t\t index in loop = "<<i<<":  stockPlaceCode = "<<stockPlaceCode<<" , matCode = "<<matCode<<" , compCode = "<<compCode<<" , wgt = "<<wgt<<endl;

			InsertMatWeightRGVInfoSingle(workSeqNO, stockPlaceCode, matCode, compCode, wgt);			
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


bool SQL4L3:: InsertMatWeightRGVInfoSingle(string workSeqNO, 
																				   string stockPlaceCode, 
																				   string matCode, 
																				   string compCode, 
																				   int wgt)
{

	bool ret=false;
	string functionName="SQL4L3 :: InsertMatWeightRGVInfoSingle()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_L3_MAT_WEIGHT_RGV_INFO( ";
		strSql += "WORK_SEQ_NO, ";
		strSql += "STOCK_PLACE_CODE, ";
		strSql += "MAT_CODE, ";
		strSql += "COMP_CODE, ";
		strSql += "WGT, ";
		strSql += "REC_TIME )";

		strSql += " VALUES( :p_WORK_SEQ_NO, ";
		strSql += " :p_STOCK_PLACE_CODE, ";
		strSql += " :p_MAT_CODE, ";
		strSql += " :p_COMP_CODE, ";
		strSql += " :p_WGT, ";
		strSql += " :p_REC_TIME )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;
		cmd.Param("p_STOCK_PLACE_CODE") =stockPlaceCode;
		cmd.Param("p_MAT_CODE") =matCode;
		cmd.Param("p_COMP_CODE") =compCode;
		cmd.Param("p_WGT") =(long)wgt;
		cmd.Param("p_REC_TIME") =iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" InsertMatWeightRGVInfoSingle Sucess! "<<endl;


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


bool SQL4L3:: UpdateMatWeightInfo(SmartData sd)
{

	bool ret=false;
	string functionName="SQL4L3 :: UpdateMatWeightInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string operateFlag = sd["OPERATE_FLAG"].toString();//操作标记 I-新增  D-删除
		string workSeqNO = sd["WORK_SEQ_NO"].toString();//流水号
		string hcWorkSeqNO= sd["HC_WORK_SEQ_NO"].toString();//智能行车流水号
		string carNO = sd["CAR_NO"].toString();//车号
		string weighAppNo = sd["WEIGH_APP_NO"].toString();//计量申请号
		string weighAppTime = sd["WEIGH_APP_TIME"].toString();//计量申请时刻
		string recCreator = sd["REC_CREATOR"].toString();//操作者
		string weighNO = sd["WEIGH_NO"].toString();//磅单号
		int grossWgt = sd["GROSS_WGT"].toInt();//毛重
		int tareWgt = sd["TARE_WGT"].toInt();//皮重
		int netWgt = sd["NET_WGT"].toInt();//净重
		string grossTime = sd["GROSS_TIME"].toString();//毛重时刻
		string tareTime = sd["TARE_TIME"].toString();//皮重时刻
		string weighTime = sd["WEIGH_TIME"].toString();//称重时刻
		string srcStockCode = sd["SRC_STOCK_CODE"].toString();//源库区代码
		string srcLocCode = sd["SRC_LOC_CODE"].toString();//源库位代码
		string srcMatCode = sd["SRC_MAT_CODE"].toString();//发方物料代码
		string srcCompCode = sd["SRC_COMP_CODE"].toString();//发方钢制代码
		string dstStockCode = sd["DST_STOCK_CODE"].toString();//目的库区代码
		string dstLocCode = sd["DST_LOC_CODE"].toString();//目的库位代码
		string dstMatCode = sd["DST_MAT_CODE"].toString();//收方物料代码
		string dstCompCode = sd["DST_COMP_CODE"].toString();//收方钢制代码

		int loopCount = sd["LOOP_COUNT"].toInt();//rgv车辆装料循环次数

		string strSql="";
		strSql="UPDATE  UACS_L3_MAT_WEIGHT_INFO  SET ";
		strSql += "OPERATE_FLAG = :p_OPERATE_FLAG, ";
		//strSql += "WORK_SEQ_NO = :p_WORK_SEQ_NO, ";
		strSql += "HC_WORK_SEQ_NO = :p_HC_WORK_SEQ_NO, ";
		strSql += "CAR_NO = :p_CAR_NO, ";
		strSql += "WEIGH_APP_NO = :p_WEIGH_APP_NO, ";
		strSql += "WEIGH_APP_TIME = :p_WEIGH_APP_TIME, ";
		strSql += "REC_CREATOR = :p_REC_CREATOR, ";
		strSql += "WEIGH_NO = :p_WEIGH_NO, ";
		strSql += "GROSS_WGT = :p_GROSS_WGT, ";
		strSql += "TARE_WGT = :p_TARE_WGT, ";
		strSql += "NET_WGT = :p_NET_WGT, ";
		strSql += "GROSS_TIME, = :p_GROSS_TIME ";
		strSql += "TARE_TIME = :p_TARE_TIME, ";
		strSql += "WEIGH_TIME = :p_WEIGH_TIME, ";
		strSql += "SRC_STOCK_CODE = :p_SRC_STOCK_CODE, ";
		strSql += "SRC_LOC_CODE = :p_SRC_LOC_CODE, ";
		strSql += "SRC_MAT_CODE = :p_SRC_MAT_CODE, ";
		strSql += "SRC_COMP_CODE = :p_SRC_COMP_CODE, ";
		strSql += "DST_STOCK_CODE = :p_DST_STOCK_CODE, ";
		strSql += "DST_LOC_CODE = :p_DST_STOCK_CODE, ";
		strSql += "DST_MAT_CODE = :p_DST_MAT_CODE, ";
		strSql += "DST_COMP_CODE = :p_DST_COMP_CODE, ";
		strSql += "LOOP_COUNT = :p_LOOP_COUNT, ";
		strSql += "UPD_TIME = :p_UPD_TIME ";
		strSql += "WHERE  WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_OPERATE_FLAG") = operateFlag;
		cmd.Param("p_WORK_SEQ_NO") =workSeqNO;
		cmd.Param("p_HC_WORK_SEQ_NO") =hcWorkSeqNO;
		cmd.Param("p_CAR_NO") =carNO;
		cmd.Param("p_WEIGH_APP_NO") =weighAppNo;
		cmd.Param("p_WEIGH_APP_TIME") =iDA::DateTime(weighAppTime);
		cmd.Param("p_REC_CREATOR") =recCreator;
		cmd.Param("p_WEIGH_NO") =weighNO;
		cmd.Param("p_GROSS_WGT") =(long)grossWgt;
		cmd.Param("p_TARE_WGT") =(long)tareWgt;
		cmd.Param("p_NET_WGT") = (long)netWgt;
		cmd.Param("p_GROSS_TIME") =iDA::DateTime(grossTime);
		cmd.Param("p_TARE_TIME") =iDA::DateTime(tareTime);
		cmd.Param("p_WEIGH_TIME") =iDA::DateTime(weighTime);
		cmd.Param("p_SRC_STOCK_CODE") =srcStockCode;
		cmd.Param("p_SRC_LOC_CODE") =srcLocCode;
		cmd.Param("p_SRC_MAT_CODE") =srcMatCode;
		cmd.Param("p_SRC_COMP_CODE") =srcCompCode;
		cmd.Param("p_DST_STOCK_CODE") =dstStockCode;
		cmd.Param("p_DST_LOC_CODE") =dstLocCode;
		cmd.Param("p_DST_MAT_CODE") =dstMatCode;
		cmd.Param("p_DST_COMP_CODE") =dstCompCode;
		cmd.Param("p_LOOP_COUNT") =(long)loopCount;
		cmd.Param("p_UPD_TIME") =iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<" UpdateMatWeightInfo Sucess! "<<endl;


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


bool SQL4L3:: DelMatWeightRGVInfo(string workSeqNO)
{

	bool ret=false;
	string functionName="SQL4L3 :: DelMatWeightRGVInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="DELETE  FROM   UACS_L3_MAT_WEIGHT_RGV_INFO WHERE  WORK_SEQ_NO = :p_WORK_SEQ_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_WORK_SEQ_NO") = workSeqNO;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" DelMatWeightRGVInfo Sucess! "<<endl;


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



bool SQL4L3:: SelCarPlanBandInfoExist(string carNO, string planNO, string workType)
{
	bool ret=false;
	string functionName="SQL4L3 :: SelCarPlanBandInfoExist()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE CAR_NO = :p_CAR_NO ";
		strSql += "  WORK_TYPE =:p_WORK_TYPE  AND  PLAN_NO = :p_PLAN_NO";
		
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount = 1;
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


bool SQL4L3:: InsCarPlanBandInfo(string carNO, 
															 string carType,  
															 string workType, 
															 string workSeqNO, 
															 string planSrc, 
															 string enterFlag, 
															 string orderFlag, 
															 iDA::DateTime bandTime)
{
	bool ret=false;
	string functionName="SQL4L3 :: InsCarPlanBandInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "INSERT INTO  UACS_PARKING_CAR_PLAN_INFO(";
		strSql +=" CAR_NO ,";
		strSql +=" CAR_TYPE ,";
		strSql +=" WORK_TYPE ,";
		strSql +=" PLAN_NO ,";
		strSql +=" PLAN_SRC ,";
		strSql +=" ENTER_FLAG ,";
		strSql +=" ORDER_FLAG ,";
		strSql +=" BAND_TIME, ";
		strSql +=" REC_TIME ) ";

		strSql += "VALUES( :p_CAR_NO, ";
		strSql += " :p_CAR_TYPE, ";
		strSql += " :p_WORK_TYPE, ";
		strSql += " :p_PLAN_NO, ";
		strSql += " :p_PLAN_SRC, ";
		strSql += " :p_ENTER_FLAG, ";
		strSql += " :p_ORDER_FLAG, ";
		strSql += " :p_BAND_TIME, ";
		strSql += " :p_REC_TIME) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_CAR_TYPE") = carType;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Param("p_PLAN_NO") = workSeqNO;
		cmd.Param("p_PLAN_SRC") = planSrc;
		cmd.Param("p_ENTER_FLAG") = enterFlag;
		cmd.Param("p_ORDER_FLAG") = orderFlag;
		cmd.Param("p_BAND_TIME") = bandTime;
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


bool SQL4L3:: DelCarPlanBandInfo(string carNO, string workSeqNO)
{
	bool ret=false;
	string functionName="SQL4L3 :: DelCarPlanBandInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " DELETE  FROM UACS_PARKING_CAR_PLAN_INFO  WHERE ";
		strSql +=" CAR_NO = :p_CAR_NO   AND  ";
		strSql +=" PLAN_NO = :p_PLAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = workSeqNO;

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


bool SQL4L3:: DelCarPlanBandInfoByWorkType(string carNO, string workSeqNO, string workType)
{
	bool ret=false;
	string functionName="SQL4L3 :: DelCarPlanBandInfoByWorkType()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " DELETE  FROM UACS_PARKING_CAR_PLAN_INFO  WHERE ";
		strSql +=" CAR_NO = :p_CAR_NO   AND  ";
		strSql +=" PLAN_NO = :p_PLAN_NO  AND ";
		strSql +=" WORK_TYPE = :p_WORK_TYPE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = workSeqNO;
		cmd.Param("p_WORK_TYPE") = workType;

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



bool SQL4L3:: SelCarStatus(string carNO, string planNO, string& enterFlag)
{
	bool ret=false;
	string functionName="SQL4L3 :: SelCarStatus()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE ";
		strSql += " CAR_NO = :p_CAR_NO  AND ";
		strSql += " PLAN_NO = :p_PLAN_NO";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("ENTER_FLAG").IsNull())
			{
				enterFlag = cmd.Field("ENTER_FLAG").AsString();
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

bool SQL4L3:: SelCarStatusByWokrType(string carNO, string planNO, string workType, string& enterFlag)
{
	bool ret=false;
	string functionName="SQL4L3 :: SelCarStatusByWokrType()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = "SELECT * FROM UACS_PARKING_CAR_PLAN_INFO WHERE ";
		strSql += " CAR_NO = :p_CAR_NO  AND ";
		strSql += " PLAN_NO = :p_PLAN_NO AND ";
		strSql += " WORK_TYPE = :p_WORK_TYPE ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_CAR_NO") = carNO;
		cmd.Param("p_PLAN_NO") = planNO;
		cmd.Param("p_WORK_TYPE") = workType;
		cmd.Execute();
		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("ENTER_FLAG").IsNull())
			{
				enterFlag = cmd.Field("ENTER_FLAG").AsString();
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