
#pragma once
#ifndef _WALL_WHOLE_STEP_
#define _WALL_WHOLE_STEP_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "MOVING_DIR.h"

#include "DataAccess.h"

#include "CranePLCStatusBase.h"

#include "WALL_SINGLE_STEP.h"

#include "CraneOrderCurrentBase.h"

#include "Adapter_UACS_CRANE_ORDER_CURRENT.h"

namespace Monitor
{
		class WALL_WHOLE_ORDER
		{
			public:
					WALL_WHOLE_ORDER();
					~WALL_WHOLE_ORDER(void);
			private:


			public:


					static bool getWall(string craneNO, string movingDirection,CranePLCStatusBase  neightborCranePLCStatusBase , long& wallX, long& wallType);

					static string getWallTypeString(long wallType);



		public:

		};
}

#endif
