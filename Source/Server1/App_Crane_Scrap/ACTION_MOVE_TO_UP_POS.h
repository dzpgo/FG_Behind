#pragma once
#ifndef _ACTION_MOVE_TO_UP_POS_
#define _ACTION_MOVE_TO_UP_POS_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "OrderCurrentBase.h"
#include "CranePLCStatusBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "ACTION_COMMON_FUNCTION.h"
#include "Clone_DownLoadMoving_Order.h"

namespace Monitor
{
	class ACTION_MOVE_TO_UP_POS
	{

	public:
		ACTION_MOVE_TO_UP_POS(void );
		~ACTION_MOVE_TO_UP_POS(void );


	public:

		static  bool  doAction(string craneNO,
												string bayNO,
												OrderCurrentBase orderCurrent, 
												CranePLCStatusBase cranePLCStatus);

	private:

	};

}

#endif