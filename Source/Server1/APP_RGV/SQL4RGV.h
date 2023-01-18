#pragma once
#ifndef _SQL4RGV_
#define _SQL4RGV_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <PowerTranser/MsgComponent.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"
#include "DataAccess.h"


namespace Monitor
{
	class SQL4RGV
	{
	public:
		SQL4RGV(void);
		~SQL4RGV(void);		

		static bool UpdRGVStatusArrive(string parkingNO, 
														string rgvNO, 
														string loadFlag, 
														string troughDir );

		static bool UpdRGVStatusLock(string rgvNO);

		static bool InitRGVStatusUnlock(string rgvNO);
		

	};
}

#endif

