#pragma once 

#ifndef   _EvadeCancelReceiver_
#define  _EvadeCancelReceiver_

#include "DataAccess.h"
#include "log4cplus/LOG.h"
#include "MOVING_DIR.h"
#include "CranePLCOrderBase.h"
#include "CraneEvadeRequestBase.h"
#include "CranePLCStatusBase.h"
#include "CraneMonitor.h"
#include "CraneEvadeLimitDefine.h"
#include "CranePrivilegeInterpreter.h"
#include "Adapter_UACS_CRANE_EVADE_REQUEST.h"

namespace Monitor
{




	class  EvadeCancelReceiver
	{





	public:
		EvadeCancelReceiver( void );
		~EvadeCancelReceiver( void );




	public:





	public:
		static void  receive(string myCraneNO, string sender,  string evadeDirection) ;



		static bool splitTag_EvadeCancel(string tagVal, string& theSender, string & theEvadeDirection);
	};



}
#endif


