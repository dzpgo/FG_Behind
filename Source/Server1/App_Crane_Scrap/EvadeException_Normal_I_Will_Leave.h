
#pragma once
#ifndef _EvadeException_Normal_I_Will_Leave_
#define _EvadeException_Normal_I_Will_Leave_

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

#include "MOVING_DIR.h"

namespace Monitor
{



	class EvadeException_Normal_I_Will_Leave
	{

	public:
		EvadeException_Normal_I_Will_Leave(void );
		~EvadeException_Normal_I_Will_Leave(void );


	public:

		static  bool  satifyException(string craneNO, 
												CranePLCStatusBase cranePLCStatus,
												OrderCurrentBase craneOrderCurrent,
												CraneEvadeRequestBase  craneEvadeRequestBase);





	};

}

#endif