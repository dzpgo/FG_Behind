/*********************************************************************
 *		
 *  ��      ��:    Connection.h
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ������ͨ�����ݿ�ӿ�Connection�࣬�������ݿ�����
 *
 *  �汾��ʷ		
 *      1.0    2009-12-08    lumengyi    ����
 *      1.0		2010-05-24	 haykin		reload operator Connect
 *		1.0		2010-07-12	 hyakin		add operator ReConnect
*********************************************************************/
#pragma once
#include <iDA/iDADef.h>
namespace iPlature
{
	namespace iDA
	{
		class ConnectionImpl;

		class Connection
		{
			friend class Command;
		public:
			Connection();
			~Connection();

			void Connect(const std::string& sDBString,
						const std::string& sUserName,
						const std::string& sPassword,
						iDA_Client_t eClient = iDA_Client_NotSpecified);

			/**********************************************************************
			 *  ����: �������ݿ�
			 *  �������� Connect 
			 *  ����ֵ�� void	 	
			 *  �����б�	��������    					ȡֵ��Χ     		    ����
			 *    sDBString  :    [IN/OUT] const std::string &	     ���ݿ���
			 *    sUserName  :    [IN/OUT] const std::string &	     �û���
			 *    sPassword  :    [IN/OUT] const std::string &	     ����
			 *    sClient  :    [IN/OUT] const std::string &	     �ַ��������ݿ����� oracle/db2/sqlserver/sqlite
			 *
			 *  �汾��ʷ		
			 *       1.0    2010-05-24  Haykin-2010    create
			 *  
			 **********************************************************************/
			void Connect(const std::string& sDBString,
						const std::string& sUserName,
						const std::string& sPassword,
						const std::string& sClient );

			/**********************************************************************
			 *  ����: �������ݿ�
			 *  �������� Connect 
			 *  ����ֵ�� void	 	
			 *  �����б�	��������    					ȡֵ��Χ     		    ����
			 *    sConnectString  :    [IN/OUT] const std::string &	     ���ݿ����������� user/password@dbname
			 *    sClient  :    [IN/OUT] const std::string &			 �ַ��������ݿ����� oracle/db2/sqlserver/sqlite
			 *
			 *  �汾��ʷ		
			 *       1.0    2010-05-24  Haykin-2010    create
			 *  
			 **********************************************************************/
			void Connect(const std::string& sConnectString
					   , const std::string& sClient = "");

			bool IsConnected() const;
			bool IsAlive() const;
			void Disconnect();
			void Rollback();
			void Commit();
			void SetAutoCommit(iDA_AutoCommit_t eAutoCommit);
			iDA_AutoCommit_t AutoCommit() const;

			/**********************************************************************
			 *  ����: �����������ݿ�
			 *  �������� ReConnect 
			 *  ����ֵ�� void	 	
			 *  �����б�	��������    					ȡֵ��Χ     		    ����
			 *
			 *  �汾��ʷ		
			 *       1.0    2010-07-12  Haykin-2010    create
			 *  
			 **********************************************************************/
			void ReConnect();

			/**********************************************************************
			 *  ����: //TODO:����Ӻ�������
			 *  �������� Client 
			 *  ����ֵ�� iPlature::iDA::iDA_Client_t	 	���ݿ�����ö�ٶ���
			 *  �����б�	��������    					ȡֵ��Χ     		    ����
			 *    strClient  :    [IN/OUT] const std::string &				�ַ��������ݿ����� oracle/db2/sqlserver/sqlite
			 *
			 *  �汾��ʷ		
			 *       1.0    2010-05-24  Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
			 *  
			 **********************************************************************/
			static iDA_Client_t Client(const std::string& strClient);

			//Gets the current DBMS client assigned for the connection.
			iDA_Client_t Client() const;
		private:
			ConnectionImpl* _impl;
		};
	}//namespace iDA
}//namespace iPlature
