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
			string m_strDbCfgFile; // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库连接指针

		public:
			StockAlgrDAL(string strDbCfgFile, iDA::Connection* pCon);
			~StockAlgrDAL(void);

			/** 新增库位推荐请求.
			 *  函数名： insertRequest 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    request : const RecommRequDesc&						库位推荐请求信息
			 *    current : const Ice::Current&                         调用端信息
			 */
			void insertRequest(const RecommRequDesc& request, const Current& current);

			/** 新增库位推荐响应.
			 *  函数名： insertReponse 
			 *  返回值： void                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    reponse : const RecommRepoDesc& 						库位推荐响应信息
			 *    current : const Ice::Current&                         调用端信息
			 */
			void insertReponse(const RecommRepoDesc& reponse, const Current& current);

			/** 读取库位推荐信息.
			 *  函数名： getReponse 
			 *  返回值： bool                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    recommendId : int						 				库位推荐请求ID
			 *    reponse : const RecommRepoDesc& 						库位推荐响应信息
			 */
			bool getReponse(int recommendId, RecommRepoDesc& reponse);

			/** 读取库位推荐请求时间.
			 *  函数名： getRequestTime 
			 *  返回值： bool                   
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    recommendId : int						 				库位推荐请求ID
			 *    requestTime : iDA::DateTime						 	库位推荐请求时间
			 *    recomType : RecommType						 		库位推荐请求类型
			 */
			bool getRequestTime(int recommendId, iDA::DateTime& requestTime, RecommType& recomType);
		};
	}
}
