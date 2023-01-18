#pragma once
#ifndef _Adapter_UACS_CRANE_MOVEORDER_MSG_
#define _Adapter_UACS_CRANE_MOVEORDER_MSG_

#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "OrderCurrentBase.h"

namespace Monitor
{


	class Adapter_UACS_CRANE_MOVEORDER_MSG
	{
	public:
		Adapter_UACS_CRANE_MOVEORDER_MSG(void);

		~Adapter_UACS_CRANE_MOVEORDER_MSG(void);

		//获取 UACS_CRANE_ORDER_MSG 的MSG_ID的序列号
		static bool SelMsgID(long& msgID);

		//除了心跳电文不插入表外，其它的下发给行车的指令电文存入数据库
		static bool insertMoveOrderMsg(long msgID, 
																	 long craneNO,
																	 long orderID,
																	 long matWeight, 
																	 long matType, 
																	 long planUpX,
																	 long planUpY,
																	 long planUpZ,
																	 long upRotateAngle,
																	 long planDownX,
																	 long planDownY,
																	 long planDownZ,
																	 long downRotateAngle,
																	 long shortCMD, 
																	 long currentX, 
																	 long currentY, 
																	 long currentZ );

		static bool insertMoveOrderMsgMidPT(long msgID, 
																				map<long, map<string, long> > mapMidPointList);

		//2018.7.1 zhangyuhong add
		//新增行车报警代码写入数据库表-行车报警履历表
		//UACS_CRANE_ALARM_HIS
		static bool insertCraneAlarmMsg(string craneNO, 
																	 long orderID, 
																	 long alarmCode);

		//2018.7.12 zhangyuhong add
		//新增行车手自动切换履历表：主要是为了记录 行车 手自动模式突变的情况
		//UACS_CRANE_AUTOMANU_SWITCH_HIS
		static bool insertCraneAutoManuSwitch(string craneNO, 
																				string switchBefore, 
																				string switchAfter);

		//2019.6.19 zhangyuhong add
		//新增行车紧急状况停止记录表插入
		//UACS_CRANE_URGENT_RECORD
		static bool insertCraneUrgentRecord(long eventNO, 
																			long orderNO, 
																			string craneNO, 
																			long xAct, 
																			long yAct, 
																			long zAct, 
																			long hasCoil
																			);

		//获取所在料格 xmax xmin ysplit
		static bool SelXMaxXMinYSplit(long pointX, long pointY, long& xLimitMax, long& xLimitMin, long& ySplit);

	};
}



#endif

