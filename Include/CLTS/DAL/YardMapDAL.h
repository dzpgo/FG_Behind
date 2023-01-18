#pragma once
#include <CLTS.h>
#include <Slice/YardMapFactory.h>

namespace CLTS
{
	namespace DAL
	{
		const static int EMPTY_POSITION = 9999;

		class YardMapDAL
		{
		private:
			string m_strDbCfgFile; // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����

		public:
			YardMapDAL(string strDbCfgFile, iDA::Connection* pCon);
			~YardMapDAL(void);

			/** ��ͼ�����г���λ.
			 *  �������� insertStock 
			 *  ����ֵ�� void
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    stockDesc : StockDesc 								��λ
			 */
			void insertCraneStock(StockDesc stockDesc);

			/** ��ͼ����������λ.
			 *  �������� insertStock 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    stockDesc : StockDesc 								��λ
			 *    saddleDesc : SaddleDesc 								����
			 */
			void insertStock(StockDesc stockDesc, SaddleDesc saddleDesc);

			/** ���������ҵ�������.
			 *  �������� getSaddleNoByPos 
			 *  ����ֵ�� StringSeq				�ҵ��İ�����                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    bayNo : const string& 								���
			 *    posX : int											������
			 *    posY : int											С������
			 */
			StringSeq getSaddleNoByPos(const string& bayNo, int posX, int posY);

			/** ���������ҵ���λ��.
			 *  �������� getStockNoByPos 
			 *  ����ֵ�� bool                   �Ƿ��ҵ���λ
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    bayNo : const string& 								���
			 *    posX : int											������
			 *    posY : int											С������				
			 *    stockNo : string&										С������				
			 */
			bool getStockNoByPos(const string& bayNo, int posX, int posY, string& stockNo);

			/** ���������ҵ�ͣ��λ��.
			 *  �������� getParkingNoByPos 
			 *  ����ֵ�� bool                   �Ƿ��ҵ�ͣ��λ
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneNo : const string& 								�г���
			 *    posX : int											������
			 *    posY : int											С������				
			 *    stockNo : string&										С������				
			 */
			bool getParkingNoByPos(const string& craneNo, int posX, int posY, string& parkingNo);

			/** �����г����ҵ����.
			 *  �������� insertStock 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneNo : const string& 								�г���
			 */
			string getBayNobyCrane(const string& craneNo);

			/** ���������λ���ҵ��������.
			 *  �������� getLiftUpPosByStockNo 
			 *  ����ֵ�� bool                   �Ƿ��ҵ���λ
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    bayNo : const string& 								���
			 *    posX : int											������
			 *    posY : int											С������				
			 *    stockNo : string&										С������				
			 */
			bool getLiftUpPosByStockNo(const string& stockNo, int& posX, int& posY, int& posZ);

			/** ������ؿ�λ���ҵ��������.
			 *  �������� getLiftDownPosByStockNo 
			 *  ����ֵ�� bool                   �Ƿ��ҵ���λ
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    bayNo : const string& 								���
			 *    posX : int											������
			 *    posY : int											С������				
			 *    stockNo : string&										С������				
			 */
			bool getLiftDownPosByStockNo(const string& stockNo, int& posX, int& posY, int& posZ);

			/** ���ʧ�ܵĺ󱸲�������.
			 *  �������� liftDownAfterError 
			 *  ����ֵ�� void                   ��
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    stockNo : const string& 								��λ��
			 *    current : const Ice::Current&                         ���ö���Ϣ
			 */
			void liftDownError(const string& stockNo, const Current& current);
		};
	}
}
