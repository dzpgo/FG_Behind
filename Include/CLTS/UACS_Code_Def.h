#pragma once
#include <CLTS.h>
#include <slice/CraneOrder.h>
#include <slice/CranePlan.h>
#include <slice/Stock.h>

namespace CLTS
{
    namespace Common
    {
		// ***************************调度下发标记***************************
		static const int FLAG_DISPAT_INIT = 0;
		static const int FLAG_DISPAT_SND = 10;
		static const int FLAG_DISPAT_SND_ACK = 11;
		static const int FLAG_DISPAT_SND_NACK = 12;
		static const int FLAG_DISPAT_DEL = 20;
		static const int FLAG_DISPAT_DEL_ACK = 21;
		static const int FLAG_DISPAT_DEL_NACK = 22;
		// **************************************************************

		/** 下发标记.
		 *  函数名： convertFlagDispatch 
		 *  返回值： string					下发标记
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    nFlagDispatch : int									下发标记
		 */
		inline string convertFlagDispatch(int nFlagDispatch)
		{
			char szFlagDispatch[256];

			switch (nFlagDispatch)
			{
			case FLAG_DISPAT_INIT:
				sprintf_s(szFlagDispatch, 256, "%d[初始]", nFlagDispatch);
				break;
			case FLAG_DISPAT_SND:
				sprintf_s(szFlagDispatch, 256, "%d[下发请求]", nFlagDispatch);
				break;
			case FLAG_DISPAT_SND_ACK:
				sprintf_s(szFlagDispatch, 256, "%d[下发确认]", nFlagDispatch);
				break;
			case FLAG_DISPAT_SND_NACK:
				sprintf_s(szFlagDispatch, 256, "%d[下发拒绝]", nFlagDispatch);
				break;
			case FLAG_DISPAT_DEL:
				sprintf_s(szFlagDispatch, 256, "%d[删除请求]", nFlagDispatch);
				break;
			case FLAG_DISPAT_DEL_ACK:
				sprintf_s(szFlagDispatch, 256, "%d[删除确认]", nFlagDispatch);
				break;
			case FLAG_DISPAT_DEL_NACK:
				sprintf_s(szFlagDispatch, 256, "%d[删除拒绝]", nFlagDispatch);
				break;
			default:
				sprintf_s(szFlagDispatch, 256, "%d[未定义]", nFlagDispatch);
				break;
			}

			return string(szFlagDispatch);
		}

		/** 库位状态.
		 *  函数名： StockStatus2String 
		 *  返回值： string					库位状态
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    status : StockStatus									库位状态
		 */
		inline string convertStockStatus(StockStatus status)
		{
			char szStockStatus[256];

			switch (status)
			{
			case StockEmpty:
				sprintf_s(szStockStatus, 256, "%d[空闲]", status);
				break;
			case StockReserved:
				sprintf_s(szStockStatus, 256, "%d[预约]", status);
				break;
			case StockOccupied:
				sprintf_s(szStockStatus, 256, "%d[占用]", status);
				break;
			default:
				sprintf_s(szStockStatus, 256, "%d[未定义]", status); 
				break;
			}

			return szStockStatus;
		}

		/** 库位封锁.
		 *  函数名： convertStockLock 
		 *  返回值： string					库位封锁
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    status : StockStatus									库位封锁
		 */
		inline string convertLockStatus(LockStatus lock)
		{
			char szLockStatus[256];

			switch (lock)
			{
			case StockConfirmed:
				sprintf_s(szLockStatus, 256, "%d[确认]", lock);
				break;
			case StockWaitChecking:
				sprintf_s(szLockStatus, 256, "%d[待判]", lock);
				break;
			default:
				sprintf_s(szLockStatus, 256, "%d[未定义]", lock);
				break;
			}

			return string(szLockStatus);
		}

		/** 库位类型.
		 *  函数名： convertStockType 
		 *  返回值： string					库位类型
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    type : StockType										库位类型
		 */
		inline string convertStockType(StockType type)
		{
			char szStockType[256];

			switch (type)
			{
			case StockSaddle:
				sprintf_s(szStockType, 256, "%d[库区]", type);
				break;
			case StockProdLine:
				sprintf_s(szStockType, 256, "%d[机组]", type);
				break;
			case StockCrane:
				sprintf_s(szStockType, 256, "%d[行车]", type);
				break;
			case StockTruck:
				sprintf_s(szStockType, 256, "%d[车位]", type);
				break;
			default:
				sprintf_s(szStockType, 256, "%d[未定义]", type); 
				break;
			}

			return string(szStockType);
		}

		/** 比对计划结果.
		 *  函数名： convertFlagPlanCheck 
		 *  返回值： string					库位类型
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    nFlagPlanCheck : int									比对计划结果
		 */
		inline string convertFlagCheckPlan(int nFlagCheckPlan)
		{
			char szCheckPlan[256];

			switch (nFlagCheckPlan)
			{
			case 0:
				sprintf_s(szCheckPlan, 256, "%d[按计划]", nFlagCheckPlan);
				break;
			case 1:
				sprintf_s(szCheckPlan, 256, "%d[未按计划]", nFlagCheckPlan);
				break;
			case 2:
				sprintf_s(szCheckPlan, 256, "%d[无计划]", nFlagCheckPlan);
				break;
			default:
				sprintf_s(szCheckPlan, 256, "%d[未定义]", nFlagCheckPlan);
				break;
			}

			return szCheckPlan;
		}

		/** 吊运实绩加到报警内容中.
		 *  函数名： convertCmdStatus 
		 *  返回值： string
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    cmdStatus : const string&									指令状态
		 */
		inline string convertCmdStatus(const string& cmdStatus)
		{
			char szCmdStatus[256];

			if (cmdStatus == "R")
			{
				sprintf_s(szCmdStatus, 256, "%s[开始]", cmdStatus.c_str());
			}
			else if (cmdStatus == "C")
			{
				sprintf_s(szCmdStatus, 256, "%s[取消]", cmdStatus.c_str());
			}
			else if (cmdStatus == "S")
			{
				sprintf_s(szCmdStatus, 256, "%s[起卷]", cmdStatus.c_str());
			}
			else if (cmdStatus == "E")
			{
				sprintf_s(szCmdStatus, 256, "%s[落关]", cmdStatus.c_str());
			}
			else
			{
				sprintf_s(szCmdStatus, 256, "%s[未定义]", cmdStatus.c_str());
			}

			return szCmdStatus;
		}
    }
}
