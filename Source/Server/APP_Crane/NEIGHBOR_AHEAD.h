
#pragma once
#ifndef _NEIGHBOR_AHEAD_
#define _NEIGHBOR_AHEAD_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "MOVING_DIR.h"

#include "DataAccess.h"

namespace Monitor
{
		class NEIGHBOR_AHEAD
		{
			public:
					NEIGHBOR_AHEAD();
					~NEIGHBOR_AHEAD(void);
			private:


			public:

					static  string getCraneNO(string craneNO, string direction);

		public:
			//前方临近行车号 不存在
	      const	 static   string  NOBODY  ;
			//前方临近行车号  未知
		  const	 static   string  UNKNOW  ;






		
		};
}

#endif
