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
			string m_strDbCfgFile;	 // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库连接指针

			StockDAL(void);

		public:
			StockDAL(string strDbCfgFile, iDA::Connection* pCon);
			~StockDAL(void);

			/** 依据库位号，读取库位信息.
			 *  函数名： getStockDesc 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    stockNo : string		 								库位号
			 *    stockDesc : StockDesc&		 						库位信息
			*/
			void getStockDesc(string stockNo, StockDesc& stockDesc);

			/** 初始化吊运计划.
			 *  函数名： initCranePlan 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    yardNo : const string&		 						初始化库区
			*/
			bool setStockPos(const string& stockNo , string& saddleNo);

			/** 初始化Z32/Z33库吊运计划.
			 *  函数名： initCranePlanZ32Z33 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    空
			*/
			void initCranePlanZ32Z33();

			/** 初始化Z51/Z52/Z53库吊运计划.
			 *  函数名： initCranePlanZ51Z52Z53 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    空
			*/
			void initCranePlanZ51Z52Z53();
		};
	}
}