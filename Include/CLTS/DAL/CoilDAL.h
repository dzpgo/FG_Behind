#pragma once
#include <Slice/ProdLine.h>
#include <CLTS.h>

extern string g_tableLineExitL2Info;
extern string g_tableCoilInfo;

namespace CLTS
{
	namespace DAL
	{
		class CoilDAL
		{
		private:
			string m_strDbCfgFile;	 // 数据库连接配置文件
			iDA::Connection* m_pCon; // 数据库连接指针

			CoilDAL(void);

		public:
			CoilDAL(string strDbCfgFile, iDA::Connection* pCon);
			~CoilDAL(void);

			//static map<string, string> getTestMap();

			/** 依据钢卷号，读取出口钢卷L2跟踪信息.
			 *  函数名： getExitSaddleTrack 
			 *  返回值： bool					读取结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : string		 								钢卷号
			 *    exitSaddleTrack : ExitSaddleTrack&		 			出口钢卷L2跟踪信息
			*/
			bool getExitSaddleTrack(string matNo, ExitSaddleTrack& exitSaddleTrack);

			/** 依据钢卷号，读取入口钢卷L2计划信息.
			 *  函数名： getL2EntryPlan 
			 *  返回值： bool					读取结果
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : string		 								钢卷号
			 *    nextUnitNo : string		 							入口机组号
			 *    exitSaddleTrack : ExitSaddleTrack&		 			出口钢卷L2跟踪信息
			 */
			bool getL2EntryPlan(string matNo, string nextUnitNo, ExitSaddleTrack& exitSaddleTrack);

			///** 依据钢卷号，读取入口钢卷L2跟踪信息.
			// *  函数名： getEntrySaddleTrack 
			// *  返回值： bool					读取结果
			// *  参数列表：
			// *    参数类型    					取值范围     		    描述
			// *    matNo : string		 								钢卷号
			// *    exitSaddleTrack : EntrySaddleTrack&		 			入口钢卷L2跟踪信息
			//*/
			//bool getEntrySaddleTrack(string matNo, EntrySaddleTrack& exitSaddleTrack);

			/** 出口钢卷L2跟踪信息写入钢卷信息表.
			 *  函数名： insertCoil 
			 *  返回值： void
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    exitSaddleTrack : const ExitSaddleTrack&		 		钢卷号
			*/
			void insertCoil(const ExitSaddleTrack& exitSaddleTrack, const Ice::Current& current);

			/** 与出口跟踪信息比对.
			 *  函数名： checkDiffWithLineExitTrack 
			 *  返回值： bool		是否一致
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : string		 								钢卷号
			*/
			bool checkDiffWithLineExitTrack(string matNo);

			/** 设定钢卷确认信息.
			 *  函数名： setConfirmInfo 
			 *  返回值： void		
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    desc : CoilConfirmDesc		 						钢卷确认信息
			*/
			void setConfirmInfo(CoilConfirmDesc desc);

			/** 读取钢卷确认信息.
			 *  函数名： setConfirmInfo 
			 *  返回值： bool				读取结果		
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : const string&									钢卷号
			 *    desc : CoilConfirmDesc		 						钢卷确认信息
			*/
			bool getConfirmInfo(const string& matNo, CoilConfirmDesc& desc);

			/** 设定钢卷状态.
			 *  函数名： setStatus 
			 *  返回值： void						
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    coilStatus : int										钢卷状态
			*/
			void setStatus(const string& matNo, int coilStatus);

			/** 读取钢卷状态.
			 *  函数名： getStatus 
			 *  返回值： bool					读取结果		
			 *  参数列表：
			 *    参数类型    					取值范围     		    描述
			 *    matNo : const string&									钢卷号
			 *    desc : CoilConfirmDesc		 						钢卷状态
			*/
			bool getStatus(const string& matNo, int& coilStatus);
		};
	}
}