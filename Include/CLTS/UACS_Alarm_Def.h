#pragma once
#include <CLTS.h>
#include <Slice/CraneOrder.h>
#include <Slice/CranePlan.h>
#include <Slice/Stock.h>
#include <slice/LineTrack.h>
#include <stdio.h>
#include <UACS_Code_Def.h>

#if defined(__WINDOWS__) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__)
#undef STR_FORMAT
#define STR_FORMAT sprintf_s
#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(__LINUX__) || defined(LINUX) || defined(_LINUX)
#undef STR_FORMAT
#define STR_FORMAT snprintf
#endif

namespace CLTS
{
    namespace Common
    {
		// *******************************************吊运计划模块*****************************************
		// 报警事件号
		static const int ALARM_CRANE_PLAN_INIT = 6000;		// 报警-吊运计划初始化
		static const int ALARM_CRANE_PLAN_NEW = 6010;		// 报警-吊运计划新增
		static const int ALARM_CRANE_PLAN_UPD = 6012;		// 报警-吊运计划更新

		static const int ALARM_CRANE_PLAN_DEL_REQBYL3 = 6020;	// 报警-请求删除吊运计划(ByL3)
		static const int ALARM_CRANE_PLAN_DEL_REQBYUACS = 6022;	// 报警-请求删除吊运计划(ByUACS)
		static const int ALARM_CRANE_PLAN_DEL = 6024;			// 报警-吊运计划删除
		static const int ALARM_CRANE_PLAN_DEL_ACKTOL3 = 6026;	// 报警-响应删除吊运计划(ToL3)

		static const int ALARM_CRANE_PLAN_SELECT = 6030;	// 报警-吊运计划开始执行
		static const int ALARM_CRANE_PLAN_CANCEL = 6040;	// 报警-吊运计划取消执行
		static const int ALARM_CRANE_PLAN_LIFTUP = 6050;	// 报警-吊运计划起卷完成
		static const int ALARM_CRANE_PLAN_LIFTDOWN = 6060;	// 报警-吊运计划落关完成
		
		// TAG点名
		static const string EV_CRANE_PLAN_INIT_REQ = "EV_CRANE_PLAN_INIT_REQ";		// 吊运计划初始化
		static const string EV_CRANE_PLAN_DEL_REQ_BYL3 = "EV_CRANE_PLAN_DEL_REQ_BYL3"; // 吊运计划初始化
		// ************************************************************************************************

		// *******************************************库图模块*****************************************
		// 报警事件号
		static const int ALARM_YARDMAP_RECOM_REQ = 3000;		// 报警-库图下发库位推荐请求
		static const int ALARM_YARDMAP_RECOM_ACK = 3010;		// 报警-库图获得库位推荐结果

		static const int ALARM_YARDMAP_LIFTUP_COIL = 3020;		// 报警-钢卷起卷实绩
		static const int ALARM_YARDMAP_LIFTUP_STOCK = 3030;		// 报警-库位起卷实绩
		static const int ALARM_YARDMAP_LIFTUP_CRANE = 3040;		// 报警-行车起卷实绩
		static const int ALARM_YARDMAP_LIFTDOWN_COIL = 3050;	// 报警-钢卷起卷实绩
		static const int ALARM_YARDMAP_LIFTDOWN_STOCK = 3060;	// 报警-库位起卷实绩
		static const int ALARM_YARDMAP_LIFTDOWN_CRANE = 3070;	// 报警-行车起卷实绩

		static const int ALARM_YARDMAP_LOCK_STOCK = 3060;		// 报警-库位设为禁用
		static const int ALARM_YARDMAP_CHECKING_STOCK = 3070;	// 报警-库位设为待判
		static const int ALARM_YARDMAP_CONFIRMED_STOCK = 3080;	// 报警-库位设为投用

		static const int ALARM_YARDMAP_EMPTY_STOCK = 3100;		// 报警-清空库位
		static const int ALARM_YARDMAP_BOOK_STOCK = 3110;		// 报警-预约库位
		static const int ALARM_YARDMAP_OCCUPY_STOCK = 3120;		// 报警-占用库位

		static const int ALARM_YARDMAP_SET_COIL_INFO = 3500;	// 报警-维护钢卷信息
		static const int ALARM_YARDMAP_MOVE_COIL = 3510;		// 报警-移动钢卷信息
		
		// ************************************************************************************************
		
		// *******************************************吊运指令模块*****************************************
		// 报警事件号（逻辑操作）
		static const int ALARM_CREATE_ORDER = 2000;		// 报警-吊运指令创建被调
		static const int ALARM_ORDER_UPDATE = 2010;		// 报警-吊运指令更新被调
		static const int ALARM_ORDER_RECOMM = 2020;		// 报警-吊运指令落关库位请求
		static const int ALARM_ORDER_L3_RECOMM = 2023;	// 报警-吊运指令请求L3推荐库位
		static const int ALARM_ORDER_UACS_RECOMM = 2026;// 报警-吊运指令请求MM推荐库位
		static const int ALARM_ORDER_RECOMM_ACK = 2030;	// 报警-吊运指令库位推荐响应
		static const int ALARM_ORDER_SET_TOSTOCK = 2040;// 报警-吊运指令修改落关被调
		static const int ALARM_ORDER_DISPATCH = 2050;	// 报警-吊运指令下发调度模型
		static const int ALARM_ORDER_DISPATCH_ACK = 2060;// 报警-吊运指令下发调度模型
		static const int ALARM_ORDER_SELECT = 2070;		// 报警-吊运指令开始执行被调
		static const int ALARM_ORDER_CANCEL = 2080;		// 报警-吊运指令取消执行被调
		static const int ALARM_ORDER_LIFTUP = 2090;		// 报警-吊运指令起卷完成被调
		static const int ALARM_ORDER_LIFTDOWN = 2100;	// 报警-吊运指令落关完成被调
		static const int ALARM_ORDER_DEL = 2110;		// 报警-吊运指令删除被调
		static const int ALARM_ORDER_FIRSTJOB = 2120;	// 报警-吊运指令优先执行被调
		static const int ALARM_ORDER_OVERBAY = 2130;	// 报警-吊运指令发生过跨
		static const int ALARM_ORDER_CHANGE_CRANE = 2140;	// 报警-吊运指令修改行车号
		static const int ALARM_ORDER_CHANGE_PRIORITY = 2150;// 报警-吊运指令修改优先级

		// 报警事件号（数据库操作）
		static const int ALARM_DAL_INSERT_ORDER = 2500;	// 报警-写入吊运指令
		static const int ALARM_DAL_SET_RECOMMID = 2510;	// 报警-设定库位推荐请求
		static const int ALARM_DAL_SET_FROMSTOCK = 2520;// 报警-设定指令起卷库位
		static const int ALARM_DAL_SET_TOSTOCK = 2530;	// 报警-设定指令落关库位
		static const int ALARM_DAL_SET_PLANNO = 2540;	// 报警-设定指令对应计划号
		static const int ALARM_DAL_SET_FLAG_DISP = 2550;// 报警-设定指令调度标记(下发模型)
		static const int ALARM_DAL_SET_ACK_DISP = 2560;	// 报警-设定指令调度标记(模型应答)
		static const int ALARM_DAL_SET_FLAG_ENABLE = 2570;	// 报警-设定指令可吊标记
		static const int ALARM_DAL_SET_FLAG_DEL = 2580;	// 报警-设定指令删除标记
		static const int ALARM_DAL_SET_PRIORITY = 2590;	// 报警-设定指令优先级
		static const int ALARM_DAL_INSERT_OPER = 2600;	// 报警-写入吊运实绩
		static const int ALARM_DAL_DEL_ORDER = 2610;	// 报警-删除吊运指令

		// 数据库操作报警
		static const int ALARM_LOGIC = 2000;
		static const int ALARM_DAL_OPER = 2500;

		// TAG点名
		static const string EV_ORDER_DEL = "EV_ORDER_DEL";		// 指令删除信号
		static const string EV_ORDER_UPDATE = "EV_ORDER_UPDATE";	// 指令更新信号
		static const string EV_ORDER_FIRSTJOB = "EV_ORDER_FIRSTJOB";	// 指令提前信号
		static const string EV_ORDER_SET_TO_STOCK = "EV_ORDER_SET_TO_STOCK";	// 指令修改目标库位
		static const string EV_ORDER_CHANGE_CRANE = "EV_ORDER_CHANGE_CRANE";	// 指令修改行车号
		static const string EV_ORDER_CREATE = "EV_ORDER_CREATE";	// 指令新建信号			
		// ************************************************************************************************

		/** 初始化报警内容.
		 *  函数名： initAlarmMsg 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    alarmMsg : AlarmMsg&				                	报警信息
		 *    nEventID : int										触发事件号
		 *    strTitle : string										标题信息
		 *    format : const char*									报警内容格式字符串
		 */
		inline void initAlarmMsg(AlarmMsg& alarmMsg, int nEventID, string strTitle, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// 初始化标题
			if (strTitle.length() == 0)
			{
				// 设定报警基本信息
				STR_FORMAT(szAlarmMsg, 
					MAX_BUFFER_LENGTH, 
					"事件%d",
					nEventID);
				alarmMsg.strTitle = szAlarmMsg;
			}
			else
			{
				// 设定报警基本信息
				STR_FORMAT(szAlarmMsg, 
					MAX_BUFFER_LENGTH, 
					"事件%d, %s", 
					nEventID,
					strTitle.c_str());
				alarmMsg.strTitle = szAlarmMsg;
			}

			// 格式化输入信息
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);
			// 初始化内容
			alarmMsg.strMsg = szMessage;
		}

		/** 行车计划信息加到报警内容中.
		 *  函数名： addAlarmMsg 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    cranePlanDesc : const CranePlanDesc&                	吊运计划
		 *    alarmMsg : AlarmMsg&			                        报警数据
		 *    format : const char*									报警格式字符串
		 *    ...													报警字符串参数列表
		 */
		inline void addAlarmMsg(const CranePlanDesc& cranePlanDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// 格式化输入信息
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// 设定报警基本信息
			alarmMsg.strMsg += szMessage;

			// 设定报警详细信息
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"L3吊运计划信息: 计划号%d, 材料号%s, 类型%s, 命令顺序号%d, 处理组%d, 起吊库位%s, 落关库位%s", 
				cranePlanDesc.planNo,
				cranePlanDesc.matNo.c_str(),
				cranePlanDesc.craneInstCode.c_str(),
				cranePlanDesc.craneSeq,
				cranePlanDesc.hgNo,
				cranePlanDesc.fromStockNo.c_str(),
				cranePlanDesc.toStockNo.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}
		
		/** 行车指令信息加到报警内容中.
		 *  函数名： addAlarmMsg 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    craneOrderDesc : const CraneOrderDesc&                吊运指令
		 *    szAlarmMsg : char*			                        报警字符串
		 *    nMsgLength : int										报警字符串长度
		 *    nEventID : int										内部事件号
		 */
		inline void addAlarmMsg(const CraneOrderDesc& craneOrderDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// 格式化输入信息
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// 设定报警基本信息
			alarmMsg.strMsg += szMessage;

			// 设定报警详细信息
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"吊运指令信息: 材料号%s, 指令编号%d, 类型%d, 计划号%d, 处理组%d, 起卷位%s, 落关位%s, 优先级%d, 行车号%s", 
				craneOrderDesc.matNo.c_str(),
				craneOrderDesc.orderNo,
				craneOrderDesc.orderType,
				craneOrderDesc.planNo,
				craneOrderDesc.groupNo,
				craneOrderDesc.fromStockNo.c_str(),
				craneOrderDesc.toStockNo.c_str(),
				craneOrderDesc.orderPriority,
				craneOrderDesc.craneNo.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}

		/** 库位信息加到报警内容中.
		 *  函数名： addAlarmMsg 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    stockDesc : const StockDesc&							库位信息
		 *    szAlarmMsg : char*			                        报警字符串
		 *    nMsgLength : int										报警字符串长度
		 *    nEventID : int										内部事件号
		 */
		inline void addAlarmMsg(const StockDesc& stockDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];
			string strStockStatus = convertStockStatus(stockDesc.status);
			string strLockStatus = convertLockStatus(stockDesc.lock);
			string strStockType = convertStockType(stockDesc.type);

			// 格式化输入信息
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// 设定报警基本信息
			alarmMsg.strMsg += szMessage;

			// 设定报警详细信息
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"库位当前信息: 库位号=%s, 库位状态=%s, 材料号=%s, 封锁状态=%s, 库位类型=%s, 区域号=%s, 中心坐标=(%d, %d, %d)",
				stockDesc.no.c_str(),
				strStockStatus.c_str(),
				stockDesc.matNo.c_str(),
				strLockStatus.c_str(),
				strStockType.c_str(),
				stockDesc.areaNo.c_str(),
				stockDesc.xCenter,
				stockDesc.yCenter,
				stockDesc.zCenter);
			alarmMsg.strDetail = szAlarmMsg;
		}

		/** 吊运实绩加到报警内容中.
		 *  函数名： addAlarmMsg 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    orderOperDesc : const OrderOperDesc&					吊运实绩
		 *    szAlarmMsg : char*			                        报警字符串
		 *    nMsgLength : int										报警字符串长度
		 *    nEventID : int										内部事件号
		 */
		inline void addAlarmMsg(const OrderOperDesc& orderOperDesc, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];
			string strCmdStatus = convertCmdStatus(orderOperDesc.cmdStatus);
			string strFlagCheckPlan = convertFlagCheckPlan(orderOperDesc.flagCheckPlan);

			// 格式化输入信息
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// 设定报警基本信息
			alarmMsg.strMsg += szMessage;

			// 设定报警详细信息
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"吊运实绩信息: 实绩类型=%s, 指令编号=%d, 行车号=%s, 操作者=%s, 实绩库位=%s, 实绩坐标=(%d, %d, %d), 实绩对照计划=%s", 
				strCmdStatus.c_str(),
				orderOperDesc.orderNo,
				orderOperDesc.craneNo.c_str(),
				orderOperDesc.userName.c_str(),
				orderOperDesc.stockNo.c_str(),
				orderOperDesc.xCranePos,
				orderOperDesc.yCranePos,
				orderOperDesc.zCranePos,
				strFlagCheckPlan.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}

		/** 吊运实绩加到报警内容中.
		 *  函数名： addAlarmMsg 
		 *  返回值： void
		 *  参数列表：
		 *    参数类型    					取值范围     		    描述
		 *    orderOperDesc : const OrderOperDesc&					吊运实绩
		 *    szAlarmMsg : char*			                        报警字符串
		 *    nMsgLength : int										报警字符串长度
		 *    nEventID : int										内部事件号
		 */
		inline void addAlarmMsg(const ExitSaddleTrack& exitSaddleTrack, AlarmMsg& alarmMsg, const char* format, ...)
		{
			char szAlarmMsg[MAX_BUFFER_LENGTH];

			// 格式化输入信息
			char szMessage[MAX_BUFFER_LENGTH];
			memset(szMessage, 0, MAX_BUFFER_LENGTH);
			va_list args;
			va_start(args, format);
			vsnprintf_s(szMessage, MAX_BUFFER_LENGTH, _TRUNCATE, format, args);

			// 设定报警基本信息
			alarmMsg.strMsg += szMessage;

			// 设定报警详细信息
			STR_FORMAT(szAlarmMsg, 
				MAX_BUFFER_LENGTH, 
				"出口跟踪信息: L2鞍座名=%s, 卷号=%s, 重量=%d, 宽度=%d, 内径=%d, 外径=%d, 开卷方向=%d, 下道机组=%s, 包装代码=%s, 合同号=%s, 生产日期=%s", 
				exitSaddleTrack.saddleL2Name.c_str(),
				exitSaddleTrack.coilNo.c_str(),
				exitSaddleTrack.weight,
				exitSaddleTrack.width,
				exitSaddleTrack.inDia,
				exitSaddleTrack.outDia,
				exitSaddleTrack.coilOpenDirection,
				exitSaddleTrack.nextUnitNo.c_str(),
				exitSaddleTrack.packCode.c_str(),
				exitSaddleTrack.workOrderNo.c_str(),
				exitSaddleTrack.productDate.c_str());
			alarmMsg.strDetail = szAlarmMsg;
		}
    }
}

#undef STR_FORMAT
