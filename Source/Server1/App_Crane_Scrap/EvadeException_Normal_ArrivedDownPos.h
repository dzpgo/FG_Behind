
#pragma once
#ifndef _EvadeException_Normal_ArrivedDownPos_
#define _EvadeException_Normal_ArrivedDownPos_

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



	class EvadeException_Normal_ArrivedDownPos
	{

	public:
		EvadeException_Normal_ArrivedDownPos(void );
		~EvadeException_Normal_ArrivedDownPos(void );


	public:

		static  bool  satifyException(string craneNO, 
												CranePLCStatusBase cranePLCStatus,
												CraneOrderCurrentBase craneOrderCurrent,
												CraneEvadeRequestBase  craneEvadeRequestBase);

		//2018.10.23 zhangyuhong add
		//只要重钩大车到位就可以先做WMS指令
		static	bool	satifyExceptionHasCoilWhenXOK(string craneNO, 
												CranePLCStatusBase cranePLCStatus,
												OrderCurrentBase craneOrderCurrent,
												CraneEvadeRequestBase  craneEvadeRequestBase);

		//2018.10.23 zhangyuhong add
		//只要空钩大车到位就可以先做WMS指令
		static	bool	satifyExceptionHasNoCoilWhenXOK(string craneNO, 
												CranePLCStatusBase cranePLCStatus,
												OrderCurrentBase craneOrderCurrent,
												CraneEvadeRequestBase  craneEvadeRequestBase);

	};

}

#endif