#include "Adapter_UACS_CRANE_MOVEORDER_MSG.h"

using namespace Monitor;



Adapter_UACS_CRANE_MOVEORDER_MSG::Adapter_UACS_CRANE_MOVEORDER_MSG(void)
{
}



Adapter_UACS_CRANE_MOVEORDER_MSG::~Adapter_UACS_CRANE_MOVEORDER_MSG(void)
{



}

bool Adapter_UACS_CRANE_MOVEORDER_MSG:: SelMsgID(long& msgID)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_MOVEORDER_MSG :: SelMsgID()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		//采用db2中的序列来记录指令号
		strSql = " SELECT SEQ_MSG_ID.NEXTVAL AS SEQ FROM SYSIBM.SYSDUMMY1 ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("SEQ").IsNull())
			{
				msgID = cmd.Field("SEQ").AsLong();
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


//除了心跳电文不插入表外，其它的下发给行车的指令电文存入数据库
bool Adapter_UACS_CRANE_MOVEORDER_MSG:: insertMoveOrderMsg(long msgID, 
																																   long craneNO,
																																   long orderID,
																																   long matWeight, 
																																   long matType, 
																																   long planUpX,
																																   long planUpY,
																																   long planUpZ,
																																   long upRotateAngle,
																																   long planDownX,
																																   long planDownY,
																																   long planDownZ,
																																   long downRotateAngle,
																																   long shortCMD, 
																																   long currentX, 
																																   long currentY, 
																																   long currentZ )
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_MOVEORDER_MSG :: insertMoveOrderMsg()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_CRANE_ORDER_MSG( ";
		strSql += "MSG_ID, ";
		strSql += "CRANE_NO, ";
		strSql += "ORDER_ID, ";
		strSql += "MAT_WEIGHT, ";
		strSql += "MAT_TYPE, ";
		strSql += "PLAN_UP_X, ";
		strSql += "PLAN_UP_Y, ";
		strSql += "PLAN_UP_Z, ";
		strSql += "UP_ROTATE_ANGLE_SET, ";
		strSql += "PLAN_DOWN_X, ";
		strSql += "PLAN_DOWN_Y, ";
		strSql += "PLAN_DOWN_Z, ";
		strSql += "DOWN_ROTATE_ANGLE_SET, ";
		strSql += "SHORT_CMD , ";
		strSql += "ACT_X , ";
		strSql += "ACT_Y ,  ";
		strSql += "ACT_Z, ";
		strSql += "REC_TIME ) ";

		strSql += " VALUES( ";
		strSql += " :p_msgID,";
		strSql += " :p_craneNO,";
		strSql += " :p_orderID, ";
		strSql += " :p_matWeight,";
		strSql += " :p_matType,";
		strSql += " :p_planUpX, ";
		strSql += " :p_planUpY, ";
		strSql += " :p_planUpZ, ";
		strSql += " :p_upRotateAngle, ";
		strSql += " :p_planDownX, ";
		strSql += " :p_planDownY, ";
		strSql += " :p_planDownZ, ";
		strSql += " :p_downRotateAngle, ";
		strSql += " :p_shortCMD,  ";
		strSql += " :p_currentX, ";
		strSql += " :p_currentY, ";
		strSql += " :p_currentZ,";
		strSql += " :p_recTime )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_msgID") =msgID;
		cmd.Param("p_craneNO") =craneNO;
		cmd.Param("p_orderID") =orderID;
		cmd.Param("p_matWeight") =matWeight;
		cmd.Param("p_matType") =matType;
		cmd.Param("p_planUpX") =planUpX ;
		cmd.Param("p_planUpY") =planUpY;
		cmd.Param("p_planUpZ") =planUpZ;
		cmd.Param("p_upRotateAngle") =upRotateAngle;
		cmd.Param("p_planDownX") =planDownX;
		cmd.Param("p_planDownY") =planDownY;
		cmd.Param("p_planDownZ") =planDownZ;
		cmd.Param("p_downRotateAngle") =downRotateAngle;
		cmd.Param("p_shortCMD") =shortCMD;
		cmd.Param("p_currentX") =currentX;
		cmd.Param("p_currentY") =currentY;
		cmd.Param("p_currentZ") =currentZ;
		cmd.Param("p_recTime") =iDA::DateTime::Now();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<" insertMoveOrderMsg 成功： CRANE_NO="<<craneNO<<endl;

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


bool Adapter_UACS_CRANE_MOVEORDER_MSG:: insertMoveOrderMsgMidPT(long msgID, 
																																				map<long, map<string, long> > mapMidPointList)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_MOVEORDER_MSG :: insertMoveOrderMsgMidPT()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_CRANE_ORDER_MSG_TURN_POINT( ";
		strSql += "MSG_ID, ";
		strSql += "REC_TIME, ";
		strSql += "PLAN_TURN_X1, ";
		strSql += "PLAN_TURN_Y1, ";
		strSql += "PLAN_TURN_X2, ";
		strSql += "PLAN_TURN_Y2, ";
		strSql += "PLAN_TURN_X3, ";
		strSql += "PLAN_TURN_Y3, ";
		strSql += "PLAN_TURN_X4, ";
		strSql += "PLAN_TURN_Y4, ";
		strSql += "PLAN_TURN_X5, ";
		strSql += "PLAN_TURN_Y5, ";
		strSql += "PLAN_TURN_X6, ";
		strSql += "PLAN_TURN_Y6, ";
		strSql += "PLAN_TURN_X7, ";
		strSql += "PLAN_TURN_Y7, ";
		strSql += "PLAN_TURN_X8, ";
		strSql += "PLAN_TURN_Y8, ";
		strSql += "PLAN_TURN_X9, ";
		strSql += "PLAN_TURN_Y9, ";
		strSql += "PLAN_TURN_X10, ";
		strSql += "PLAN_TURN_Y10, ";
		strSql += "PLAN_TURN_X11, ";
		strSql += "PLAN_TURN_Y11, ";
		strSql += "PLAN_TURN_X12, ";
		strSql += "PLAN_TURN_Y12, ";
		strSql += "PLAN_TURN_X13, ";
		strSql += "PLAN_TURN_Y13, ";
		strSql += "PLAN_TURN_X14, ";
		strSql += "PLAN_TURN_Y14, ";
		strSql += "PLAN_TURN_X15, ";
		strSql += "PLAN_TURN_Y15, ";
		strSql += "PLAN_TURN_X16, ";
		strSql += "PLAN_TURN_Y16, ";
		strSql += "PLAN_TURN_X17, ";
		strSql += "PLAN_TURN_Y17, ";
		strSql += "PLAN_TURN_X18, ";
		strSql += "PLAN_TURN_Y18, ";
		strSql += "PLAN_TURN_X19, ";
		strSql += "PLAN_TURN_Y19, ";
		strSql += "PLAN_TURN_X20, ";
		strSql += "PLAN_TURN_Y20 ) ";

		strSql += " VALUES( ";
		strSql += " :p_msgID,";
		strSql += " :p_recTime, ";
		strSql += " :p_planTurnX1,";
		strSql += " :p_planTurnY1,";
		strSql += " :p_planTurnX2,";
		strSql += " :p_planTurnY2,";
		strSql += " :p_planTurnX3,";
		strSql += " :p_planTurnY3,";
		strSql += " :p_planTurnX4,";
		strSql += " :p_planTurnY4,";
		strSql += " :p_planTurnX5,";
		strSql += " :p_planTurnY5,";
		strSql += " :p_planTurnX6,";
		strSql += " :p_planTurnY6,";
		strSql += " :p_planTurnX7,";
		strSql += " :p_planTurnY7,";
		strSql += " :p_planTurnX8,";
		strSql += " :p_planTurnY8,";
		strSql += " :p_planTurnX9,";
		strSql += " :p_planTurnY9,";
		strSql += " :p_planTurnX10,";
		strSql += " :p_planTurnY10,";
		strSql += " :p_planTurnX11,";
		strSql += " :p_planTurnY11,";
		strSql += " :p_planTurnX12,";
		strSql += " :p_planTurnY12,";
		strSql += " :p_planTurnX13,";
		strSql += " :p_planTurnY13,";
		strSql += " :p_planTurnX14,";
		strSql += " :p_planTurnY14,";
		strSql += " :p_planTurnX15,";
		strSql += " :p_planTurnY15,";
		strSql += " :p_planTurnX16,";
		strSql += " :p_planTurnY16,";
		strSql += " :p_planTurnX17,";
		strSql += " :p_planTurnY17,";
		strSql += " :p_planTurnX18,";
		strSql += " :p_planTurnY18,";
		strSql += " :p_planTurnX19,";
		strSql += " :p_planTurnY19,";
		strSql += " :p_planTurnX20,";
		strSql += " :p_planTurnY20 )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_msgID") =msgID;
		cmd.Param("p_recTime") =iDA::DateTime::Now();

		//解析 mapMidPointList
		map<string, long> mapMidPoint;
		string planTurnX = "p_planTurnX";
		string planTurnY = "p_planTurnY";
		string paramX = "";
		string paramY = "";
		for (int i = 1; i <= 20; i++)
		{
			mapMidPoint = mapMidPointList[i];
			paramX = planTurnX + StringHelper::ToString(i);
			paramY = planTurnY + StringHelper::ToString(i);
			cmd.Param(paramX) =mapMidPoint["X"];
			cmd.Param(paramY) =mapMidPoint["Y"];
		}

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();
		ret=true;
		log.Debug()<<__FUNCTION__<<" insertMoveOrderMsgMidPT 成功! "<<endl;

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



//2018.7.1 zhangyuhong add
//新增行车报警代码写入数据库表-行车报警履历表
//UACS_CRANE_ALARM_HIS
bool Adapter_UACS_CRANE_MOVEORDER_MSG::insertCraneAlarmMsg(string craneNO, 
																																  long orderID, 
																																  long alarmCode)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_MOVEORDER_MSG :: insertCraneAlarmMsg()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_CRANE_ALARM_HIS( ";
		strSql += "CRANE_NO, ";
		strSql += "ORDER_ID, ";
		strSql += "ALARM_CODE ) ";

		strSql += " VALUES( :p_craneNO,";
		strSql += " :p_orderID, ";
		strSql += " :P_alarmCode ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_craneNO") =craneNO;
		cmd.Param("p_orderID") =orderID;
		cmd.Param("P_alarmCode") =alarmCode ;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" insertCraneAlarmMsg 成功： CRANE_NO="<<craneNO<<endl;


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


//2018.7.12 zhangyuhong add
//新增行车手自动切换履历表：主要是为了记录 行车 手自动模式突变的情况
//UACS_CRANE_AUTOMANU_SWITCH_HIS
bool Adapter_UACS_CRANE_MOVEORDER_MSG::insertCraneAutoManuSwitch(string craneNO, 
																 string switchBefore, 
																 string switchAfter)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_MOVEORDER_MSG :: insertCraneAutoManuSwitch()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_CRANE_AUTOMANU_SWITCH_HIS( ";
		strSql += "CRANE_NO, ";
		strSql += "SWITCH_BEFORE, ";
		strSql += "SWITCH_AFTER ) ";

		strSql += " VALUES( :p_craneNO,";
		strSql += " :p_switchBefore, ";
		strSql += " :P_switchAfter ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_craneNO") =craneNO;
		cmd.Param("p_switchBefore") =switchBefore;
		cmd.Param("P_switchAfter") =switchAfter ;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" insertCraneAutoManuSwitch 成功： CRANE_NO="<<craneNO<<endl;


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



bool Adapter_UACS_CRANE_MOVEORDER_MSG::insertCraneUrgentRecord(long eventNO, 
																																		   long orderNO, 
																																		   string craneNO, 
																																		   long xAct, 
																																		   long yAct, 
																																		   long zAct, 
																																		   long hasCoil)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_MOVEORDER_MSG :: insertCraneUrgentRecord()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_CRANE_URGENT_RECORD( ";
		strSql += "EVENT, ";
		strSql += "ORDER_NO, ";
		strSql += "CRANE_NO, ";
		strSql += "X_ACT, ";
		strSql += "Y_ACT, ";
		strSql += "Z_ACT, ";
		strSql += "HAS_COIL ) ";

		strSql += " VALUES(";
		strSql += " :p_eventNO,";
		strSql += " :p_orderNO, ";
		strSql += " :p_craneNO, ";
		strSql += " :p_xAct, ";
		strSql += " :p_yAct, ";
		strSql += " :p_zAct, ";
		strSql += " :P_hasCoil ) ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_eventNO") =eventNO;
		cmd.Param("p_orderNO") =orderNO;
		cmd.Param("p_craneNO") =craneNO;
		cmd.Param("p_xAct") =xAct;
		cmd.Param("p_yAct") =yAct;
		cmd.Param("p_zAct") =zAct;
		cmd.Param("P_hasCoil") =hasCoil ;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<" insertCraneUrgentRecord 成功： CRANE_NO="<<craneNO<<endl;


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

bool Adapter_UACS_CRANE_MOVEORDER_MSG:: SelXMaxXMinYSplit(long pointX, long pointY, long& xLimitMax, long& xLimitMin, long& ySplit)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_MOVEORDER_MSG :: SelXMaxXMinYSplit()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		long nCount = 0;
		string strSql="";
		strSql = " SELECT * FROM UACS_YARDMAP_GRID_DEFINE  WHERE  ";
		strSql += " :p_POINT_X > X_LIMIT_MIN AND ";
		strSql += " :p_POINT_X < X_LIMIT_MAX AND ";
		strSql += " :p_POINT_Y > Y_LIMIT_MIN AND ";
		strSql += " :p_POINT_Y < Y_LIMIT_MAX  ORDER BY ";
		strSql += " ABS(X_CENTER - :p_POINT_X)  ASC ";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Execute();

		while (cmd.FetchNext())
		{
			nCount = 1;
			if(!cmd.Field("X_LIMIT_MIN").IsNull())
			{
				xLimitMin = cmd.Field("X_LIMIT_MIN").AsLong();
			}
			if(!cmd.Field("X_LIMIT_MAX").IsNull())
			{
				xLimitMax = cmd.Field("X_LIMIT_MAX").AsLong();
			}
			if(!cmd.Field("Y_SPLIT").IsNull())
			{
				ySplit = cmd.Field("Y_SPLIT").AsLong();
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



