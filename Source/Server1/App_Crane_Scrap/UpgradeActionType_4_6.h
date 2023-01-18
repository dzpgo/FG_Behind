
#pragma once
#ifndef _UpgradeActionType_4_6_
#define _UpgradeActionType_4_6_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "OrderCurrentBase.h"
#include "CranePLCStatusBase.h"

#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

#include "ACTION_COMMON_FUNCTION.h"
#include "CraneEvadeRequestBase.h"
#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"

#include "CraneOrderCurrentBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

#include "ACTION_COMMON_FUNCTION.h"
//#include "Test_D202_Exit_To_Yard.h"


namespace Monitor
{



	class UpgradeActionType_4_6
	{

	public:
		UpgradeActionType_4_6(void );
		~UpgradeActionType_4_6(void );


	public:

		static bool    tryUpdate(string craneNO, 
												CranePLCStatusBase cranePLCStatus,
												OrderCurrentBase craneOrderCurrent,
												CraneEvadeRequestBase  craneEvadeRequestBase);





	};

}

#endif