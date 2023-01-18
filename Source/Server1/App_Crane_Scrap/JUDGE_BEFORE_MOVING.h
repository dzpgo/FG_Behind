
#pragma once
//����ǰ�����ж������
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

					//�������ƶ�
					static bool craneIsMoving(CranePLCStatusBase cranePLCStatusBase);

					//�г�����������������½�ȥ���  ��  ����������
					static bool craneLiftCoilUpDown(CranePLCStatusBase cranePLCStatusBase);


					//2018.10.17 zhangyuhong add
					//�չ�����½���COIL_UP_PROCESS�����ء���ǯ��������
					static bool isACraneLiftCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//�ع����������COIL_UP_PROCESS���ع�����ǯ��������
					static bool isACraneLiftCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//�ع�����½���COIL_DOWN_PROCESS���ع�����ǯ��������
					static bool isACraneDownCoilDown(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//�չ����������COIL_DOWN_PROCESS���չ�����ǯ��������
					static bool isACraneDownCoilUp(CranePLCStatusBase  cranePLCStatusBase, OrderCurrentBase craneOrderCurrent);

					//�󳵵�λ������ֻ��С���ڶ�
					static bool isACraneOnlyYMoving(CranePLCStatusBase cranePLCStatusBase);

					//2018.12.27 zhangyuhong add
					//����һ�ѣ����������Եͼ������������Ե�Ŀ��λ���������Եͼ��������㷨
					static bool if_Facing_Auto_Car_Low_Level(string craneNO, long currentX , long targetX, string direction,CranePLCStatusBase  cranePLCStatusBase,
																										string  neightborCraneNO, CranePLCStatusBase  neightborCranePLCStatusBase,
																										long& canReachX);

		
		};
}

#endif
