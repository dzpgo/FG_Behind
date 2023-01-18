#pragma once
#include <Slice/ProdLine.h>
#include <CLTS.h>

extern string g_tableLineExitL2Info;
extern string g_tableCoilInfo;

namespace CLTS
{
	namespace DAL
	{
		class CoilDAL
		{
		private:
			string m_strDbCfgFile;	 // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����ָ��

			CoilDAL(void);

		public:
			CoilDAL(string strDbCfgFile, iDA::Connection* pCon);
			~CoilDAL(void);

			//static map<string, string> getTestMap();

			/** ���ݸ־�ţ���ȡ���ڸ־�L2������Ϣ.
			 *  �������� getExitSaddleTrack 
			 *  ����ֵ�� bool					��ȡ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : string		 								�־��
			 *    exitSaddleTrack : ExitSaddleTrack&		 			���ڸ־�L2������Ϣ
			*/
			bool getExitSaddleTrack(string matNo, ExitSaddleTrack& exitSaddleTrack);

			/** ���ݸ־�ţ���ȡ��ڸ־�L2�ƻ���Ϣ.
			 *  �������� getL2EntryPlan 
			 *  ����ֵ�� bool					��ȡ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : string		 								�־��
			 *    nextUnitNo : string		 							��ڻ����
			 *    exitSaddleTrack : ExitSaddleTrack&		 			���ڸ־�L2������Ϣ
			 */
			bool getL2EntryPlan(string matNo, string nextUnitNo, ExitSaddleTrack& exitSaddleTrack);

			///** ���ݸ־�ţ���ȡ��ڸ־�L2������Ϣ.
			// *  �������� getEntrySaddleTrack 
			// *  ����ֵ�� bool					��ȡ���
			// *  �����б�
			// *    ��������    					ȡֵ��Χ     		    ����
			// *    matNo : string		 								�־��
			// *    exitSaddleTrack : EntrySaddleTrack&		 			��ڸ־�L2������Ϣ
			//*/
			//bool getEntrySaddleTrack(string matNo, EntrySaddleTrack& exitSaddleTrack);

			/** ���ڸ־�L2������Ϣд��־���Ϣ��.
			 *  �������� insertCoil 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    exitSaddleTrack : const ExitSaddleTrack&		 		�־��
			*/
			void insertCoil(const ExitSaddleTrack& exitSaddleTrack, const Ice::Current& current);

			/** ����ڸ�����Ϣ�ȶ�.
			 *  �������� checkDiffWithLineExitTrack 
			 *  ����ֵ�� bool		�Ƿ�һ��
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : string		 								�־��
			*/
			bool checkDiffWithLineExitTrack(string matNo);

			/** �趨�־�ȷ����Ϣ.
			 *  �������� setConfirmInfo 
			 *  ����ֵ�� void		
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    desc : CoilConfirmDesc		 						�־�ȷ����Ϣ
			*/
			void setConfirmInfo(CoilConfirmDesc desc);

			/** ��ȡ�־�ȷ����Ϣ.
			 *  �������� setConfirmInfo 
			 *  ����ֵ�� bool				��ȡ���		
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : const string&									�־��
			 *    desc : CoilConfirmDesc		 						�־�ȷ����Ϣ
			*/
			bool getConfirmInfo(const string& matNo, CoilConfirmDesc& desc);

			/** �趨�־�״̬.
			 *  �������� setStatus 
			 *  ����ֵ�� void						
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    coilStatus : int										�־�״̬
			*/
			void setStatus(const string& matNo, int coilStatus);

			/** ��ȡ�־�״̬.
			 *  �������� getStatus 
			 *  ����ֵ�� bool					��ȡ���		
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : const string&									�־��
			 *    desc : CoilConfirmDesc		 						�־�״̬
			*/
			bool getStatus(const string& matNo, int& coilStatus);
		};
	}
}