#include <climits>
#include "SQL4SRS.h"

using namespace Monitor;



SQL4SRS::SQL4SRS(void)
{
}



SQL4SRS::~SQL4SRS(void)
{
}


bool SQL4SRS:: SelScanNO4Mat(string& scanNO)
{

	bool ret=false;
	string functionName="SQL4SRS :: SelScanNO4Mat()";
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


bool SQL4SRS:: SelScanNO4Car(string& scanNO)
{

	bool ret=false;
	string functionName="SQL4SRS :: SelScanNO4Car()";
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


bool SQL4SRS:: SelComLineNO(string module, int& lineNO)
{

	bool ret=false;
	string functionName="SQL4SRS :: SelComLineNO()";
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


bool SQL4SRS:: InsParkingSRSMatInfo(string scanNO, //扫描处理号
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
	string functionName="SQL4SRS :: InsParkingSRSMatInfo()";
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

bool SQL4SRS:: InsParkingSRSMatInfo2(string scanNO, //扫描处理号
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
	string functionName="SQL4SRS :: InsParkingSRSMatInfo2()";
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


bool SQL4SRS:: UpdParkingSRSMatInfo(string scanNO, 
																		string scanResult, 
																		long pointX, 
																		long pointY, 
																		long pointZ )	
{
	bool ret=false;
	string functionName="SQL4SRS :: UpdParkingSRSMatInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//更新激光扫描结果
		string strSql = "";
		strSql = "UPDATE  UACS_PARKING_SRS_MAT_INFO  SET ";
		strSql += " SCAN_RESULT = :p_SCAN_RESULT,  ";
		strSql += " POINT_X = :p_POINT_X, ";
		strSql += " POINT_Y = :p_POINT_Y, ";
		strSql += " POINT_Z = :p_POINT_Z, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SCAN_RESULT") = scanResult;
		cmd.Param("p_POINT_X") = pointX;
		cmd.Param("p_POINT_Y") = pointY;
		cmd.Param("p_POINT_Z") = pointZ;
		cmd.Param("p_SCAN_NO") = scanNO;
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

bool SQL4SRS:: InsParkingSRSCarInfo(string scanNO, 
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
																			string scanIP )
{
	bool ret=false;
	string functionName="SQL4SRS :: InsParkingSRSCarInfo()";
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

bool SQL4SRS:: SelParkingTreatmentNOCarNO(string parkingNO, string& parkingTreatmentNO, string& carNO)
{

	bool ret=false;
	string functionName="SQL4SRS :: SelParkingTreatmentNO()";
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


bool SQL4SRS:: SelRGVNO(string parkingNO, string& rgvNO)
{

	bool ret=false;
	string functionName="SQL4SRS :: SelRGVCarNO()";
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


bool SQL4SRS:: UpdParkingSRSCarInfo(string scanNO, 
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
																		long pointXMax,
																		long pointXMin, 
																		long pointYMax,
																		long pointYMin,
																		long centerX,
																		long centerY
																		)
{
	bool ret=false;
	string functionName="SQL4SRS :: UpdParkingSRSCarInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		//更新激光扫描结果
		string strSql = "";
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
		strSql += " POINT_X_MAX = :p_POINT_X_MAX, ";
		strSql += " POINT_X_MIN = :p_POINT_X_MIN, ";
		strSql += " POINT_Y_MAX = :p_POINT_Y_MAX, ";
		strSql += " POINT_Y_MIN = :p_POINT_Y_MIN, ";
		strSql += " CENTER_X = :p_CENTER_X, ";
		strSql += " CENTER_Y = :p_CENTER_Y, ";
		strSql += " REC_TIME = :p_REC_TIME ";
		strSql +="	WHERE  SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_SCAN_RESULT") = scanResult;
		cmd.Param("p_POINT_X_1") = pointX1;
		cmd.Param("p_POINT_Y_1") = pointY1;
		cmd.Param("p_POINT_Z_1") = pointZ1;
		cmd.Param("p_POINT_X_2") = pointX2;
		cmd.Param("p_POINT_Y_2") = pointY2;
		cmd.Param("p_POINT_Z_2") = pointZ2;
		cmd.Param("p_POINT_X_3") = pointX3;
		cmd.Param("p_POINT_Y_3") = pointY3;
		cmd.Param("p_POINT_Z_3") = pointZ3;
		cmd.Param("p_POINT_X_4") = pointX4;
		cmd.Param("p_POINT_Y_4") = pointY4;
		cmd.Param("p_POINT_Z_4") = pointZ4;

		cmd.Param("p_POINT_X_MAX") = pointXMax;
		cmd.Param("p_POINT_X_MIN") = pointXMin;
		cmd.Param("p_POINT_Y_MAX") = pointYMax;
		cmd.Param("p_POINT_Y_MIN") = pointYMin;
		cmd.Param("p_CENTER_X") = centerX;
		cmd.Param("p_CENTER_Y") = centerY;

		cmd.Param("p_SCAN_NO") = scanNO;
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


bool SQL4SRS:: SelOrderNOByMatScanNO(string matScanNO, long& orderNO)
{

	bool ret=false;
	string functionName="SQL4SRS :: SelOrderNOByMatScanNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = " SELECT  ORDER_NO  FROM UACS_PARKING_SRS_MAT_INFO  WHERE  ";
		strSql += " SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_NO") = matScanNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("ORDER_NO").IsNull())
			{
				orderNO = cmd.Field("ORDER_NO").AsLong();
			}
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


bool SQL4SRS:: SelOrderNOByCarScanNO(string carScanNO, long& orderNO)
{

	bool ret=false;
	string functionName="SQL4SRS :: SelOrderNOByCarScanNO()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = " SELECT  ORDER_NO  FROM UACS_PARKING_SRS_CAR_INFO  WHERE  ";
		strSql += " SCAN_NO  = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_NO") = carScanNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("ORDER_NO").IsNull())
			{
				orderNO = cmd.Field("ORDER_NO").AsLong();
			}
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



bool SQL4SRS:: UpdParkingRGVStatusSRS(string parkingNO, 
																					  long pointXMin, 
																					  long pointXMax, 
																					  long pointYMin, 
																					  long pointYMax)
{
	bool ret=false;
	string functionName="SQL4SRS :: UpdParkingRGVStatusSRS()";
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