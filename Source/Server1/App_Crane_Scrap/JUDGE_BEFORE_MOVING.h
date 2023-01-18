
#pragma once
//动车前条件判断主入口
#ifndef _JUDGE_BEFORE_MOVING_
#define _JUDGE_BEFORE_MOVING_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "DataAccess.h"

#include "CONDITION_TARGET_AREA_IS_CLEAN.h"
#include "CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA.h"

#include "CranePLCOrderBase.h"
#include "RED_LINE_BASIC_DATA.h"
#include "CranePLCStatusBase.h"
#include "WALL_SINGLE_STEP.h"
#include "WALL_WHOLE_ORDER.h"
#include "CLOSE_TO_STATIC_WALL.h"
#include "CLOSE_TO_DYNAMIC_WALL.h"
#include "CranePrivilegeInterpreter.h"
#include "CraneEvadeRequestBase.h"
#include "FollowException_4_5.h"

#include "ACTION_COMMON_FUNCTION.h"
namespace Monitor
{
		class JUDGE_BEFORE_MOVING
		{
			public:
					JUDGE_BEFORE_MOVING();
					~JUDGE_BEFORE_MOVING(void);
			private:


			public:
				   static const long X_OFFSET_MAX = 100;

				   static const long X_REACH_MAX = 30;


			public:

					//2018.11.27 zhangyuhong add
					static  bool judge(long orderNO, string craneNO, long currentX , long targetX , long& canReachX);

		private:
					static bool judge_Facing_Auto_Car_Low_Level(string craneNO, long currentX , long targetX, string direction,CranePLCStatusBase  cranePLCStatusBase,
																							 string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase,
																							 long& canReachX);

					static bool judge_Facing_Auto_Car_High_Level(string craneNO, long currentX , long targetX, string direction,CranePLCStatusBase  cranePLCStatusBase,
																							 string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase,
																							 long& canReachX);



					static bool judge_Facing_Manu_Car(string craneNO, long currentX , long targetX, string direction,CranePLCStatusBase  cranePLCStatusBase,
																		   string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase,
																		  long& canReachX);

					static double get_Crane_Order_Priority(string craneNO);

		public:
					
					static bool isACraneStopped(CranePLCStatusBase  cranePLCStatusBase);

					//大车正在移动
					static bool craneIsMoving(CranePLCStatusBase cranePLCStatusBase);

					//行车正在起卷或落卷（包括下降去起卷  和  起卷后上升）
					static bool craneLiftCoilUpDown(CranePLCStatusBase cranePLCStatusBase);


					//2018.10.17 zhangyuhong add
					//空钩起卷下降：COIL_UP_PROCESS、空载、夹钳升降负向
					static bool isACraneLiftCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//重钩起卷上升：COIL_UP_PROCESS、重钩、夹钳升降正向
					static bool isACraneLiftCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//重钩落卷下降：COIL_DOWN_PROCESS、重钩、夹钳升降负向
					static bool isACraneDownCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//空钩落卷上升：COIL_DOWN_PROCESS、空钩、夹钳升降正向
					static bool isACraneDownCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//大车到位不动，只有小车在动
					static bool isACraneOnlyYMoving(CranePLCStatusBase cranePLCStatusBase);

					//2018.12.27 zhangyuhong add
					//试算一把，如果调用面对低级车靠近，可以到目标位，则调用面对低级车靠近算法
					static bool if_Facing_Auto_Car_Low_Level(string craneNO, long currentX , long targetX, string direction,CranePLCStatusBase  cranePLCStatusBase,
																										string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase,
																										long& canReachX);

		
		};
}

#endif
