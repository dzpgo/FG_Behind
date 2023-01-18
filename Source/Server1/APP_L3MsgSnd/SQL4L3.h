#pragma once
#ifndef _SQL4L3_
#define _SQL4L3_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"


namespace Monitor
{
	class SQL4L3
	{
	public:
		SQL4L3(void);
		~SQL4L3(void);

		//============MsgHCP411====================================

		static bool UpdL3PLanStatus(string workSeqNO, string planStatus);

		static bool UpdL3PlanCraneWgtZC(string workSeqNO, long craneWgtZC);

		static bool UpdL3PlanCraneWgtXL(string workSeqNO, long craneWgtXL);






	};
}

#endif

