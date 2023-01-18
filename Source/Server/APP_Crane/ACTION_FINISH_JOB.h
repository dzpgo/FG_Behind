#pragma once
#ifndef _ACTION_FINISH_JOB_
#define _ACTION_FINISH_JOB_

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
	class ACTION_FINISH_JOB
	{

	public:
		ACTION_FINISH_JOB(void );
		~ACTION_FINISH_JOB(void );


	public:

		static  bool  doAction(string craneNO,
												string bayNO,
												OrderCurrentBase orderCurrent, 
												CranePLCStatusBase cranePLCStatus);

	private:

	};

}

#endif