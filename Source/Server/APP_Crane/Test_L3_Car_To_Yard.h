/*********************************************************************
*		
*  文      件:    CRANE_TESTING_D202_EXIT.h   		
*
*
*  概述：
*        ：行车ACTION动作所调用的公共函数库

*
*  版本历史		
*      2017年04月建立
*********************************************************************/
#pragma once
#ifndef  _Test_L3_Car_To_Yard_
#define  _Test_L3_Car_To_Yard_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "CraneMonitor.h"
#include "OrderCurrentBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

//=================ACTION=========================
#include "ACTION_COMMON_FUNCTION.h"
#include "ACTION_UP_POS_IS_OK.h"
#include "ACTION_MOVE_TO_UP_POS.h"
#include "ACTION_MAT_UP.h"
#include "ACTION_MOVE_TO_DOWN_POS.h"
#include "ACTION_MAT_DOWN.h"
#include "ACTION_FINISH_JOB.h"
#include "ACTION_GRID_INFO_CHECK.h"
#include "ACTION_DOWN_POS_IS_OK.h"



namespace Monitor
{



	class Test_L3_Car_To_Yard
	{

	public:
		Test_L3_Car_To_Yard(void );
		~Test_L3_Car_To_Yard(void );


	public:

		static bool  Test(string craneNO, OrderCurrentBase  orderCurrent ,CranePLCStatusBase cranePLCStatusBase);


	};

}

#endif