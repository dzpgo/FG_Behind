
#pragma once
#ifndef _ACTION_CHECK_BEFORE_EVADE_
#define _ACTION_CHECK_BEFORE_EVADE_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "CraneOrderCurrentBase.h"
#include "CranePLCStatusBase.h"

#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

#include "ACTION_COMMON_FUNCTION.h"
#include "CraneEvadeRequestBase.h"
#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"
//#include "RejectConditionEvade_Z32.h"
//#include "RejectConditionEvade_Z33.h"


namespace Monitor
{



	class ACTION_CHECK_BEFORE_EVADE
	{

	public:
		ACTION_CHECK_BEFORE_EVADE(void );
		~ACTION_CHECK_BEFORE_EVADE(void );


	public:

		static  bool  doAction(string craneNO, 
										string bayNO,
										CraneEvadeRequestBase craneEvadeRequest, 
										CranePLCStatusBase cranePLCStatus);




	};

}

#endif