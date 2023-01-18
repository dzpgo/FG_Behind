#pragma once
#ifndef  _Adapter_UACS_CRANE_EVADE_REQUEST_
#define  _Adapter_UACS_CRANE_EVADE_REQUEST_

#include "CraneEvadeRequestBase.h"
#include  "log4cplus/LOG.h"

namespace Monitor{

	class Adapter_UACS_CRANE_EVADE_REQUEST
	{
	public:
		Adapter_UACS_CRANE_EVADE_REQUEST(void);
		~Adapter_UACS_CRANE_EVADE_REQUEST(void);

	public:
		static	bool    GetData(string craneNO , CraneEvadeRequestBase &  craneEvadeBase );

		static  bool   Update( CraneEvadeRequestBase craneEvadeBase );

		static  bool   UpdateStatus(string craneNO ,string status);

		static  bool   UpdateActionType(string craneNO, string actionType);

		static bool   Init(string craneNO);

	};


}


#endif




