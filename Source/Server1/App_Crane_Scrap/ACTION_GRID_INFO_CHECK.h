#pragma once
#ifndef _ACTION_GRID_INFO_CHECK_
#define _ACTION_GRID_INFO_CHECK_

#include <map>
#include <vector>

#include "DataAccess.h"
#include "log4cplus/LOG.h"

#include "OrderCurrentBase.h"
#include "CranePLCStatusBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"
#include "ACTION_COMMON_FUNCTION.h"
#include "Clone_DownLoadMoving_Order.h"
#include "Adapter_UACS_YARDMAP_STOCK_INFO.h"

namespace Monitor
{
	class ACTION_GRID_INFO_CHECK
	{

	public:
		ACTION_GRID_INFO_CHECK(void );
		~ACTION_GRID_INFO_CHECK(void );


	public:

		static  bool  doAction(string craneNO,
												string bayNO,
												OrderCurrentBase orderCurrent, 
												CranePLCStatusBase cranePLCStatus);		

	private:

	};

}

#endif