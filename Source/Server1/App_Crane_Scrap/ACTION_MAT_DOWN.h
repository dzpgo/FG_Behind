#pragma once
#ifndef _ACTION_MAT_DOWN_
#define _ACTION_MAT_DOWN_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "OrderCurrentBase.h"
#include "OrderQueueBase.h"
#include "CranePLCStatusBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "ACTION_COMMON_FUNCTION.h"
#include "Clone_DownLoadMoving_Order.h"

namespace Monitor
{
	class ACTION_MAT_DOWN
	{

	public:
		ACTION_MAT_DOWN(void );
		~ACTION_MAT_DOWN(void );


	public:

		static  bool  doAction(string craneNO,
												string bayNO,
												OrderCurrentBase orderCurrent, 
												CranePLCStatusBase cranePLCStatus);

	private:

	};

}

#endif