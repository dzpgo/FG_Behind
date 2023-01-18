
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
			//ǰ���ٽ��г��� ������
	      const	 static   string  NOBODY  ;
			//ǰ���ٽ��г���  δ֪
		  const	 static   string  UNKNOW  ;






		
		};
}

#endif
