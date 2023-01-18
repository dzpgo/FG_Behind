#pragma once
#include <iostream>
#include <pace/pace.h>
#include <iDA/iDA.h>
#include <iDA/ConnectionPool.h>
#include <log4cplus/LOG.h>
#include <Slice/CltsException.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** ���ݿ�����.
		 *  �������� dbConn 
		 *  ����ֵ�� int					iDA��������ֵ
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    con     : iDA::Connection&                            iDA���ݿ�����
		 *    strCfgfile : string                            		�����ַ��������ļ�
		 */		
		int dbConn(iDA::Connection & con, string strCfgfile);

		/** SQL����.
		 *  �������� dbExecute 
		 *  ����ֵ�� int					iDA��������ֵ
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    command    : iDA::Command&                            iDA���ݿ�����
		 *    file : string                            				�����ַ��������ļ�
		 *    line : int                            				�����ַ��������ļ�
		 */				
		int dbExecute(LOG& log, iDA::Command& command, string file, int line);

		/** �����ύ.
		 *  �������� dbCommit 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    pCon    : iDA::Connection*                            ���ݿ�����ָ��
		 */
		void dbCommit(LOG& log, iDA::Connection* pCon);

		/** �����ع�.
		 *  �������� dbCommit 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    pCon    : iDA::Connection*                            ���ݿ�����ָ��
		 */
		void dbRollback(LOG& log, iDA::Connection* pCon);

		/** ��������ʼ(������������Ϣ).
		 *  �������� transactionBegin 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log : LOG                                             ��־����
		 *    current : const Ice::Current&                         ��������������
		 *    strFunc : const string&								����������
		 */
		void transactionBegin(LOG& log, Ice::Current& current, const string& strFunc);

		/** �����ύ(������������Ϣ�ύ).
		 *  �������� transactionCommit 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    timeStart :  IceUtil::Time                            ���ÿ�ʼʱ��
		 *    pCon    : iDA::Connection*                            ���ݿ�����ָ��
		 *    caller  : const Ice::Current&		                    ������������Ϣ
		 *    function : const string&                              ��ǰ���ú���
		 */
		void transactionCommit(LOG& log, IceUtil::Time timeStart, iDA::Connection* pCon, const Ice::Current& caller, const string& function);

		/** ����ع�(������������Ϣ�ع�).
		 *  �������� transactionRollback 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    timeStart :  IceUtil::Time                            ���ÿ�ʼʱ��
		 *    pCon    : iDA::Connection*                            ���ݿ�����ָ��
		 *    caller  : const Ice::Current&		                    ������������Ϣ
		 *    function : const string&                              ��ǰ���ú���
		 */
		void transactionRollback(LOG& log, iDA::Connection* pCon, const Ice::Current& caller, const string& function);
	}
}
