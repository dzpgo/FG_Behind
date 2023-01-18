



#pragma once 

#include "Evade_Tag_Define.h"


using namespace Monitor;



Evade_Tag_Define:: Evade_Tag_Define()
{

}

Evade_Tag_Define:: ~Evade_Tag_Define()
{

}




string Evade_Tag_Define ::getTagName_Evade_Request(string craneNO)
{


	string functionName = "Evade_Tag_Define :: getTagName_Evade_Request()";
	//LOG log(functionName, AUTO_CATCH_PID);

	string tagName=DB_STR_NULL;
	LOG log(functionName);

	try
	{
	
			log.Debug()<<"根据craneNO获取避让请求发送tag点名称, craneNO="<<craneNO<<endl;

			if(craneNO=="4_4" || craneNO == "4_5" || craneNO == "4_6" || craneNO == "4_7")
			{
				tagName="C2A_1_EVADE_REQUEST";
			}

			log.Debug()<<"tagName="<<tagName<<endl;

		return tagName;
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

	return tagName;

}







string Evade_Tag_Define ::getTagName_Evade_Cancel(string craneNO)
{


	string functionName = "Evade_Tag_Define :: getTagName_Evade_Cancel()";
	//LOG log(functionName, AUTO_CATCH_PID);

	string tagName=DB_STR_NULL;
	LOG log(functionName);

	try
	{
	
			log.Debug()<<"根据craneNO获取避让请求取消tag点名称, craneNO="<<craneNO<<endl;		

			if(craneNO=="4_4" || craneNO == "4_5" || craneNO == "4_6" || craneNO == "4_7")
			{
				tagName="C2A_1_EVADE_CANCEL";
			}

			log.Debug()<<"tagName="<<tagName<<endl;

		return tagName;
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

	return tagName;

}


