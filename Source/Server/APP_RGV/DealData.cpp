//********************************************************************
//** Copyright (c) 2016 宝信软件
//** 创建日期：2016-12-30
//** 修改人：
//** 修改日期：
//** 整理日期：
//********************************************************************

#include "DealData.h"
#include "DataAccess.h"

using namespace Monitor;


string DealData::DumpValue(SmartData& sd,const string& ident)
{
	string strResult = "";
	for (int i=0; i < sd.size(); i++)
	{
		string itemVal = "";
		if (sd[i].type() == SmartData::COMPOSITE)
		{
			itemVal.append(DumpValue(sd[i],ident));
		} 
		else
		{
			string strVal = "";
			if (!sd[i].IsNull())
			{
				strVal = sd[i].toString();
			}
			itemVal.append(strVal);
		}
		if (i != (sd.size()-1))
		{
			itemVal.append(ident);
		}
		strResult.append(itemVal);
	}
	return strResult;
}

void DealData::InsertSendData(std::string msgId,std::string dataStr,ByteSeq data,int id)
{
	LOG log("L3MsgSnd");
	try
	{
		string sql = "INSERT INTO UACS_L3MSG_SEND (ID,MSGID,DATA,DATASTR,REC_TIME,FLAG) VALUES (:p_ID,:p_MSGID,:p_DATA,:p_DATASTR,:p_REC_TIME,'0')";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, sql);    // command object
		cmd.Param("p_ID") = (long)id;
		cmd.Param("p_MSGID") = msgId;		
		cmd.Param("p_DATA").SetBlobData((unsigned char*)&data[0],data.size());
		cmd.Param("p_DATASTR")= dataStr;	
		cmd.Param("p_REC_TIME") = iDA::DateTime::Now(); 

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();
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

		log.Debug()<<__FUNCTION__<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
}

int DealData::GetMaxId()
{
	LOG log("L3MsgSnd");
	int ID = 0;
	try
	{
		string sql = "SELECT MAX(ID) AS ID FROM UACS_L3MSG_SEND";
		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, sql);    // command object
		cmd.Execute();
		if (cmd.FetchNext())
		{
			if(!cmd.Field("ID").IsNull())
			{
				ID = (int)cmd.Field("ID").AsLong();
			}
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
		log.Debug()<<__FUNCTION__<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
	return ID;
}

void DealData::UpdateSendDataFlag(int id)
{
	LOG log("L3MsgSnd");
	try
	{
		string sql = "UPDATE UACS_L3MSG_SEND SET FLAG = 1, SEND_TIME = :p_SEND_TIME WHERE ID = :p_ID";

		iDA::Command cmd(&CDataAccess::GetInstance()->m_DBCon, sql);    // command object
		cmd.Param("p_ID") = (long)id;
		cmd.Param("p_SEND_TIME") = iDA::DateTime::Now(); 

		cmd.Execute();

		CDataAccess::GetInstance()->m_DBCon.Commit();
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

		log.Debug()<<__FUNCTION__<<"   error:"<<x.ErrMsg()<<endl;
	}
	catch (std::exception& stdex)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<stdex.what()<<endl;
	}
	catch (...)
	{
		log.Debug()<<__FUNCTION__<<"   error:"<<endl;
	}
}

