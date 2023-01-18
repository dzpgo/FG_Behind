#pragma once
#include <iostream>
#include <pace/pace.h>
#include <iDA/iDA.h>
#include <iDA/ConnectionPool.h>
#include <log4cplus/LOG.h>
#include <Slice/CltsException.h>
#include <Msg/MsgSetting.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** �׳��쳣��Ϣ.
		 *  �������� throwCltsEx 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    file    : const string&                               �쳣���ļ���
		 *    line    : int                                         �쳣���к�
		 *    function: string                               		�쳣�ĺ�����
		 *    type      : string&                             		�쳣����
		 *    format : const char*                                  �쳣��ʽ�ַ���
		 */
		void throwCltsEx(string file, int line, string function, string type, const char* format, ...);
		
		/** �׳��쳣��Ϣ.
		 *  �������� throwCltsEx 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    file    : const string&                               �쳣���ļ���
		 *    line    : int                                         �쳣���к�
		 *    current : const Ice::Current&                         ��������������
		 *    type      : string&                             		�쳣����
		 *    format : const char*                                  �쳣��ʽ�ַ���
		 */
		void throwCltsEx(string file, int line, const Ice::Current& current, string type, const char* format, ...);

		/** �����쳣��Ϣ.
		 *  �������� catchFunc 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    file    : const string&                               �����쳣���ļ���
		 *    line    : int                                         �����쳣���к�
		 *    ex      : std::exception&                             �쳣��Ϣ
		 *    bThrowEx : bool                                       ������Ƿ��ٴ��׳��쳣
		 */
		void catchFunc( LOG& log, const string& file, int line, const string& function, std::exception& ex, bool bThrowEx = true);

		/** �����쳣��Ϣ.
		 *  �������� catchFunc 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    file    : const string&                               �����쳣���ļ���
		 *    line    : int                                         �����쳣���к�
		 *    function : const string&                              �����쳣�ĺ���
		 *    ex      : std::exception&                             �쳣��Ϣ
		 *    bThrowEx : bool                                       ������Ƿ��ٴ��׳��쳣
		 */
		void catchFunc( LOG& log, const string& file, int line, const string& function, const IceUtil::Time& timeStart, std::exception& ex, bool bThrowEx = true);

		/** �����쳣��Ϣ.
		 *  �������� catchFunc 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&                                        ��־ʵ��
		 *    file    : const string&                               �����쳣���ļ���
		 *    line    : int                                         �����쳣���к�
		 *    function : const string&                              �����쳣�ĺ���
		 *    timeStart : const IceUtil::Time&                      �����õ���ʼʱ��
		 *    current : const Ice::Current&                         ��������������
		 *    ex      : std::exception&                             �쳣��Ϣ
		 *    bThrowEx : bool                                       ������Ƿ��ٴ��׳��쳣
		 */
		void catchFunc( LOG& log, const string& file, int line, const string& function, const IceUtil::Time& timeStart, const Ice::Current& current, std::exception& ex, bool bThrowEx = true);
	}
}
