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
*      1.1    2013-03-28    sxd    �޸�
*      %USER%   
*********************************************************************/
#pragma once
#ifndef _DATAACCESS_H_
#define _DATAACCESS_H_

#include <iDA/iDA.h>
#include <string>
#include <vector>

#include "PreDefine.h"

using namespace std;
//#include "DBDefine.h"
using namespace iPlature;

namespace Monitor
{

		 const char SPLIT_VERTICALLINE[] = "|";
		 const char SPLIT_COMMA[] = ",";

	    static const string DB_STR_NULL = "999999";
	    static const long DB_INT_NULL =999999;
		static const iDA::DateTime  DB_TIME_NULL(1970,01,01,00,00,00);

		static const string DF_STR_NULL = "";
		static const long DF_INT_NULL = -1;

/*********************************************************************
		*  ��      ��:   	CDataAccess
		*  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
		*  �� ְ �����ݿ����
		*              ��������ݿ������
		*  �汾��ʷ		
		*       1.0    2010-06-03    fzz    �����������������
		*     
		*********************************************************************/
		class CDataAccess
		{
		public:
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
			~CDataAccess(void);

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
			void Initialize(void);

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
			void UnInitialize(void);

			static CDataAccess* GetInstance(void);

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
			void GetConnectionString(void);

		private:
			CDataAccess(void);

		public:
			iDA::Connection m_DBCon;

		private:
			static CDataAccess*	m_pDBInstance;
			string m_strUsername;					//���ݿ��û���			
			string m_strPassword;					//���ݿ�����			
			string m_strDatabase;					//���ݿ�SID
			string m_strDBStatus;					//���ݿ�����

		public:
			static bool isDBTimeNULL(iPlature::iDA::DateTime theValue);
		};

}
#endif