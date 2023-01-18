
#pragma once

#ifndef _CONDITION_TARGET_AREA_IS_CLEAN_
#define _CONDITION_TARGET_AREA_IS_CLEAN_

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
		class CONDITION_TARGET_AREA_IS_CLEAN
		{
			public:
					CONDITION_TARGET_AREA_IS_CLEAN();
					~CONDITION_TARGET_AREA_IS_CLEAN(void);
			private:


			public:

					static  bool judge(string craneNO, string movingDirection, long currentX , long targetX, CranePLCStatusBase  neightborCranePLCStatusBase);

	




		
		};
}

#endif
