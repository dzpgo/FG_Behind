#pragma once
#ifndef _ACTION_UP_POS_IS_OK_
#define _ACTION_UP_POS_IS_OK_

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
	class ACTION_UP_POS_IS_OK
	{

	public:
		ACTION_UP_POS_IS_OK(void );
		~ACTION_UP_POS_IS_OK(void );


	public:

		static  bool  doAction(string craneNO,
												string bayNO,
												OrderCurrentBase orderCurrent, 
												CranePLCStatusBase cranePLCStatus);		

	private:

	};

}

#endif