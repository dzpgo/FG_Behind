#pragma once
#ifndef _Adapter_UACS_CRANE_SAFE_PLC_MSG_
#define _Adapter_UACS_CRANE_SAFE_PLC_MSG_

#include "log4cplus/LOG.h"

#include "DataAccess.h"

#include "CraneOrderCurrentBase.h"

namespace Monitor
{


	class Adapter_UACS_CRANE_SAFE_PLC_MSG
	{
	public:
		Adapter_UACS_CRANE_SAFE_PLC_MSG(void);

		~Adapter_UACS_CRANE_SAFE_PLC_MSG(void);

		//除了心跳电文不插入表外，其它的下发给行车的指令电文存入数据库
		static bool insertSAFEPLCMsg(string craneNO,
			string msgID,
			string msgText);
	};
}
#endif

