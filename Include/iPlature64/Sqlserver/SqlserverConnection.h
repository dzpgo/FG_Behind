/*********************************************************************
 *		
 *  ��      ��:    SqlserverConnection.h   		
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������
 *
 *  �汾��ʷ		
 *      1.0    2009-08-12    linchangbo    ����
 *     
*********************************************************************/
#pragma once
#include <Sqlserver/Sqlserver.h>
//#include <Sqlserver/SqlserverResultSet.h>
//#include <Sqlserver/SqlserverStatement.h>
#include <string>
#include <vector>

namespace Sqlserver
{
	class SqlserverResultSet;
	class SqlserverStatement;
	class SqlserverConnection
	{
	private:
		std::string _longin;
		std::string _password;
		std::string _servicename;
		_ConnectionPtr m_pConnection;
		std::vector<SqlserverResultSet*> resultsets;
		std::vector<SqlserverStatement*> statements;
	public:
		SqlserverConnection();
		SqlserverConnection(const std::string& login,const std::string& password,const std::string& service_name);
		~SqlserverConnection(void);
		/**********************************************************************
		*  ����: �����ݿ�����
		*  �������� open
		*  ����ֵ�� SqlserverParameter&		��������
		*  �����б�	��������    					ȡֵ��Χ     	����
		*  login  :  [IN] const std::string&	     				    ��½��
		*  password:  [IN] const std::string&	     				    ����
		*  service_name:  [IN] const std::string&	     				��������\\���ݿ�ʵ����/���ݿ���������WINSERVER1\\SQLEXPRESS/iPlature��
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		void open (const std::string& login,const std::string& password,const std::string& service_name);
		/**********************************************************************
		*  ����: �ر����ݿ�����
		*  �������� close
		*  ����ֵ�� void
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		void close();
		/**********************************************************************
		*  ����: ���´����ݿ�����
		*  �������� reopen
		*  ����ֵ�� void
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		void reopen();
		/**********************************************************************
		*  ����: ִ��SQL���
		*  �������� execute
		*  ����ֵ�� int		ִ��SQL�������Ӱ��ļ�¼��
		*  �����б�	��������    					ȡֵ��Χ     	����
		*  sql_block  :  [IN] const std::string&	     				SQL���
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		int execute(const std::string& sql_block);
		/**********************************************************************
		*  ����: ׼��SQL���
		*  �������� prepare
		*  ����ֵ�� SqlserverStatement*		׼��SQL��䲢���SqlserverStatement����
		*  �����б�	��������    					ȡֵ��Χ     	����
		*  sql_block  :  [IN] const std::string&	     				SQL���
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		SqlserverStatement* prepare(const std::string& sql_block);
		/**********************************************************************
		*  ����: ׼��SQL���
		*  �������� select
		*  ����ֵ�� SqlserverResultSet*		׼��SQL��䲢���SqlserverResultSet����
		*  �����б�	��������    					ȡֵ��Χ     	����
		*  sql_block  :  [IN] const std::string&	     				SQL���
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		SqlserverResultSet* select(const std::string& sql_block);
		/**********************************************************************
		*  ����: ��ʼ����
		*  �������� beginTrans
		*  ����ֵ�� void
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		void beginTrans();
		/**********************************************************************
		*  ����: �ύ����
		*  �������� commit
		*  ����ֵ�� void
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		void commit();
		/**********************************************************************
		*  ����: �ع�����
		*  �������� rollback
		*  ����ֵ�� void
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		void rollback();
		/**********************************************************************
		*  ����: �ͷ���Դ
		*  �������� release
		*  ����ֵ�� void
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		void release();
	};
}