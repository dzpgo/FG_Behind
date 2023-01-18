
#pragma once
#ifndef _CLOSE_TO_STATIC_WALL_
#define _CLOSE_TO_STATIC_WALL_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "MOVING_DIR.h"

#include "DataAccess.h"
#include "RED_LINE_BASIC_DATA.h"
#include "CranePLCOrderBase.h"
namespace Monitor
{
		class CLOSE_TO_STATIC_WALL
		{
			public:
					CLOSE_TO_STATIC_WALL();
					~CLOSE_TO_STATIC_WALL(void);
			private:


			public:

					static  bool closeToWall(string craneNO, string direction, long currentX, long wallX, long& XCanGo);

	




		
		};
}

#endif
