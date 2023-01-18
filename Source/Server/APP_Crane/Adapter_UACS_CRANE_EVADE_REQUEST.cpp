#pragma once
#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"


using  namespace Monitor;

Adapter_UACS_CRANE_EVADE_REQUEST::Adapter_UACS_CRANE_EVADE_REQUEST(void)
{

}

Adapter_UACS_CRANE_EVADE_REQUEST::~Adapter_UACS_CRANE_EVADE_REQUEST(void)
{

}

bool  Adapter_UACS_CRANE_EVADE_REQUEST::GetData(string craneNO , CraneEvadeRequestBase &  craneEvadeBase)
{



	bool ret=false;
	string functionName="Adapter_UACS_CRANE_EVADE_REQUEST::GetData()";
	LOG log(functionName, AUTO_CATCH_PID);
	//LOG log(functionName);
	try
	{
		log.Debug()<<" craneNO = "<<craneNO << "准备获取避让指令： UACS_CRANE_EVADE_REQUEST "<<endl;

		if (craneNO == DB_STR_NULL)
		{
			log.Debug()<<" craneNO is fault , return false "<<endl;
			return ret;
		}

		string	strSql=" SELECT * FROM UACS_CRANE_EVADE_REQUEST WHERE TARGET_CRANE_NO =:p_TARGET_CRANE_NO " ;
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object
		cmd.Param("p_TARGET_CRANE_NO") = craneNO;
		cmd.Execute();

		if (cmd.FetchNext())
		{
			craneEvadeBase.setTargetCraneNO(craneNO);
			if (!cmd.Field("SENDER").IsNull())
			{
				craneEvadeBase.setSender(cmd.Field("SENDER").AsString());
			}
			if (!cmd.Field("ORIGINAL_SENDER").IsNull())
			{
				craneEvadeBase.setOriginalSender(cmd.Field("ORIGINAL_SENDER").AsString());
			}
			if (!cmd.Field("EVADE_X_REQUEST").IsNull())
			{
				craneEvadeBase.setEvadeXRequest(cmd.Field("EVADE_X_REQUEST").AsLong());
			}
			if (!cmd.Field("EVADE_X").IsNull())
			{
				craneEvadeBase.setEvadeX(cmd.Field("EVADE_X").AsLong());
			}
			if (!cmd.Field("EVADE_DIRECTION").IsNull())
			{
				craneEvadeBase.setEvadeDirection(cmd.Field("EVADE_DIRECTION").AsString());
			}
			if (!cmd.Field("EVADE_ACTION_TYPE").IsNull())
			{
				craneEvadeBase.setEvadeActionType(cmd.Field("EVADE_ACTION_TYPE").AsString());
			}
			if (!cmd.Field("STATUS").IsNull())
			{
				craneEvadeBase.setStatus(cmd.Field("STATUS").AsString());
			}
			//2018.11.30 zhangyuhong add
			//新增：避让指令优先级获取
			if (!cmd.Field("PRIORITY").IsNull())
			{
				craneEvadeBase.setPriority(cmd.Field("PRIORITY").AsDouble());
			}
			craneEvadeBase.logOutValues();
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


//2018.11.30 zhangyuhong add
//新增：避让指令优先级数据  更新到数据库表
bool  Adapter_UACS_CRANE_EVADE_REQUEST::Update(CraneEvadeRequestBase craneEvadeBase)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_EVADE_REQUEST::Update()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		log.Debug()<<" craneNO = "<<craneEvadeBase.getTargetCraneNO() << " try to get UacsCraneEvadeRequestBase "<<endl;

		if ( craneEvadeBase.getTargetCraneNO() == DB_STR_NULL)
		{
			log.Debug()<<" craneNO is fault , return false "<<endl;
			return ret;
		}

		string	strSql=" UPDATE UACS_CRANE_EVADE_REQUEST SET ";
					strSql=strSql+" SENDER =:p_SENDER , ";
					strSql=strSql+" ORIGINAL_SENDER =:p_ORIGINAL_SENDER , ";
					strSql=strSql+" EVADE_X_REQUEST =:p_EVADE_X_REQUEST , ";
					strSql=strSql+" EVADE_X =:p_EVADE_X , ";
					strSql=strSql+" EVADE_DIRECTION =:p_EVADE_DIRECTION , ";
					strSql=strSql+" EVADE_ACTION_TYPE =:p_EVADE_ACTION_TYPE , ";
					strSql=strSql+" STATUS =:p_STATUS,  ";
					strSql=strSql+" PRIORITY =:p_PRIORITY ";			//2018.11.30 zhangyuhong add 
					strSql=strSql+" WHERE ";
					strSql=strSql+" TARGET_CRANE_NO =:p_TARGET_CRANE_NO " ;

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_TARGET_CRANE_NO") = craneEvadeBase.getTargetCraneNO();
		cmd.Param("p_SENDER") = craneEvadeBase.getSender();
		cmd.Param("p_ORIGINAL_SENDER") = craneEvadeBase.getOriginalSender();
		cmd.Param("p_EVADE_X_REQUEST") = craneEvadeBase.getEvadeXRequest();
		cmd.Param("p_EVADE_X") = craneEvadeBase.getEvadeX();
		cmd.Param("p_EVADE_DIRECTION") = craneEvadeBase.getEvadeDirection();
		cmd.Param("p_EVADE_ACTION_TYPE") = craneEvadeBase.getEvadeActionType();
		cmd.Param("p_STATUS") = craneEvadeBase.getStatus();
		cmd.Param("p_PRIORITY") = craneEvadeBase.getPriority();

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret = true;

	

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



bool  Adapter_UACS_CRANE_EVADE_REQUEST::UpdateStatus(string craneNO ,string status)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_EVADE_REQUEST::UpdateStatus()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		log.Debug()<<" craneNO = "<<craneNO << " try to get UacsCraneEvadeRequestBase "<<endl;

		if ( craneNO == DB_STR_NULL)
		{
			log.Debug()<<" craneNO is fault , return false "<<endl;
			return ret;
		}

		string	strSql=" UPDATE UACS_CRANE_EVADE_REQUEST SET ";
		strSql=strSql+  " STATUS =:p_STATUS  ";
		strSql=strSql+  " WHERE ";
		strSql=strSql+  " TARGET_CRANE_NO =:p_TARGET_CRANE_NO " ;

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_TARGET_CRANE_NO") = craneNO;

		cmd.Param("p_STATUS") = status;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret = true;



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



bool  Adapter_UACS_CRANE_EVADE_REQUEST::UpdateActionType(string craneNO ,string actionType)
{

	bool ret=false;
	string functionName="Adapter_UACS_CRANE_EVADE_REQUEST::UpdateActionType()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{



		if ( craneNO == DB_STR_NULL)
		{
			log.Debug()<<" craneNO is fault , return false "<<endl;
			return ret;
		}

		string	strSql=" UPDATE UACS_CRANE_EVADE_REQUEST SET ";
		strSql=strSql+  " EVADE_ACTION_TYPE =:p_EVADE_ACTION_TYPE  ";
		strSql=strSql+  " WHERE ";
		strSql=strSql+  " TARGET_CRANE_NO =:p_TARGET_CRANE_NO " ;

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_TARGET_CRANE_NO") = craneNO;

		cmd.Param("p_EVADE_ACTION_TYPE") = actionType;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret = true;



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


bool  Adapter_UACS_CRANE_EVADE_REQUEST::Init(string craneNO)
{


	bool ret=false;
	string functionName="Adapter_UACS_CRANE_EVADE_REQUEST::Init()";
	LOG log(functionName, AUTO_CATCH_PID);

	try
	{

		log.Debug()<<" craneNO = "<<craneNO << " try to get UacsCraneEvadeRequestBase "<<endl;

		if ( craneNO == DB_STR_NULL)
		{
			log.Debug()<<" craneNO is fault , return false "<<endl;
			return ret;
		}

		string	strSql=" UPDATE UACS_CRANE_EVADE_REQUEST SET ";
					strSql=strSql+" SENDER =NULL , ";
					strSql=strSql+" ORIGINAL_SENDER =NULL , ";
					strSql=strSql+" EVADE_X_REQUEST =NULL , ";
					strSql=strSql+" EVADE_X =NULL , ";
					strSql=strSql+" EVADE_DIRECTION =NULL , ";
					strSql=strSql+" EVADE_ACTION_TYPE =NULL , ";
					strSql=strSql+" STATUS =:p_STATUS,  ";
					strSql=strSql+" PRIORITY =NULL  ";
					strSql=strSql+" WHERE ";
					strSql=strSql+" TARGET_CRANE_NO =:p_TARGET_CRANE_NO " ;

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, strSql);    // command object

		cmd.Param("p_TARGET_CRANE_NO") = craneNO;

	
		cmd.Param("p_STATUS") = CraneEvadeRequestBase::STATUS_EMPTY;

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();

		ret = true;

	

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
