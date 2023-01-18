
#pragma once
#ifndef _ACTION_FINISH_Evade_
#define _ACTION_FINISH_Evade_

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
namespace Monitor
{



	class ACTION_FINISH_Evade
	{

	public:
		ACTION_FINISH_Evade(void );
		~ACTION_FINISH_Evade(void );


	public:

		static  bool  doAction(string craneNO, 
										string bayNO,
										CraneEvadeRequestBase craneEvadeRequest, 
										CranePLCStatusBase cranePLCStatus);




	};

}

#endif