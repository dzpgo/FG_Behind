#pragma once
#include "StockAlgr.h"
#include <CLTS.h>
#include <Slice/CraneOrderFactory.h>
#include <Slice/CranePlanFactory.h>
#include <Slice/YardMapFactory.h>

extern string g_tableCraneOrder;		// ����ָ���
extern string g_tableCraneOrderOper;	// ����ʵ����
extern string g_tableCraneOrderHisy;	// ����ָ��������
extern string g_tableCraneOrderPriority;// ����ָ�����ȼ������

namespace CLTS
{
	namespace DAL
	{
		class CraneOrderDAL
		{
		private:
			string m_strDbCfgFile; // ���ݿ����������ļ�
			iDA::Connection* m_pCon; // ���ݿ�����ָ��

			/** ɾ����λ�Ƽ�(����ָ����).
			 *  �������� delRecommend 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 */
			void delRecommend(const CraneOrderDesc& craneOrderDesc, const Current& current);

		public:
			CraneOrderDAL(string strDbCfgFile, iDA::Connection* pCon);
			~CraneOrderDAL(void);

			/** ��ȡָ��Ĳ��Ϻ�.
			 *  �������� getCraneOrderNo 
			 *  ����ֵ�� bool					                 
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    orderNo : int& 										ָ����
			 *    matNo : string&		 								���Ϻ�
			 */
			bool getCraneOrderNo(int orderNo, string& matNo);
			
			/** ��ȡ���ϵ�ָ����.
			 *  �������� getCraneOrderNo 
			 *  ����ֵ�� bool					                 
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : string		 								���Ϻ�
			 *    orderType : int 										ָ������
			 *    orderNo : int& 										ָ����
			 */
			bool getCraneOrderNo(string matNo, int orderType, int& orderNo);

			/** ��ȡ���Ϻ����λ���ϵ�ָ��.
			 *  �������� getCraneOrderNoByLiftUp 
			 *  ����ֵ�� bool					                 
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : string		 								���Ϻ�
			 *    liftUpStock : StockDesc 								����λ
			 *    orderNo : int& 										ָ����
			 */
			bool getCraneOrderNoByLiftUp(string matNo, StockDesc liftUpStock, int& orderNo);

			/** ��ȡ���ϵļƻ����.
			 *  �������� getCranePlanNo 
			 *  ����ֵ�� bool					                 
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    matNo : string		 								���Ϻ�
			 *    orderType : int 										ָ������
			 *    orderNo : int& 										�ƻ����
			 */
			bool getCranePlanNo(string matNo, int orderType, int& planNo);

			/** ��������ָ��.
			 *  �������� insertCraneOrder 
			 *  ����ֵ�� int					����ָ����
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    current : const Ice::Current&                         ���ö���Ϣ
			 *
			 */
			int insertCraneOrder(const CraneOrderDesc& craneOrderDesc, const Current& current);

			/** ��������ʵ��.
			 *  �������� insertOrderOper 
			 *  ����ֵ�� int                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    orderOperDesc : const OrderOperDesc& 					�·����
			 */
			int insertOrderOper(const CraneOrderDesc& craneOrderDesc, const CranePlanDesc& planDesc, const OrderOperDesc& orderOperDesc, const Current& current);

			/** ָ����д���λ�Ƽ�������.
			 *  �������� setReqRecommend 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    recommendId : int 									�Ƽ�������
			 */
			void setReqRecommend(const CraneOrderDesc& craneOrderDesc, int& recommendId);

			/** ��ȡ�Ƽ�Ӧ���Ӧ��ָ����.
			 *  �������� getOrderNoByRecommend 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    reponse : const RecommRepoDesc& 						�Ƽ�����Ӧ��
			 *    nOrderNo : int& 										ָ����
			 */
			bool getOrderNoByRecommend(const RecommRepoDesc& reponse, int& nOrderNo);

			/** ɾ��ָ��(����ָ����).
			 *  �������� delOrder 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 */
			void delOrder(const CraneOrderDesc& craneOrderDesc, const Current& current);

			/** �������λ��(����ָ����).
			 *  �������� updateOrderFromStock 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    fromStockNo : const string& 							�����λ
			 *    bayNo : const string& 								������
			 */
			void setOrderFromStock(const CraneOrderDesc& craneOrderDesc, const string& fromStockNo, const string& bayNo, const Current& current);

			/** ����ж��λ��.
			 *  �������� updateOrderToStock 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    toStockNo : const string& 							�����λ
			 */
			void setOrderToStock(const CraneOrderDesc& craneOrderDesc, const string& toStockNo, const Current& current);

			/** �趨����ָ��ĵ��˼ƻ���.
			 *  �������� setCranePlanNo 
			 *  ����ֵ�� int					����ָ����
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    planNo : int 											�ƻ����
			 */
			void setCranePlanNo(const CraneOrderDesc& craneOrderDesc, int planNo, const Current& current);

			/** ����ָ����·����.
			 *  �������� setFlagDispatch 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    flagDispatch : int 									�·����
			 */
			void setFlagDispatch(const CraneOrderDesc& craneOrderDesc, int flagDispatch, const Current& current);

			/** ����ָ����·����.
			 *  �������� setFlagDispatch 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    flagDispatchAck : int 								Ӧ����
			 *    dispCraneNo : const string& 							�����г�
			 */
			void setFlagDispatch(const CraneOrderDesc& craneOrderDesc, int flagDispatchAck, const string& dispCraneNo, const Current& current);

			/** ����ָ����·����ȱ��.
			 *  �������� setFlagEnable 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    flagEnable : int 										�ɵ����
			 */
			void setFlagEnable(const CraneOrderDesc& craneOrderDesc, int flagEnable, const Current& current);

			/** ����ָ���ɾ�����.
			 *  �������� setFlagDel 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    flagDel : int 										ɾ�����
			 */
			void setFlagDel(const CraneOrderDesc& craneOrderDesc, int flagDel, const Current& current);

			/** ����ָ��ķ����г���.
			 *  �������� setCraneNo 
			 *  ����ֵ�� void                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 *    craneNo : const string& 								�����г���
			 */
			void setCraneNo(const CraneOrderDesc& craneOrderDesc, const string& craneNo, const Current& current);

			/** ����ָ������ȼ�.
			 *  �������� setOrderPriority 
			 *  ����ֵ�� bool                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 */
			void setOrderPriority(const CraneOrderDesc& craneOrderDesc, int nOrderPriority, const Current& current);

			/** ��ȡָ������ȼ�.
			 *  �������� getOrderPriority 
			 *  ����ֵ�� int                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    craneOrderDesc : const CraneOrderDesc&		 		����ָ��
			 */
			bool getOrderPriority(const CraneOrderDesc& craneOrderDesc, int& nOrderPriority, const Current& current);

			/** ��ȡ��ɾ���ĵ���ָ���.
			 *  �������� getDeletedOrderNo 
			 *  ����ֵ�� vector<int>                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    ��
			 */
			vector<int> getDeletedOrderNo(const Current& current);

			/** ��ȡָ�����͵ĵ���ָ���.
			 *  �������� getOrderNoByOrderType 
			 *  ����ֵ�� vector<int>                   
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    nOrderType : int 										ָ������
			 */
			vector<int> getOrderNoByOrderType(int nOrderType, const Current& current);

			/** ��ȡָ�����˼ƻ��ĵ���ָ���.
			 *  �������� getOrderNoByPlanNo 
			 *  ����ֵ�� vector<int>
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    nPlanNo : int		 									�ƻ���
			*/
			vector<int> getOrderNoByPlanNo(int cranePlanNo, const Current& current);

			/** ����Ƿ�����ڵ���ģ���еĵ���ָ��.
			 *  �������� isExistedInDispMM 
			 *  ����ֵ�� bool					���ڽ��
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    nOrderNo : int		 								����ָ���
			 *    matNo : const string&		 							�־��
			*/
			bool isExistedInDispMM(int nOrderNo, const string& matNo, const Current& current);

			/** ����Ƿ���ɾ��ָ��ʱ��.
			 *  �������� isDeletedTimeout 
			 *  ����ֵ�� bool					���ڽ��
			 *  �����б�
			 *    ��������    					ȡֵ��Χ     		    ����
			 *    nOrderNo : int		 								����ָ���
			 *    matNo : const string&		 							�־��
			 *    deletedTimeOut : int		 							ɾ���൱ǰʱ��
			*/
			bool isDeletedTimeout(int nOrderNo, const string& matNo, int deletedTimeOut, const Current& current);
		};
	}
}