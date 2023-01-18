#pragma once
#include <Slice/CranePlanFactory.h>
#include <CLTS.h>

namespace CLTS
{
	namespace DAL
	{
		class CranePlanDAL
		{
		private:
			string m_strDbCfgFile;	 // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����ָ��

			CranePlanDAL(void);

			// ���ݿ�������ƻ�ģ�飩
			const string m_tableCranePlan;
			const string m_tableCranePlanHisy;

		public:
			CranePlanDAL(string strDbCfgFile, iDA::Connection* pCon);
			~CranePlanDAL(void);

			/** ���ݼƻ��ţ���ȡ���˼ƻ�.
			 *  �������� initCranePlan 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    nPlanNo : int		 									�ƻ���
			 *    cranePlanDesc : CranePlanDesc&		 				���˼ƻ���Ϣ
			*/
			bool getCranePlan(int nPlanNo, CranePlanDesc& cranePlanDesc, const Ice::Current& current);

			/** ��ʼ�����˼ƻ�.
			 *  �������� initCranePlan 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    yardNo : const string&		 						��ʼ������
			*/
			bool getSaddleNo(const string& stockNo, string& saddleNo, const Ice::Current& current);

			/** ��ʼ��Z32/Z33����˼ƻ�.
			 *  �������� initCranePlanZ32Z33 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    ��
			*/
			void initCranePlanZ32Z33(const Ice::Current& current);

			/** ��ʼ��Z51/Z52/Z53����˼ƻ�.
			 *  �������� initCranePlanZ51Z52Z53 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    ��
			*/
			void initCranePlanZ51Z52Z53(const Ice::Current& current);

			/** ɾ�����˼ƻ�.
			 *  �������� delCranePlan 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    nPlanNo : int		 									�ƻ���
			*/
			void delCranePlan(int cranePlanNo, const Ice::Current& current);

			/** ��ȡ���϶�Ӧ�ĵ��˼ƻ�.
			 *  �������� getPlanNoByMatNo 
			 *  ����ֵ�� vector<int>			���˼ƻ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    nPlanNo : int		 									���Ϻ�
			 *    craneInstCode : string		 						L3����ָ���
			*/
			vector<int> getPlanNoByMatNo(const string& matNo, const string& craneInstCode, const Ice::Current& current);

			/** ��ȡ��ɾ���ĵ��˼ƻ�.
			 *  �������� getPlanNoDeleted 
			 *  ����ֵ�� vector<int>			���˼ƻ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : cosnt string&		 							���Ϻ�
			 *    craneInstCode : cosnt string&		 					L3����ָ���
			*/
			vector<int> getPlanNoDeleted(const string& matNo, const string& craneInstCode, const Ice::Current& current);
		};
	}
}