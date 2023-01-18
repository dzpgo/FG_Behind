/*********************************************************************
*		
*  ��      ��:    DataAccess.h   		//TODO������ļ�����
*
*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
*
*  ���������ݿ����
*        ��������ݿ������
*
*  �汾��ʷ		
*      1.0    2010-06-03    fzz    ����������������ļ�
*	   1.1    2013-03-28    sxd    �޸�
*      1.2    2013-04-15    zyh    �޸�
*      %USER%   
*********************************************************************/
#include "DataAccess.h"
#include <pace/pace.h>
#include <log4cplus/LOG.h>


using namespace Monitor;


CDataAccess*  CDataAccess::m_pDBInstance = NULL;

/**********************************************************************
*  ����: ���캯��
*  �������� CDataAccess 
*  ����ֵ�� 	 	��
*  �����б�	��������    					ȡֵ��Χ     		    ����
*
*  �汾��ʷ		
*       1.0    2010-06-03  fzz    ��Ӻ���
*  
**********************************************************************/
CDataAccess::CDataAccess(void)
{

}
/**********************************************************************
*  ����: ��������
*  �������� ~CDataAccess 
*  ����ֵ�� 	 	��
*  �����б�	��������    					ȡֵ��Χ     		    ����
*
*  �汾��ʷ		
*       1.0    2010-06-03  fzz    ��Ӻ���
*  
**********************************************************************/
CDataAccess::~CDataAccess(void)
{
	//
}
/**********************************************************************
*  ����: ��ʼ�����ݿ���Ϣ���������ݿ�
*  �������� Initialize 
*  ����ֵ�� void	 	
*  �����б�	��������    					ȡֵ��Χ     		    ����
*
*  �汾��ʷ		
*       1.0    2010-05-29  fzz    ��Ӻ���
*  
**********************************************************************/
void CDataAccess::Initialize(void)
{
	LOG log("CDataAccess::Initialize");

	//��ȡ����---��Ҫ�����ļ���ƽ̨��configĿ¼����
	GetConnectionString();


	//�������ý������ݿ�����
	try
	{

		log.Info()<<"m_strDBStatus!"<<m_strDBStatus<<endl;
		if (m_strDBStatus == "iDA_Oracle_Client")
		{
			m_DBCon.Connect(m_strDatabase, m_strUsername, m_strPassword, iDA::iDA_Oracle_Client);//�����ݿ�����,ORCLE
		}
		else if (m_strDBStatus == "iDA_DB2_Client")
		{
			m_DBCon.Connect(m_strDatabase, m_strUsername, m_strPassword, iDA::iDA_DB2_Client);//�����ݿ�����,DB2
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
*  ����: �ͷų�ʼ����Ϣ,�ر����ݿ�����
*  �������� UnInitialize 
*  ����ֵ�� int	 	�ɹ���0  ʧ�ܣ�1
*  �����б�	��������    					ȡֵ��Χ     		    ����
*
*  �汾��ʷ		
*       1.0    2010-06-03  fzz    ��Ӻ���
*  
**********************************************************************/
void CDataAccess::UnInitialize(void)
{
	LOG log("CDataAccess::UnInitialize");
	try
	{
		m_DBCon.Disconnect();//�ر����ݿ�����

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
*  ����: ��ȡ���ݿ������ַ���
*  �������� GetConnectionString 
*  ����ֵ�� int	 	�ɹ���0  ʧ�ܣ�1
*  �����б�	��������    					ȡֵ��Χ     		    ����
*
*  �汾��ʷ		
*       1.0    2010-06-03  fzz    ��Ӻ���
*  
**********************************************************************/
void CDataAccess::GetConnectionString(void)
{
	LOG log("CDataAccess::GetConnectionString");

	vector<string> arrayConnectionString;								//�������ݿ������ַ�������
	try
	{
		Parameter param("PTModule.config");				//��ȡ�����ļ�

		arrayConnectionString = param.getStringSeq("DBAccess.ConnectionString");//�������ļ��л�ȡ���ݿ������ַ�������

		if(arrayConnectionString.size() != 4)							//���ݿ������ֶβ�Ϊ�ĸ�����
		{
			log.Error()<<"Connection property number error!"<<endl;
		}
		else															//�ɹ��������ļ��л�ȡ���ݿ������ַ�������
		{
			m_strUsername = arrayConnectionString[0];					//���ݿ��û���	
			m_strPassword = arrayConnectionString[1];					//���ݿ�����	
			m_strDatabase = arrayConnectionString[2];					//���ݿ�SID	
			m_strDBStatus = arrayConnectionString[3];					//���ݿ�����


			//m_strDBStatus = arrayConnectionString[0];					//���ݿ�����
			//m_strDatabase = arrayConnectionString[1];					//���ݿ�SID	
			//m_strUsername = arrayConnectionString[2];					//���ݿ��û���	
			//m_strPassword = arrayConnectionString[3];					//���ݿ�����	

		}			
	}
	catch(const Ice::FileException& e)									//����Ice�쳣
	{
		//log.Error()<<e.ice_id();
	}
	catch(...)															//����δ֪�쳣
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