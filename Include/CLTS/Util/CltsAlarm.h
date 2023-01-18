#pragma once
#include <iostream>
#include <Ice/Ice.h>
#include <iDA/iDA.h>
#include <pace/pace.h>
#include <Slice/CltsException.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		struct AlarmMsg
		{
			string strTitle;
			string strMsg;
			string strDetail;
		};

		/** ��ȡ���ö˵��¼���.
		 *  �������� getEventID 
		 *  ����ֵ�� bool                  ��ȡ���
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    current : const Ice::Context&                         �������������ݣ���������Ϣ��
		 *    nEventID : int&										�¼����
		 */
		bool getEventID(const Ice::Current& current, int& nEventID);

		/** �趨���õ��¼���.
		 *  �������� setEventID 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    current : Ice::Context&								��������������
		 *    nEventID : int&										�¼����
		 */
		void setEventID(Ice::Current& current, int nEventID);

		/** ���ͱ���.
		 *  �������� pushAlarm 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    p     : AlarmWrapper&                                 ����ģ��
		 *    function : const string&                              �����쳣�ĺ���
		 *    nAlarmId    : int										�����¼���
		 *    alarmMsg    : const AlarmMsg&							��������
		 *    ex      : std::exception&                             �쳣��Ϣ
		 */
		void pushAlarm(AlarmWrapper& p, const string& function, int nAlarmId, const AlarmMsg& alarmMsg, std::exception& ex);

		/** ���ͱ���.
		 *  �������� pushAlarm 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    p     : AlarmWrapper&                                 ����ģ��
		 *    nAlarmId    : int										�����¼���
		 *    alarmMsg    : const AlarmMsg&							��������
		 */
		void pushAlarm(AlarmWrapper& p, int nAlarmId, const AlarmMsg& alarmMsg);

		/** ��¼������־.
		 *  �������� logAlarm 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log     : LOG&										��־ģ��
		 *    alarmMsg    : const AlarmMsg&							��������
		 */
		void logAlarm(LOG& log, const AlarmMsg& alarmMsg);
	}
}
