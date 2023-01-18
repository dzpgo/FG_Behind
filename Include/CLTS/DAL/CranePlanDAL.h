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
			string m_strDbCfgFile;	 // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库连接指针

			CranePlanDAL(void);

			// 数据库表名（计划模块）
			const string m_tableCranePlan;
			const string m_tableCranePlanHisy;

		public:
			CranePlanDAL(string strDbCfgFile, iDA::Connection* pCon);
			~CranePlanDAL(void);

			/** 依据计划号，读取吊运计划.
			 *  函数名： initCranePlan 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    nPlanNo : int		 									计划号
			 *    cranePlanDesc : CranePlanDesc&		 				吊运计划信息
			*/
			bool getCranePlan(int nPlanNo, CranePlanDesc& cranePlanDesc, const Ice::Current& current);

			/** 初始化吊运计划.
			 *  函数名： initCranePlan 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    yardNo : const string&		 						初始化库区
			*/
			bool getSaddleNo(const string& stockNo, string& saddleNo, const Ice::Current& current);

			/** 初始化Z32/Z33库吊运计划.
			 *  函数名： initCranePlanZ32Z33 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    空
			*/
			void initCranePlanZ32Z33(const Ice::Current& current);

			/** 初始化Z51/Z52/Z53库吊运计划.
			 *  函数名： initCranePlanZ51Z52Z53 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    空
			*/
			void initCranePlanZ51Z52Z53(const Ice::Current& current);

			/** 删除吊运计划.
			 *  函数名： delCranePlan 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    nPlanNo : int		 									计划号
			*/
			void delCranePlan(int cranePlanNo, const Ice::Current& current);

			/** 读取材料对应的吊运计划.
			 *  函数名： getPlanNoByMatNo 
			 *  返回值： vector<int>			吊运计划号
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    nPlanNo : int		 									材料号
			 *    craneInstCode : string		 						L3吊运指令号
			*/
			vector<int> getPlanNoByMatNo(const string& matNo, const string& craneInstCode, const Ice::Current& current);

			/** 读取已删除的吊运计划.
			 *  函数名： getPlanNoDeleted 
			 *  返回值： vector<int>			吊运计划号
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : cosnt string&		 							材料号
			 *    craneInstCode : cosnt string&		 					L3吊运指令号
			*/
			vector<int> getPlanNoDeleted(const string& matNo, const string& craneInstCode, const Ice::Current& current);
		};
	}
}