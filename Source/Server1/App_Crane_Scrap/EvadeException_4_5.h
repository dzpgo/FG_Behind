
#pragma once
#ifndef _EvadeException_4_5_
#define _EvadeException_4_5_

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

namespace Monitor
{



	class EvadeException_4_5
	{

	public:
		EvadeException_4_5(void );
		~EvadeException_4_5(void );


	public:

		static  bool  satifyException(string craneNO, 
												CranePLCStatusBase cranePLCStatus,
												OrderCurrentBase craneOrderCurrent,
												CraneEvadeRequestBase  craneEvadeRequestBase);





	};

}

#endif