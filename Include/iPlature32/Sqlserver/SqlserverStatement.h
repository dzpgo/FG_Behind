/*********************************************************************
 *		
 *  ��      ��:    SqlserverStatement.h   		
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
#include <string>
#include <map>
#include <vector>

namespace Sqlserver
{
	class SqlserverParameter;
	class SqlserverResultSet;
	class SqlserverStatement
	{
	private:
		_CommandPtr m_pCommand;
		std::vector<SqlserverParameter*> m_Parameters;
		std::vector<SqlserverResultSet*> resultsets;
	public:
		SqlserverStatement();
		~SqlserverStatement();
		inline _CommandPtr& getCommand(){return m_pCommand;};
		/**********************************************************************
		 *  ����: ������
		 *  �������� bind 
		 *  ����ֵ�� SqlserverParameter&
		 *  �����б�	��������    					ȡֵ��Χ     	����
		 *    name  :  [IN] const char*	     						�󶨵Ĳ�����
		 *    type  :  [IN] DataTypesEnum	     					�󶨵Ĳ�������
		 *
		 *  �汾��ʷ		
		 *       1.0    2009-09-07  lumengyi    ���ע��
		 *  
		 **********************************************************************/
		SqlserverParameter &bind (const char *name,DataTypesEnum type = DT_UNKNOWN);
		/**********************************************************************
		*  ����: ִ��SQL���
		*  �������� execute 
		*  ����ֵ�� int		ִ��SQL�������Ӱ��ļ�¼��
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		int execute ();
		/**********************************************************************
		*  ����: ��ѯSQL���
		*  �������� select 
		*  ����ֵ�� SqlserverResultSet*		��ѯSQL����õ��Ľ����
		*  �����б�	��������    					ȡֵ��Χ     	����
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		SqlserverResultSet* select ();
		/**********************************************************************
		*  ����: �������ֻ�ò�������
		*  �������� operator [] 
		*  ����ֵ�� SqlserverParameter&		��������
		*  �����б�	��������    					ȡֵ��Χ     	����
		*    name  :  [IN] const char*	     							������
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		SqlserverParameter& operator [] (const char *name);
		/**********************************************************************
		*  ����: ���������Ż�ò�������
		*  �������� operator [] 
		*  ����ֵ�� SqlserverParameter&		��������
		*  �����б�	��������    					ȡֵ��Χ     	����
		*  parameter_index  :  [IN] unsigned int	     				������
		*
		*  �汾��ʷ		
		*       1.0    2009-09-07  lumengyi    ���ע��
		*  
		**********************************************************************/
		SqlserverParameter& operator [] (unsigned int parameter_index);
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
		inline void release (void) {/*m_pCommand.Release();*/}
	};
}