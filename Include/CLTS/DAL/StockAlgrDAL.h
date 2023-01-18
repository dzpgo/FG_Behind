#pragma once
#include <Slice/StockAlgr.h>
#include <CLTS.h>

namespace CLTS
{
	namespace DAL
	{
		class StockAlgrDAL
		{
		private:
			string m_strDbCfgFile; // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����ָ��

		public:
			StockAlgrDAL(string strDbCfgFile, iDA::Connection* pCon);
			~StockAlgrDAL(void);

			/** ������λ�Ƽ�����.
			 *  �������� insertRequest 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    request : const RecommRequDesc&						��λ�Ƽ�������Ϣ
			 *    current : const Ice::Current&                         ���ö���Ϣ
			 */
			void insertRequest(const RecommRequDesc& request, const Current& current);

			/** ������λ�Ƽ���Ӧ.
			 *  �������� insertReponse 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    reponse : const RecommRepoDesc& 						��λ�Ƽ���Ӧ��Ϣ
			 *    current : const Ice::Current&                         ���ö���Ϣ
			 */
			void insertReponse(const RecommRepoDesc& reponse, const Current& current);

			/** ��ȡ��λ�Ƽ���Ϣ.
			 *  �������� getReponse 
			 *  ����ֵ�� bool                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    recommendId : int						 				��λ�Ƽ�����ID
			 *    reponse : const RecommRepoDesc& 						��λ�Ƽ���Ӧ��Ϣ
			 */
			bool getReponse(int recommendId, RecommRepoDesc& reponse);

			/** ��ȡ��λ�Ƽ�����ʱ��.
			 *  �������� getRequestTime 
			 *  ����ֵ�� bool                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    recommendId : int						 				��λ�Ƽ�����ID
			 *    requestTime : iDA::DateTime						 	��λ�Ƽ�����ʱ��
			 *    recomType : RecommType						 		��λ�Ƽ���������
			 */
			bool getRequestTime(int recommendId, iDA::DateTime& requestTime, RecommType& recomType);
		};
	}
}
