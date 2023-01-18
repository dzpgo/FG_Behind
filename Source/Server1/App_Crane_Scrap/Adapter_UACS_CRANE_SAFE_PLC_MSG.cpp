#include "Adapter_UACS_CRANE_SAFE_PLC_MSG.h"

using namespace Monitor;



Adapter_UACS_CRANE_SAFE_PLC_MSG::Adapter_UACS_CRANE_SAFE_PLC_MSG(void)
{
}



Adapter_UACS_CRANE_SAFE_PLC_MSG::~Adapter_UACS_CRANE_SAFE_PLC_MSG(void)
{
}


//发送SAFE PLC 电文记录到数据库表
bool Adapter_UACS_CRANE_SAFE_PLC_MSG:: insertSAFEPLCMsg(string craneNO, 
														   string msgID, 
														   string msgText)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_SAFE_PLC_MSG :: insertSAFEPLCMsg()";
	LOG log(functionName, AUTO_CATCH_PID);
	try
	{
		string strSql="";
		strSql="INSERT INTO  UACS_CRANE_SAFEPLC_MSG( ";
		strSql += "CRANE_NO, ";
		strSql += "MSG_ID, ";
		strSql += "MSG_TEXT) ";

		strSql += " VALUES( :p_craneNO,";
		strSql += " :p_msgID, ";
		strSql += " :p_msgText )";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_craneNO") =craneNO;
		cmd.Param("p_msgID") =msgID;
		cmd.Param("p_msgText") =msgText ;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret=true;

		log.Debug()<<__FUNCTION__<<"........... successed CRANE_NO="<<craneNO<<endl;


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
