//2018.11.26 zhangyuhong add


#pragma once
#ifndef _EvadeRequestSenderException_
#define _EvadeRequestSenderException_

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



	class EvadeRequestSenderException
	{

	public:
		EvadeRequestSenderException(void );
		~EvadeRequestSenderException(void );


	public:

		static  bool  satifyException(string craneNO, 
															string neighborCraneNO,
															string  movingDirection);





	};

}

#endif