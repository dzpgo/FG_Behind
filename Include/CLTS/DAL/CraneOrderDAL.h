#pragma once
#include "StockAlgr.h"
#include <CLTS.h>
#include <Slice/CraneOrderFactory.h>
#include <Slice/CranePlanFactory.h>
#include <Slice/YardMapFactory.h>

extern string g_tableCraneOrder;		// 吊运指令表
extern string g_tableCraneOrderOper;	// 吊运实绩表
extern string g_tableCraneOrderHisy;	// 吊运指令履历表
extern string g_tableCraneOrderPriority;// 吊运指令优先级定义表

namespace CLTS
{
	namespace DAL
	{
		class CraneOrderDAL
		{
		private:
			string m_strDbCfgFile; // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库连接指针

			/** 删除库位推荐(依据指令编号).
			 *  函数名： delRecommend 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 */
			void delRecommend(const CraneOrderDesc& craneOrderDesc, const Current& current);

		public:
			CraneOrderDAL(string strDbCfgFile, iDA::Connection* pCon);
			~CraneOrderDAL(void);

			/** 读取指令的材料号.
			 *  函数名： getCraneOrderNo 
			 *  返回值： bool					                 
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    orderNo : int& 										指令编号
			 *    matNo : string&		 								材料号
			 */
			bool getCraneOrderNo(int orderNo, string& matNo);
			
			/** 读取材料的指令编号.
			 *  函数名： getCraneOrderNo 
			 *  返回值： bool					                 
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : string		 								材料号
			 *    orderType : int 										指令类型
			 *    orderNo : int& 										指令编号
			 */
			bool getCraneOrderNo(string matNo, int orderType, int& orderNo);

			/** 读取材料和起卷位符合的指令.
			 *  函数名： getCraneOrderNoByLiftUp 
			 *  返回值： bool					                 
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : string		 								材料号
			 *    liftUpStock : StockDesc 								起卷库位
			 *    orderNo : int& 										指令编号
			 */
			bool getCraneOrderNoByLiftUp(string matNo, StockDesc liftUpStock, int& orderNo);

			/** 读取材料的计划编号.
			 *  函数名： getCranePlanNo 
			 *  返回值： bool					                 
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : string		 								材料号
			 *    orderType : int 										指令类型
			 *    orderNo : int& 										计划编号
			 */
			bool getCranePlanNo(string matNo, int orderType, int& planNo);

			/** 新增吊运指令.
			 *  函数名： insertCraneOrder 
			 *  返回值： int					新增指令编号
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    current : const Ice::Current&                         调用端信息
			 *
			 */
			int insertCraneOrder(const CraneOrderDesc& craneOrderDesc, const Current& current);

			/** 新增吊运实绩.
			 *  函数名： insertOrderOper 
			 *  返回值： int                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    orderOperDesc : const OrderOperDesc& 					下发标记
			 */
			int insertOrderOper(const CraneOrderDesc& craneOrderDesc, const CranePlanDesc& planDesc, const OrderOperDesc& orderOperDesc, const Current& current);

			/** 指令中写入库位推荐请求编号.
			 *  函数名： setReqRecommend 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    recommendId : int 									推荐请求编号
			 */
			void setReqRecommend(const CraneOrderDesc& craneOrderDesc, int& recommendId);

			/** 读取推荐应答对应的指令编号.
			 *  函数名： getOrderNoByRecommend 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    reponse : const RecommRepoDesc& 						推荐请求应答
			 *    nOrderNo : int& 										指令编号
			 */
			bool getOrderNoByRecommend(const RecommRepoDesc& reponse, int& nOrderNo);

			/** 删除指令(依据指令编号).
			 *  函数名： delOrder 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 */
			void delOrder(const CraneOrderDesc& craneOrderDesc, const Current& current);

			/** 更新起吊位置(依据指令编号).
			 *  函数名： updateOrderFromStock 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    fromStockNo : const string& 							起吊库位
			 *    bayNo : const string& 								起吊跨号
			 */
			void setOrderFromStock(const CraneOrderDesc& craneOrderDesc, const string& fromStockNo, const string& bayNo, const Current& current);

			/** 更新卸下位置.
			 *  函数名： updateOrderToStock 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    toStockNo : const string& 							起吊库位
			 */
			void setOrderToStock(const CraneOrderDesc& craneOrderDesc, const string& toStockNo, const Current& current);

			/** 设定吊运指令的吊运计划号.
			 *  函数名： setCranePlanNo 
			 *  返回值： int					新增指令编号
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    planNo : int 											计划编号
			 */
			void setCranePlanNo(const CraneOrderDesc& craneOrderDesc, int planNo, const Current& current);

			/** 更新指令的下发标记.
			 *  函数名： setFlagDispatch 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    flagDispatch : int 									下发标记
			 */
			void setFlagDispatch(const CraneOrderDesc& craneOrderDesc, int flagDispatch, const Current& current);

			/** 更新指令的下发标记.
			 *  函数名： setFlagDispatch 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    flagDispatchAck : int 								应答结果
			 *    dispCraneNo : const string& 							分配行车
			 */
			void setFlagDispatch(const CraneOrderDesc& craneOrderDesc, int flagDispatchAck, const string& dispCraneNo, const Current& current);

			/** 更新指令的下发调度标记.
			 *  函数名： setFlagEnable 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    flagEnable : int 										可吊标记
			 */
			void setFlagEnable(const CraneOrderDesc& craneOrderDesc, int flagEnable, const Current& current);

			/** 更新指令的删除标记.
			 *  函数名： setFlagDel 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    flagDel : int 										删除标记
			 */
			void setFlagDel(const CraneOrderDesc& craneOrderDesc, int flagDel, const Current& current);

			/** 更新指令的分配行车号.
			 *  函数名： setCraneNo 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 *    craneNo : const string& 								分配行车号
			 */
			void setCraneNo(const CraneOrderDesc& craneOrderDesc, const string& craneNo, const Current& current);

			/** 更新指令的优先级.
			 *  函数名： setOrderPriority 
			 *  返回值： bool                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 */
			void setOrderPriority(const CraneOrderDesc& craneOrderDesc, int nOrderPriority, const Current& current);

			/** 读取指令的优先级.
			 *  函数名： getOrderPriority 
			 *  返回值： int                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    craneOrderDesc : const CraneOrderDesc&		 		吊运指令
			 */
			bool getOrderPriority(const CraneOrderDesc& craneOrderDesc, int& nOrderPriority, const Current& current);

			/** 读取已删除的吊运指令号.
			 *  函数名： getDeletedOrderNo 
			 *  返回值： vector<int>                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    无
			 */
			vector<int> getDeletedOrderNo(const Current& current);

			/** 读取指定类型的吊运指令号.
			 *  函数名： getOrderNoByOrderType 
			 *  返回值： vector<int>                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    nOrderType : int 										指令类型
			 */
			vector<int> getOrderNoByOrderType(int nOrderType, const Current& current);

			/** 读取指定吊运计划的吊运指令号.
			 *  函数名： getOrderNoByPlanNo 
			 *  返回值： vector<int>
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    nPlanNo : int		 									计划号
			*/
			vector<int> getOrderNoByPlanNo(int cranePlanNo, const Current& current);

			/** 检查是否存在于调度模型中的吊运指令.
			 *  函数名： isExistedInDispMM 
			 *  返回值： bool					存在结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    nOrderNo : int		 								吊运指令号
			 *    matNo : const string&		 							钢卷号
			*/
			bool isExistedInDispMM(int nOrderNo, const string& matNo, const Current& current);

			/** 检查是否已删除指定时间.
			 *  函数名： isDeletedTimeout 
			 *  返回值： bool					存在结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    nOrderNo : int		 								吊运指令号
			 *    matNo : const string&		 							钢卷号
			 *    deletedTimeOut : int		 							删除距当前时间
			*/
			bool isDeletedTimeout(int nOrderNo, const string& matNo, int deletedTimeOut, const Current& current);
		};
	}
}