
#pragma once
#ifndef _WALL_SINGLE_STEP_
#define _WALL_SINGLE_STEP_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "MOVING_DIR.h"

#include "DataAccess.h"

#include "CranePLCStatusBase.h"
namespace Monitor
{
		class WALL_SINGLE_STEP
		{
			public:
					WALL_SINGLE_STEP();
					~WALL_SINGLE_STEP(void);
			private:


			public:


					static bool getWall(string craneNO, string movingDirection,  CranePLCStatusBase  neightborCranePLCStatusBase , long& wallX, long& wallType);



		public:
			const static long WALL_STATIC;
			const static long WALL_DYNAMIC;
		
		};
}

#endif
