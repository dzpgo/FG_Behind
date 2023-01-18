
#pragma once
#ifndef _ToBe_Or_Not_ToBe_
#define _ToBe_Or_Not_ToBe_

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

#include "CraneOrderCurrentBase.h"
#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

#include "ACTION_COMMON_FUNCTION.h"

#include "EvadeException_4_4.h"
#include "EvadeException_4_5.h"

#include "EvadeException_4_6.h"

#include "EvadeException_Normal_ArrivedDownPos.h"
#include "EvadeException_Normal_I_Will_Leave.h"
#include "UpgradeActionType_4_6.h"
#include "UpgradeActionType_4_5.h"
#include "UpgradeActionType_4_4.h"

namespace Monitor
{



	class ToBe_Or_Not_ToBe
	{

	public:
		ToBe_Or_Not_ToBe(void );
		~ToBe_Or_Not_ToBe(void );


	public:

		static  string  choose(string craneNO, 
										CranePLCStatusBase cranePLCStatus);

		static const string CHOISE_DO_WMSORDER;
		static const string CHOISE_DO_EVADE;
		static const string CHOISE_NOTHING_TODO;




	};

}

#endif