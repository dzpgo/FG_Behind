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
			string m_strDbCfgFile;	 // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库连接指针

			LineSaddleDAL(void);

		public:
			LineSaddleDAL(string strDbCfgFile, iDA::Connection* pCon);
			~LineSaddleDAL(void);

			// L2生产计划状态
			const static int COIL_IN_YARD = 100;
			const static int COIL_IN_CRANE = 200;
			const static int COIL_IN_LINE = 300;
			const static int COIL_IN_UNCOILER = 400;
			const static int UNCOILER_DONE = 500;

			/** 依据鞍座号，读取机组鞍座设定信息.
			 *  函数名： getSaddleDefine 
			 *  返回值： bool					读取结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    saddleNo : string		 								机组鞍座号
			 *    lineSaddleDesc : LineSaddleDesc&		 				吊运计划信息
			 *    current : const Ice::Current&                         调用端信息
			*/
			bool getSaddleDefine(const string& saddleNo, LineSaddleDesc& lineSaddleDesc, const Current& current);

			/** 依据钢卷号，读取机组出口跟踪表中的库位信息.
			 *  函数名： getStockNoFromLineExitTrack 
			 *  返回值： bool					读取结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : const string&		 							材料号
			 *    lineSaddleDesc : string&		 						库位号
			 *    current : const Ice::Current&                         调用端信息
			*/
			bool getStockNoFromLineExitTrack(const string& matNo, string& stockNo, const Current& current);

			/** 依据钢卷号，读取机组入口跟踪表中的库位信息.
			 *  函数名： getStockNoFromLineEntryTrack 
			 *  返回值： bool					读取结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : const string&		 							材料号
			 *    stockNo : string&		 								库位号
			 *    current : const Ice::Current&                         调用端信息
			*/
			bool getStockNoFromLineEntryTrack(const string& matNo, string& stockNo, const Current& current);

			/** 依据钢卷号，读取机组生产计划状态.
			 *  函数名： getL2PlanState 
			 *  返回值： bool					读取结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : const string&		 							材料号
			 *    planState : int&		 								材料的计划状态
			 *    current : const Ice::Current&                         调用端信息
			*/
			bool getL2PlanState(const string& matNo, int& planState, const Current& current);

			/** 库位号是否为行车.
			 *  函数名： isCraneStock 
			 *  返回值： bool					行车结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    stockNo : const string&		 						材料号
			 *    current : const Ice::Current&                         调用端信息
			*/
			bool isCraneStock(const string& stockNo, const Current& current);
		};
	}
}