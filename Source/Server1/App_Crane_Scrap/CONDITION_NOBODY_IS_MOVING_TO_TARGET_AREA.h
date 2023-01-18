
#pragma once

#ifndef _CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA_
#define _CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "MOVING_DIR.h"
#include "NEIGHBOR_AHEAD.h"
#include "CranePLCStatusBase.h"
#include "CraneMonitor.h"

#include "DataAccess.h"

#include "RED_LINE_BASIC_DATA.h"

namespace Monitor
{
		class CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA
		{
			public:
					CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA();
					~CONDITION_NOBODY_IS_MOVING_TO_TARGET_AREA(void);
			private:


			public:

					static  bool judge(string craneNO, string movingDirection, long currentX , long targetX, CranePLCStatusBase  neightborCranePLCStatusBase);

	




		
		};
}

#endif
