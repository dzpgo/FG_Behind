/*********************************************************************
*		
*  文      件:    DataAccess.h   		//TODO请概述文件功能
*
*  版权所有:   Shanghai Baosight Software Co., Ltd.
*
*  概述：数据库基类
*        ：完成数据库的连接
*
*  版本历史		
*      1.0    2010-06-03    fzz    根据软件设计书添加文件
*	   1.1    2013-03-28    sxd    修改
*      1.2    2013-04-15    zyh    修改
*      %USER%   
*********************************************************************/
#include "DataAccess.h"
#include <pace/pace.h>
#include <log4cplus/LOG.h>


using namespace Monitor;


CDataAccess*  CDataAccess::m_pDBInstance = NULL;

/**********************************************************************
*  概述: 构造函数
*  函数名： CDataAccess 
*  返回值： 	 	无
*  参数列表：	参数类型    					取值范围     		    描述
*
*  版本历史		
*       1.0    2010-06-03  fzz    添加函数
*  
**********************************************************************/
CDataAccess::CDataAccess(void)
{

}
/**********************************************************************
*  概述: 析构函数
*  函数名： ~CDataAccess 
*  返回值： 	 	无
*  参数列表：	参数类型    					取值范围     		    描述
*
*  版本历史		
*       1.0    2010-06-03  fzz    添加函数
*  
**********************************************************************/
CDataAccess::~CDataAccess(void)
{
	//
}
/**********************************************************************
*  概述: 初始化数据库信息，连接数据库
*  函数名： Initialize 
*  返回值： void	 	
*  参数列表：	参数类型    					取值范围     		    描述
*
*  版本历史		
*       1.0    2010-05-29  fzz    添加函数
*  
**********************************************************************/
void CDataAccess::Initialize(void)
{
	LOG log("CDataAccess::Initialize");

	//读取配置---需要配置文件在平台的config目录下面
	GetConnectionString();


	//根据配置进行数据库连接
	try
	{

		log.Info()<<"m_strDBStatus!"<<m_strDBStatus<<endl;
		if (m_strDBStatus == "iDA_Oracle_Client")
		{
			m_DBCon.Connect(m_strDatabase, m_strUsername, m_strPassword, iDA::iDA_Oracle_Client);//打开数据库连接,ORCLE
		}
		else if (m_strDBStatus == "iDA_DB2_Client")
		{
			m_DBCon.Connect(m_strDatabase, m_strUsername, m_strPassword, iDA::iDA_DB2_Client);//打开数据库连接,DB2
			log.Info()<<"m_strDatabase="<<m_strDatabase<<"   m_strUsername="<<m_strUsername<<"  m_strPassword="<<m_strPassword<<endl;
		}
		else
		{
			log.Error()<<"Database Type Configure Error!"<<endl;
		}

		log.Info()<<"DataBase Connected Success"<<endl;
	}
	catch (iDA::Exception &x)
	{
		try
		{
			m_DBCon.Rollback();
		}
		catch (iDA::Exception &)
		{

		}
		log.Error()<<"DataBase Connected Failed "<<x.ErrMsg().c_str()<<endl;
	}


}
/**********************************************************************
*  概述: 释放初始化信息,关闭数据库连接
*  函数名： UnInitialize 
*  返回值： int	 	成功：0  失败：1
*  参数列表：	参数类型    					取值范围     		    描述
*
*  版本历史		
*       1.0    2010-06-03  fzz    添加函数
*  
**********************************************************************/
void CDataAccess::UnInitialize(void)
{
	LOG log("CDataAccess::UnInitialize");
	try
	{
		m_DBCon.Disconnect();//关闭数据库连接

		log.Info()<<"DataBase Close Success"<<endl;
	}
	catch (iDA::Exception &x)
	{
		try
		{
			m_DBCon.Rollback();
		}
		catch (iDA::Exception &)
		{

		}
		log.Error()<<"DataBase Close Failed "<<x.ErrMsg().c_str()<<endl;

	}

}
/**********************************************************************
*  概述: 获取数据库连接字符串
*  函数名： GetConnectionString 
*  返回值： int	 	成功：0  失败：1
*  参数列表：	参数类型    					取值范围     		    描述
*
*  版本历史		
*       1.0    2010-06-03  fzz    添加函数
*  
**********************************************************************/
void CDataAccess::GetConnectionString(void)
{
	LOG log("CDataAccess::GetConnectionString");

	vector<string> arrayConnectionString;								//保存数据库链接字符串序列
	try
	{
		Parameter param("PTModule.config");				//读取配置文件

		arrayConnectionString = param.getStringSeq("DBAccess.ConnectionString");//从配置文件中获取数据库链接字符串序列

		if(arrayConnectionString.size() != 4)							//数据库链接字段不为四个报错
		{
			log.Error()<<"Connection property number error!"<<endl;
		}
		else															//成功从配置文件中获取数据库链接字符串序列
		{
			m_strUsername = arrayConnectionString[0];					//数据库用户名	
			m_strPassword = arrayConnectionString[1];					//数据库密码	
			m_strDatabase = arrayConnectionString[2];					//数据库SID	
			m_strDBStatus = arrayConnectionString[3];					//数据库类型


			//m_strDBStatus = arrayConnectionString[0];					//数据库类型
			//m_strDatabase = arrayConnectionString[1];					//数据库SID	
			//m_strUsername = arrayConnectionString[2];					//数据库用户名	
			//m_strPassword = arrayConnectionString[3];					//数据库密码	

		}			
	}
	catch(const Ice::FileException& e)									//捕获Ice异常
	{
		//log.Error()<<e.ice_id();
	}
	catch(...)															//捕获未知异常
	{
		log.Error()<<"UnknowException"<<endl;
	}

}

CDataAccess* CDataAccess::GetInstance(void)
{
	if (m_pDBInstance == NULL)
	{
		m_pDBInstance = new CDataAccess;
	}

	return m_pDBInstance;
}


bool CDataAccess::isDBTimeNULL(iPlature::iDA::DateTime theValue)
{
	bool isDBNULL=false;
	if(theValue.GetYear()==DB_TIME_NULL.GetYear()   &&  theValue.GetDay()==DB_TIME_NULL.GetDay()  &&
		theValue.GetHour()==DB_TIME_NULL.GetHour() && theValue.GetMinute()==DB_TIME_NULL.GetMinute() && theValue.GetSecond()==DB_TIME_NULL.GetSecond())
	{
		isDBNULL=true;
	}

	return isDBNULL;
}