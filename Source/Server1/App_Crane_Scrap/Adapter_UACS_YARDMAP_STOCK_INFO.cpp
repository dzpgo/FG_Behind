#include "Adapter_UACS_YARDMAP_STOCK_INFO.h"

using namespace Monitor;



Adapter_UACS_YARDMAP_STOCK_INFO::Adapter_UACS_YARDMAP_STOCK_INFO(void)
{
}



Adapter_UACS_YARDMAP_STOCK_INFO::~Adapter_UACS_YARDMAP_STOCK_INFO(void)
{
}

bool Adapter_UACS_YARDMAP_STOCK_INFO::SelStockNOByXY(string bayNO, long x, long y, string& stockNO)
{

	bool ret=false;
	string functionName="Adapter_UACS_YARDMAP_STOCK_INFO :: SelStockNOByXY()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " SELECT * FROM ";
		strSql += " ( ";
		strSql += " SELECT GRID_NO AS STOCK_NO, BAY_NO, X_START, X_END, Y_START, Y_END  FROM UACS_YARDMAP_GRID_DEFINE  ";
		strSql += " UNION ";
		strSql += " SELECT PARKING_NO AS STOCK_NO, BAY_NO, X_START, X_END, Y_START, Y_END  FROM UACS_PARKING_INFO_DEFINE ";
		strSql += " ) ";
		strSql += " WHERE BAY_NO = :p_BAY_NO AND  ";
		strSql += " X_START < :p_X AND  ";
		strSql += " X_END > :p_X AND  ";
		strSql += " Y_START < :p_Y AND  ";
		strSql += " Y_END > :p_Y  ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_X") =x;	
		cmd.Param("p_Y") =y;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("STOCK_NO").IsNull())
			{
				stockNO = cmd.Field("STOCK_NO").AsString();
			}
			ret = true;
			return ret;
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


bool Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromDumpingInfo(string stockNO, map<string, long>& mapXYZValue)
{

	bool ret=false;
	string functionName="Adapter_UACS_YARDMAP_STOCK_INFO :: SelXYZValueFromDumpingInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long temp = DB_INT_NULL;
		string strSql="";
		strSql = " SELECT * FROM UACS_DUMPING_INFO_DEFINE WHERE DUMPING_NO = :p_DUMPING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_DUMPING_NO") = stockNO;	
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("X_START").IsNull())
			{
				temp = cmd.Field("X_START").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("X_START", temp));
			}
			if(!cmd.Field("X_END").IsNull())
			{
				temp = cmd.Field("X_END").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("X_END", temp));
			}
			if(!cmd.Field("X_CENTER").IsNull())
			{
				temp = cmd.Field("X_CENTER").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("X_CENTER", temp));
			}

			if(!cmd.Field("Y_START").IsNull())
			{
				temp = cmd.Field("Y_START").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("Y_START", temp));
			}
			if(!cmd.Field("Y_END").IsNull())
			{
				temp = cmd.Field("Y_END").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("Y_END", temp));
			}
			if(!cmd.Field("Y_CENTER").IsNull())
			{
				temp = cmd.Field("Y_CENTER").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("Y_CENTER", temp));
			}

			ret = true;
			return ret;
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


bool Adapter_UACS_YARDMAP_STOCK_INFO::SelXYZValueFromGridInfo(string stockNO, map<string, long>& mapXYZValue)
{

	bool ret=false;
	string functionName="Adapter_UACS_YARDMAP_STOCK_INFO :: SelXYZValueFromGridInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long temp = DB_INT_NULL;
		string strSql="";
		strSql = " SELECT * FROM UACS_YARDMAP_GRID_DEFINE WHERE GRID_NO = :p_GRID_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_GRID_NO") = stockNO;	
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("X_START").IsNull())
			{
				temp = cmd.Field("X_START").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("X_START", temp));
			}
			if(!cmd.Field("X_END").IsNull())
			{
				temp = cmd.Field("X_END").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("X_END", temp));
			}
			if(!cmd.Field("X_CENTER").IsNull())
			{
				temp = cmd.Field("X_CENTER").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("X_CENTER", temp));
			}

			if(!cmd.Field("Y_START").IsNull())
			{
				temp = cmd.Field("Y_START").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("Y_START", temp));
			}
			if(!cmd.Field("Y_END").IsNull())
			{
				temp = cmd.Field("Y_END").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("Y_END", temp));
			}
			if(!cmd.Field("Y_CENTER").IsNull())
			{
				temp = cmd.Field("Y_CENTER").AsLong();
				mapXYZValue.insert(map<string, long>::value_type("Y_CENTER", temp));
			}

			ret = true;
			return ret;
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


bool Adapter_UACS_YARDMAP_STOCK_INFO::SelMatCompCodeFromGridInfo(string stockNO, string& matCode, string& compCode)
{
	bool ret=false;
	string functionName="Adapter_UACS_YARDMAP_STOCK_INFO :: SelMatCompCodeFromGridInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = " SELECT  MAT_CODE, COMP_CODE  FROM UACS_YARDMAP_GRID_DEFINE WHERE GRID_NO = :p_GRID_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_GRID_NO") = stockNO;	
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("MAT_CODE").IsNull())
			{
				matCode = cmd.Field("MAT_CODE").AsString();
			}
			if(!cmd.Field("COMP_CODE").IsNull())
			{
				compCode = cmd.Field("COMP_CODE").AsString();
			}

			ret = true;
			return ret;
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


bool Adapter_UACS_YARDMAP_STOCK_INFO::SelCarCenterXY(string carScanNO, long& centerX, long& centerY)
{
	bool ret=false;
	string functionName="Adapter_UACS_YARDMAP_STOCK_INFO :: SelCarCenterXY()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = " SELECT  CENTER_X, CENTER_Y  FROM UACS_PARKING_SRS_CAR_INFO WHERE SCAN_NO = :p_SCAN_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_SCAN_NO") = carScanNO;	
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("CENTER_X").IsNull())
			{
				centerX = cmd.Field("CENTER_X").AsLong();
			}
			if(!cmd.Field("CENTER_Y").IsNull())
			{
				centerY = cmd.Field("CENTER_Y").AsLong();
			}

			ret = true;
			return ret;
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


bool Adapter_UACS_YARDMAP_STOCK_INFO::SelParkingInfo(string pakringNO, 
																												long& xStart, 
																												long& xEnd, 
																												long& xCenter, 
																												long& yStart, 
																												long& yEnd, 
																												long& yCenter, 
																												string& scanDir)
{
	bool ret=false;
	string functionName="Adapter_UACS_YARDMAP_STOCK_INFO :: SelParkingInfo()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql = " SELECT  *  FROM UACS_PARKING_INFO_DEFINE WHERE PARKING_NO = :p_PARKING_NO ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_PARKING_NO") = pakringNO;	
		cmd.Execute();

		if (cmd.FetchNext())
		{
			if(!cmd.Field("X_START").IsNull())
			{
				xStart = cmd.Field("X_START").AsLong();
			}
			if(!cmd.Field("X_END").IsNull())
			{
				xEnd = cmd.Field("X_END").AsLong();
			}
			if(!cmd.Field("X_CENTER").IsNull())
			{
				xCenter = cmd.Field("X_CENTER").AsLong();
			}
			if(!cmd.Field("Y_START").IsNull())
			{
				yStart = cmd.Field("Y_START").AsLong();
			}
			if(!cmd.Field("Y_END").IsNull())
			{
				yEnd = cmd.Field("Y_END").AsLong();
			}
			if(!cmd.Field("Y_CENTER").IsNull())
			{
				yCenter = cmd.Field("Y_CENTER").AsLong();
			}

			ret = true;
			return ret;
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