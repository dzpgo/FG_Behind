#pragma once
#include <Slice/CranePlan.h>

using namespace std;
using namespace Ice;

namespace CLTS
{
	namespace Util
	{
		/** ���˼ƻ�������.
		 *  �������� catchFunc 
		 */
		class CranePlanHelper
		{
			/** �ַ���ת��Ϊ����״̬.
			 *  �������� convert 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    strStatus : const string&                             ����״̬�ַ���
			 *    status    : PLANSTATUS&                               ����״̬
			 */
			static void convert(const string& strStatus, CLTS::PLANSTATUS& status);
		};
	}
}
