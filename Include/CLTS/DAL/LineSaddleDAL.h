#pragma once
#include <Slice/LineSaddle.h>
#include <CLTS.h>

namespace CLTS
{
	namespace DAL
	{
		class LineSaddleDAL
		{
		private:
			string m_strDbCfgFile;	 // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����ָ��

			LineSaddleDAL(void);

		public:
			LineSaddleDAL(string strDbCfgFile, iDA::Connection* pCon);
			~LineSaddleDAL(void);

			// L2�����ƻ�״̬
			const static int COIL_IN_YARD = 100;
			const static int COIL_IN_CRANE = 200;
			const static int COIL_IN_LINE = 300;
			const static int COIL_IN_UNCOILER = 400;
			const static int UNCOILER_DONE = 500;

			/** ���ݰ����ţ���ȡ���鰰���趨��Ϣ.
			 *  �������� getSaddleDefine 
			 *  ����ֵ�� bool					��ȡ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    saddleNo : string		 								���鰰����
			 *    lineSaddleDesc : LineSaddleDesc&		 				���˼ƻ���Ϣ
			 *    current : const Ice::Current&                         ���ö���Ϣ
			*/
			bool getSaddleDefine(const string& saddleNo, LineSaddleDesc& lineSaddleDesc, const Current& current);

			/** ���ݸ־�ţ���ȡ������ڸ��ٱ��еĿ�λ��Ϣ.
			 *  �������� getStockNoFromLineExitTrack 
			 *  ����ֵ�� bool					��ȡ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : const string&		 							���Ϻ�
			 *    lineSaddleDesc : string&		 						��λ��
			 *    current : const Ice::Current&                         ���ö���Ϣ
			*/
			bool getStockNoFromLineExitTrack(const string& matNo, string& stockNo, const Current& current);

			/** ���ݸ־�ţ���ȡ������ڸ��ٱ��еĿ�λ��Ϣ.
			 *  �������� getStockNoFromLineEntryTrack 
			 *  ����ֵ�� bool					��ȡ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : const string&		 							���Ϻ�
			 *    stockNo : string&		 								��λ��
			 *    current : const Ice::Current&                         ���ö���Ϣ
			*/
			bool getStockNoFromLineEntryTrack(const string& matNo, string& stockNo, const Current& current);

			/** ���ݸ־�ţ���ȡ���������ƻ�״̬.
			 *  �������� getL2PlanState 
			 *  ����ֵ�� bool					��ȡ���
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : const string&		 							���Ϻ�
			 *    planState : int&		 								���ϵļƻ�״̬
			 *    current : const Ice::Current&                         ���ö���Ϣ
			*/
			bool getL2PlanState(const string& matNo, int& planState, const Current& current);

			/** ��λ���Ƿ�Ϊ�г�.
			 *  �������� isCraneStock 
			 *  ����ֵ�� bool					�г����
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    stockNo : const string&		 						���Ϻ�
			 *    current : const Ice::Current&                         ���ö���Ϣ
			*/
			bool isCraneStock(const string& stockNo, const Current& current);
		};
	}
}