#pragma once
#include <pace/pace.h>
#include <log4cplus/LOG.h>
#include <Slice/CltsException.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** �Ǽǵ����߽���.
		 *  �������� cltsInit 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    pComponent��iPlature::Component*                      ʵ����ַ
		 */
		void cltsInit(Component* pComponent);

		/** ��ӡ�������.
		 *  �������� logInvokedEnd 
		 *  ����ֵ�� void
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    log : LOG                                             ��־����
		 *    timeStart :  IceUtil::Time                            ���ÿ�ʼʱ��
		 */
		void logInvokedEnd(LOG& log, IceUtil::Time timeStart);

		/** ������������������(��ӵ�����).
		 *  �������� createCurrent 
		 *  ����ֵ�� Current                �������������ݣ���������Ϣ��
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    strCallerFunc : const string&							�����ߺ�����
		 */
		Ice::Current createCurrent(const string& strCallerFunc);

		/** ������������������(��ӱ�����).
		 *  �������� createCurrent 
		 *  ����ֵ�� Current                �������������ݣ���������Ϣ��
		 *  �����б�
		 *    ��������    					ȡֵ��Χ     		    ����
		 *    current : const Ice::Current&                         ��������������
		 *    strInvokdeFunc : const string&						�������ߺ�����
		 */
		Ice::Current createCurrent(const Ice::Current& current, const string& strInvokdeFunc);
	}
}
