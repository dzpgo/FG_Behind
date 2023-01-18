
#pragma once
#ifndef _FollowException_4_5_
#define _FollowException_4_5_

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



	class FollowException_4_5
	{

	public:
		FollowException_4_5(void );
		~FollowException_4_5(void );


	public:

		static  bool  satifyException(string craneNO, 
															long targetX, 
															CranePLCStatusBase cranePLCStatus,
															OrderCurrentBase craneOrderCurrent, 
															string neighborCraneNO, 
															CranePLCStatusBase neighborCranePLCStatus);





	};

}

#endif