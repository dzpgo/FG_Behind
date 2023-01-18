
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
		  //�г����г�֮�����С���  �ӳ����ĵ�������
	      const	static  long   LIMIT_DISTANCE_BETWEEN_CRANES  ;

		  //Ϊ�˱����ٽ�������Ĳ�����
		  const static   long   COMPENSATE_DISTANCE;

		  //׷�����С��������
		  const static   long   FOLLOW_MIN_DISTANCE;
		

		
		};
}

#endif
