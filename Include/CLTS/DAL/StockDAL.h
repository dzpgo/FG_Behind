#pragma once
#include <Slice/CranePlanFactory.h>
#include <CLTS.h>

namespace CLTS
{
	namespace DAL
	{
		class StockDAL
		{
		private:
			string m_strDbCfgFile;	 // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����ָ��

			StockDAL(void);

		public:
			StockDAL(string strDbCfgFile, iDA::Connection* pCon);
			~StockDAL(void);

			/** ���ݿ�λ�ţ���ȡ��λ��Ϣ.
			 *  �������� getStockDesc 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    stockNo : string		 								��λ��
			 *    stockDesc : StockDesc&		 						��λ��Ϣ
			*/
			void getStockDesc(string stockNo, StockDesc& stockDesc);

			/** ��ʼ�����˼ƻ�.
			 *  �������� initCranePlan 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    yardNo : const string&		 						��ʼ������
			*/
			bool setStockPos(const string& stockNo , string& saddleNo);

			/** ��ʼ��Z32/Z33����˼ƻ�.
			 *  �������� initCranePlanZ32Z33 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    ��
			*/
			void initCranePlanZ32Z33();

			/** ��ʼ��Z51/Z52/Z53����˼ƻ�.
			 *  �������� initCranePlanZ51Z52Z53 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    ��
			*/
			void initCranePlanZ51Z52Z53();
		};
	}
}