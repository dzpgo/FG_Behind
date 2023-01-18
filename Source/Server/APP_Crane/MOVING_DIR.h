
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
			//������
	      const	 static   string  DIR_X_INC  ;
			//������
		  const	 static   string  DIR_X_DES  ;
		  //������
		  const  static    string  DIR_X_ON_SPOT;





		
		};
}

#endif
