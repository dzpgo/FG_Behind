
#pragma once
#ifndef _MOVING_DIR_
#define _MOVING_DIR_

#include <map>
#include <vector>
#include <pace/P99Component.h>
#include <tag/Tag.h>
#include "log4cplus/LOG.h"

#include "CranePLCOrderBase.h"
#include "DataAccess.h"

namespace Monitor
{
		class MOVING_DIR
		{
			public:
					MOVING_DIR();
					~MOVING_DIR(void);
			private:


			public:

					static  string getDirection(string craneNO, long currentX , long targetX);

		public:
			//方向常量
	      const	 static   string  DIR_X_INC  ;
			//方向常量
		  const	 static   string  DIR_X_DES  ;
		  //方向常量
		  const  static    string  DIR_X_ON_SPOT;





		
		};
}

#endif
