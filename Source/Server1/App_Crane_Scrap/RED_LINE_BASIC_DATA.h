
#pragma once
#ifndef _RED_LINE_BASIC_DATA_
#define _RED_LINE_BASIC_DATA_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"


#include "DataAccess.h"

namespace Monitor
{
		class RED_LINE_BASIC_DATA
		{
			public:
					RED_LINE_BASIC_DATA();
					~RED_LINE_BASIC_DATA(void);


				

		public:
		  //行车与行车之间的最小间距  从车中心到车中心
	      const	static  long   LIMIT_DISTANCE_BETWEEN_CRANES  ;

		  //为了避免临界而给出的补偿量
		  const static   long   COMPENSATE_DISTANCE;

		  //追随的最小拉开距离
		  const static   long   FOLLOW_MIN_DISTANCE;
		

		
		};
}

#endif
