#pragma once 

#include <CLTS.h>
#include <Util.h>

namespace CLTS
{
	namespace DAL
	{
		class EventDAL
		{
		private:
			string m_strDbCfgFile; // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����ָ��

			/** ���������¼���.
			 *  �������� generateEventID 
			 *  ����ֵ�� int					�����¼���	                 
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    ��
			 */
			int generateEventID();

		public:
			EventDAL(string strDbCfgFile, iDA::Connection* pCon);
			~EventDAL(void);

			/** ������������Ϣ�м�������¼���.
			 *  �������� generateEventID 
			 *  ����ֵ�� int					                 
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    current : Ice::Current&		 						������������Ϣ
			 */
			int generateEventID(Ice::Current& current);
		};
	}
}